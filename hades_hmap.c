#include "hades_hmap.h"
#include "hades_iter.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Hades_HMap*
Hades_NewHMap(const Hades_SizeFunc HashKey, const Hades_BiPredicate KeyEq,
              const Hades_Consumer FreeKey, const Hades_Consumer FreeVal)
{
    const Hades_HMap copy = {
        0, {NULL}, HashKey, KeyEq,
        FreeKey? FreeKey: free, FreeVal? FreeVal: free
    };
    Hades_HMap* map = (Hades_HMap*) malloc(sizeof(Hades_HMap));
    memcpy(map, &copy, sizeof(Hades_HMap));
    return map;
}

void Hades_FreeHMap(Hades_HMap* map)
{
    for (int i = 0; i < Hades_HMapBuckets; i++) {
        Hades_HMapNode* top = map->buckets[i];
        while (top) {
            map->FreeKey(top->key);
            map->FreeVal(top->value);
            Hades_HMapNode* tmp = top;
            top = top->next;
            free(tmp);
        }
    }
    free(map);
}

bool Hades_HMapHasKey(const Hades_HMap* map, const void* key)
{
    return Hades_GetNodeFromHMap(map, key) != NULL;
}

void* Hades_AddToHMap(Hades_HMap* map, void* key, void* value)
{
    Hades_HMapNode* node = Hades_GetNodeFromHMap(map, key);
    if (node) {
        void* oldval = node->value;
        node->value = value;
        return oldval;
    }
    const size_t i = map->HashKey(key) % Hades_HMapBuckets;
    const Hades_HMapNode copy = {key, value, NULL, map->buckets[i]};
    map->buckets[i] = (Hades_HMapNode*) malloc(sizeof(Hades_HMapNode));
    memcpy(map->buckets[i], &copy, sizeof(Hades_HMapNode));
    map->size += 1;
    return NULL;
}

void* Hades_RmFromHMap(Hades_HMap* map, const void* key)
{
    Hades_HMapNode* node = Hades_GetNodeFromHMap(map, key);
    if (!node) {
        return NULL;
    }
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        const size_t i = map->HashKey(key) % Hades_HMapBuckets;
        map->buckets[i] = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }

    map->FreeKey(node->key);
    void* val = node->value;
    free(node);
    map->size -= 1;
    return val;
}

void* Hades_GetFromHMap(const Hades_HMap* map, const void* key)
{
    Hades_HMapNode* node = Hades_GetNodeFromHMap(map, key);
    if (!node) {
        return NULL;
    }
    return node->value;
}

Hades_HMapNode* Hades_GetNodeFromHMap(const Hades_HMap* map, const void* key)
{
    size_t i = map->HashKey(key) % Hades_HMapBuckets;
    Hades_HMapNode* curr = map->buckets[i];
    while (curr && !map->AreKeysEqual(key, curr->key)) {
        curr = curr->next;
    }
    return curr;
}

Hades_Iter* Hades_IterHMapVals(const Hades_HMap* map)
{
    const Hades_Iter itercpy = {NULL, NULL};
    Hades_Iter* iter = (Hades_Iter*) malloc(sizeof(Hades_Iter));
    memcpy(iter, &itercpy, sizeof(Hades_Iter));

    for (int i = Hades_HMapBuckets-1; i >= 0; i--) {
        Hades_HMapNode* curr = map->buckets[i];
        while (curr) {
            const Hades_IterNode nodecpy = {curr->value, iter->top};
            iter->top = (Hades_IterNode*) malloc(sizeof(Hades_IterNode));
            memcpy(iter->top, &nodecpy, sizeof(Hades_IterNode));
            curr = curr->next;
        }
    }
    iter->curr = iter->top;
    return iter;
}