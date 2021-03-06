#include "hades_hmap.h"
#include "hades_stdhash.h"
#include "hades_iter.h"
#include "hades_error.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Hades_HMap*
Hades_NewHMap(const Hades_SizeFunc HashKey, const Hades_BiPredicate KeyEq,
              const Hades_Consumer FreeKey, const Hades_Consumer FreeVal)
{
    const Hades_HMap copy = {
        0, {NULL}, HashKey? HashKey: Hades_HashID, KeyEq? KeyEq: Hades_IDEq,
        FreeKey? FreeKey: free, FreeVal? FreeVal: free
    };
    Hades_HMap* map = NULL;
    if ((map = (Hades_HMap*) malloc(sizeof(Hades_HMap))) != NULL) {
        memcpy(map, &copy, sizeof(Hades_HMap));
    } else {
        Hades_SetGameError("Ran out of memory when trying to create a map");
    }
    return map;
}

void Hades_FreeHMap(Hades_HMap* map)
{
    if (!map) {
        Hades_SetGameError("FreeHMap was called with a null map");
        return;
    }
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
    if (!map) {
        Hades_SetGameError("HMapHasKey was called with a null map");
        return false;
    }
    return Hades_GetHMapNode(map, key) != NULL;
}

void* Hades_AddToHMap(Hades_HMap* map, const void* key, size_t keysz,
                      void* value)
{
    if (NULL == map) {
        puts("AddToHMap was called with a null map");
        return NULL;
    }
    Hades_HMapNode* node = Hades_GetHMapNode(map, key);
    if (node != NULL) {
        void* oldval = node->value;
        node->value = value;
        return oldval;
    }
    const size_t i = map->HashKey(key) % Hades_HMapBuckets;
    Hades_HMapNode ncpy = {malloc(keysz), value, NULL, map->buckets[i]};
    if (NULL == ncpy.key) {
        puts("Ran out of memory when allocating key for hmap");
        return NULL;
    }
    memcpy(ncpy.key, key, keysz);
    map->buckets[i] = (Hades_HMapNode*) malloc(sizeof(Hades_HMapNode));
    if (NULL == map->buckets[i]) {
        puts("Ran out of memory when allocating node for hmap");
        map->buckets[i] = ncpy.next;
        free(ncpy.key);
        return NULL;
    }
    memcpy(map->buckets[i], &ncpy, sizeof(Hades_HMapNode));
    if (map->buckets[i]->next) {
        map->buckets[i]->next->prev = map->buckets[i];
    }
    map->size += 1;
    return NULL;
}

void* Hades_RmFromHMap(Hades_HMap* map, const void* key)
{
    if (!map) {
        Hades_SetGameError("RmFromHMap was called with a null map");
    }
    Hades_HMapNode* node = Hades_GetHMapNode(map, key);
    if (!node) {
        return NULL;
    }
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        const size_t i = map->HashKey(key) % Hades_HMapBuckets;
        map->buckets[i] = node->next;
    }
    if (node->next != NULL) {
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
    if (!map) {
        Hades_SetGameError("GetFromHMap was called with a null map");
    }
    Hades_HMapNode* node = Hades_GetHMapNode(map, key);
    if (!node) {
        return NULL;
    }
    return node->value;
}

Hades_HMapNode* Hades_GetHMapNode(const Hades_HMap* map, const void* key)
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
    if (!map) {
        Hades_SetGameError("IterHMapVals was called with a null map");
    }

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
