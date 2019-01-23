#include "hades_hset.h"
#include "hades_stdhash.h"
#include "hades_iter.h"
#include "hades_error.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Hades_HSet* Hades_NewHSet(Hades_SizeFunc HashItem, Hades_BiPredicate ItemEq,
                          Hades_Consumer FreeItem)
{
    
    Hades_HSet* set = (Hades_HSet*) malloc(sizeof(Hades_HSet));
    if (NULL == set) {
        Hades_SetGameError("Ran out of memory when creating a set");
        return NULL;
    }
    const Hades_HSet setcpy = {
        0, {NULL}, HashItem? HashItem : Hades_HashID,
        ItemEq? ItemEq : Hades_IDEq, FreeItem? FreeItem : free
    };
    memcpy(set, &setcpy, sizeof(Hades_HSet));
    return set;
}

void Hades_FreeHSet(Hades_HSet* set)
{
    if (NULL == set) {
        Hades_SetGameError("FreeHSet was called with a null object");
    }
    for (int i = 0; i < Hades_MaxBuckets; i++) {
        Hades_HSetNode* top = set->buckets[i];
        while (top) {
            set->FreeItem(top->item);
            Hades_HSetNode* tmp = top;
            top = top->next;
            free(tmp);
        }
    }
    free(set);
}

Hades_HSetNode* Hades_GetHSetNode(const Hades_HSet* set, const void* item)
{
    size_t i = set->HashItem(item) % Hades_MaxBuckets;
    Hades_HSetNode* node = set->buckets[i];
    while (node != NULL) {
        if (NULL == set->ItemEq) {
            puts("ItemEq is null!");
        }
        if (set->ItemEq(item, node->item)) {
            break;
        }
        node = node->next;
    }
    return node;
}

bool Hades_AddToHSet(Hades_HSet* set, const void* item, size_t size)
{
    if (NULL == set) {
        puts("AddToHSet called with a null set");
        return false;
    }
    if (Hades_GetHSetNode(set, item) != NULL) {
        return false;
    }
    const size_t i = set->HashItem(item) % Hades_MaxBuckets;
    Hades_HSetNode nodecpy = {malloc(size), NULL, set->buckets[i]};
    if (nodecpy.item != NULL) {
        memcpy(nodecpy.item, item, size);
    } else {
        puts("Ran out of memory when adding to a set");
        return false;
    }
    set->buckets[i] = (Hades_HSetNode*) malloc(sizeof(Hades_HSetNode));
    if (set->buckets[i] != NULL) {
        memcpy(set->buckets[i], &nodecpy, sizeof(Hades_HSetNode));
        set->size += 1;
    } else {
        puts("Ran out of memory when creating a set");
        set->buckets[i] = nodecpy.next;
        return false;
    }
    return true;
}

bool Hades_HSetHas(const Hades_HSet* set, const void* item)
{
    if (NULL == set) {
        puts("HSetHasItem called with null set");
        return false;
    }
    Hades_HSetNode* node = Hades_GetHSetNode(set, item);
    return node != NULL;
}

bool Hades_RmFromHSet(Hades_HSet* set, const void* key)
{
    if (NULL == set) {
        puts("RmFromHSet called with null set");
        return false;
    }
    Hades_HSetNode* node = Hades_GetHSetNode(set, key);
    if (!node) {
        return false;
    }
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        set->buckets[set->HashItem(key) % Hades_MaxBuckets] = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    set->FreeItem(node->item);
    free(node);
    set->size -= 1;
    return true;
}

Hades_Iter* Hades_IterHSet(const Hades_HSet* set)
{
    if (NULL == set) {
        Hades_SetGameError("IterHSet called with null set");
        return NULL;
    }
    Hades_Iter* iter = (Hades_Iter*) malloc(sizeof(Hades_Iter));
    if (iter != NULL) {
        Hades_Iter itercpy = {NULL, NULL};
        memcpy(iter, &itercpy, sizeof(Hades_Iter));
    } else {
        Hades_SetGameError("Ran out of memory when creating a set iterator");
        return NULL;
    }

    for (int i = 0; i < Hades_MaxBuckets; i++) {
        Hades_HSetNode* curr = set->buckets[i];
        while (curr != NULL) {
            const Hades_IterNode nodecpy = {curr->item, iter->top};
            iter->top = (Hades_IterNode*) malloc(sizeof(Hades_IterNode));
            if (iter->top != NULL) {
                memcpy(iter->top, &nodecpy, sizeof(Hades_IterNode));
                curr = curr->next;
            } else {
                Hades_SetGameError("Ran out of memory when creating a set "
                                   "iterator");
                iter->top = nodecpy.next;
                Hades_CloseIter(iter);
                return NULL;
            }
        }
    }
    iter->curr = iter->top;
    return iter;
}
