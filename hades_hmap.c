#include "hades_hmap.h"
#include "hades_iter.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Hades_HMap*
Hades_NewHMap(const Hades_SizeFunc HashKey,
              const Hades_BiPredicate AreKeysEqual,
              const Hades_Consumer FreeKey, const Hades_Consumer FreeVal)
{
    const Hades_HMap copy = {
        0, {NULL}, HashKey, AreKeysEqual,
        FreeKey? FreeKey: free, FreeVal? FreeVal: free
    };
    Hades_HMap* map = (Hades_HMap*) malloc(sizeof(Hades_HMap));
    memcpy(map, &copy, sizeof(Hades_HMap));
    return map;
}

void Hades_DelHMap(Hades_HMap* map)
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

Hades_HMapEntry* Hades_RmFromHMap(Hades_HMap* map, const void* key)
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

    const Hades_HMapEntry copy = {node->key, node->value};
    Hades_HMapEntry* entry;
    entry = (Hades_HMapEntry*) malloc(sizeof(Hades_HMapEntry));
    memcpy(entry, &copy, sizeof(Hades_HMapEntry));
    free(node);
    map->size -= 1;
    return entry;
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

Hades_Iter* Hades_IterHMap(const Hades_HMap* map, 
                           const Hades_Consumer FreeEntry)
{
    Hades_Iter* iter = Hades_NewIter(FreeEntry);
    for (int i = Hades_HMapBuckets-1; i >= 0; i--) {
        Hades_HMapNode* curr = map->buckets[i];
        while (curr) {
            const Hades_HMapEntry ecpy = {curr->key, curr->value};
            const Hades_IterNode nodecpy = {
                malloc(sizeof(Hades_HMapEntry)), iter->top
            };
            memcpy(nodecpy.data, &ecpy, sizeof(Hades_HMapEntry));

            iter->top = (Hades_IterNode*) malloc(sizeof(Hades_IterNode));
            memcpy(iter->top, &nodecpy, sizeof(Hades_IterNode));

            curr = curr->next;
        }
    }
    return iter;
}
