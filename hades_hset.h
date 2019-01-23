#ifndef HADES_HSET_H
#define HADES_HSET_H

#include "hades_stdhash.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct Hades_HSet Hades_HSet;
typedef struct Hades_HSetNode Hades_HSetNode;
typedef struct Hades_Iter Hades_Iter;

typedef void (*Hades_Consumer)(void*);
typedef size_t (*Hades_SizeFunc)(const void*);
typedef bool (*Hades_BiPredicate)(const void*, const void*);

/** defined in "hades_hset.h"
 * struct Hades_HSet;
 *  A quasi-generic hash set.
 *
 * Fields
 *                size_t size - of the set
 *  Hades_HSetNode* buckets[] - stores the items
 *    Hades_SizeFunc HashItem - hash an item
 *   Hades_BiPredicate ItemEq - compare two items for equality
 *    Hades_Consumer FreeItem - deallocate item
 */
struct Hades_HSet {
    size_t size;
    Hades_HSetNode* buckets[Hades_MaxBuckets];
    Hades_SizeFunc HashItem;
    Hades_BiPredicate ItemEq;
    Hades_Consumer FreeItem;
};

/** defined in "hades_hset.h"
 * struct Hades_HSetNode;
 *  stores an item for a set
 *
 * Fields
 *      void* item - being stored
 *  Hades_HSetNode* prev - prev bucket
 *  Hades_HSetNode* next - next bucket
 */
struct Hades_HSetNode {
    void* item;
    Hades_HSetNode* prev;
    Hades_HSetNode* next;
};

/** defined in "hades_hset.h"
 * Hades_HSet* Hades_NewHSet(Hades_SizeFunc HashItem,
 *                           Hades_BiPredicate ItemEq,
 *                           Hades_Consumer FreeItem);
 *  Create a new hash set.
 *
 * Parameters:
 *  HashItem - hash an item
 *    ItemEq - compare two items for equality
 *  FreeItem - deallocate an item
 *
 * Postconditions:
 *  If HashItem is null, HashID will be used. If ItemEq is Null, IDEq will
 *  be used. If FreeItem is null, free will be used.
 */
Hades_HSet* Hades_NewHSet(Hades_SizeFunc, Hades_BiPredicate, Hades_Consumer);

/** defined in "hades_hset.h"
 * void Hades_FreeHSet(Hades_HSet* set);
 *  Deallocate set.
 *
 * Parameters:
 *  set - to deallocate
 *
 * Preconditions:
 *  set isn't null
 */
void Hades_FreeHSet(Hades_HSet*);

/** defined in "hades_hset.h"
 * Hades_HSetNode* Hades_GetHSetNode(const Hades_HSet* set,
 *                                   const void* item);
 *  Get a node from a set.
 *
 * Parameters:
 *   set - contains item
 *  item - to get the node of
 *
 * Postconditions:
 *  Returns null if item doesn't exist in set.
 */
Hades_HSetNode* Hades_GetHSetNode(const Hades_HSet*, const void*);

/** defined in "hades_hset.h"
 * bool Hades_AddToHSet(Hades_HSet* set, const void* item, size_t size);
 *  Add item to set.
 *
 * Parameters:
 *   set - to add to
 *  item - to add
 *  size - of item to add
 *
 * Postconditions:
 *  Returns true if item didn't previously exist in set and shallow copies
 *  item.
 */
bool Hades_AddToHSet(Hades_HSet* set, const void* item, size_t size);

/** defined in "hades_hset.h"
 * bool Hades_HSetHas(const Hades_HSet* set, const void* item);
 *  Determine if item exists in set.
 *
 * Parameters:
 *   set - to check in
 *  item - to look for
 */
bool Hades_HSetHas(const Hades_HSet*, const void*);

/** defined in "hades_hset.h"
 * bool Hades_RmFromHSet(Hades_HSet* set, const void* item);
 *  Remove item from set.
 *
 * Parameters:
 *   set - to remove from
 *  item - to remove
 *
 * Postconditions:
 *  Returns false if item doesn't exist in set.
 */
bool Hades_RmFromHSet(Hades_HSet*, const void*);

/** defined in "hades_hset.h"
 * Hades_Iter* Hades_IterHSet(const Hades_HSet* set);
 *  Iterate set.
 *
 * Parameters:
 *  set - to iterate
 *
 * Postconditions:
 *  Iterates over pointers to items.
 */
Hades_Iter* Hades_IterHSet(const Hades_HSet*);

#endif
