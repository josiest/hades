#ifndef HADES_HMAP_H
#define HADES_HMAP_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Hades_HMap Hades_HMap;
typedef struct Hades_HMapNode Hades_HMapNode;
typedef struct Hades_HMapEntry Hades_HMapEntry;
typedef struct Hades_Iter Hades_Iter;

typedef size_t (*Hades_SizeFunc)(const void*);
typedef bool (*Hades_BiPredicate)(const void*, const void*);
typedef void (*Hades_Consumer)(void*);

enum {
    Hades_HMapBuckets=149
};

/** defined in "hades_hmap.h"
 * struct Hades_HMap;
 *  Map Data Structure.
 *
 * Fields
 *                     size_t size - of the map
 *       Hades_HMapNode* buckets[] - map storage
 *          Hades_SizeFunc HashKey - hash a key
 *  Hades_BiPredicate AreKeysEqual - compare two keys
 *          Hades_Consumer FreeKey - deallocate a key
 *          Hades_Consumer FreeVal - deallocate a value
 */
struct Hades_HMap {
    size_t size;
    Hades_HMapNode* buckets[Hades_HMapBuckets];
    const Hades_SizeFunc HashKey;
    const Hades_BiPredicate AreKeysEqual;
    const Hades_Consumer FreeKey;
    const Hades_Consumer FreeVal;
};

/** defined in "hades_hmap.h"
 * struct Hades_HMapNode;
 *  Used by the Map Data Structure.
 *
 * Fields
 *            void* key, * value - key, value pair
 *  Hades_HMapNode* prev, * next - prev and next buckets
 */
struct Hades_HMapNode {
    void* key;
    void* value;
    Hades_HMapNode* prev;
    Hades_HMapNode* next;
};

/** defined in "hades_hmap.h"
 * struct Hades_HMapEntry;
 *  A key-value pair of a map.
 *
 * Fields
 *  void* key, * value - the key-value pair
 */
struct Hades_HMapEntry {
    void* key;
    void* value;
};

/** defined in "hades_hmap.h"
 * Hades_HMap*
 * Hades_NewHMap(const Hades_SizeFunc HashKey,
 *               const Hades_BiPredicate AreKeysEqual,
 *               const Hades_Consumer FreeKey, const Hades_Consumer FreeVal);
 *  Create a new hash map.
 *
 * Parameters:
 *       HashKey - hash a key
 *  AreKeysEqual - compare two keys for equality
 *       FreeKey - deallocate a key
 *       FreeVal - deallocate a value
 *
 * Preconditions:
 *  HashKey and AreKeysEqual are not null.
 *
 * Postconditions:
 *  If FreeKey and FreeVal are NULL, free will be used.
 */
Hades_HMap* Hades_NewHMap(const Hades_SizeFunc, const Hades_BiPredicate,
                          const Hades_Consumer, const Hades_Consumer);

/** defined in "hades_hmap.h"
 * void Hades_DelHMap(Hades_HMap* map);
 *  Delete a hash map.
 * 
 * Parameters:
 *  map - to delete
 */
void Hades_DelHMap(Hades_HMap*);

/** defined in "hades_hmap.h"
 * bool Hades_HMapHasKey(const Hades_HMap* map, const void* key);
 *  Determine if a map has a value associated with a key.
 *
 * Parameters:
 *  map - to check in
 *  key - to check for
 */
bool Hades_HMapHasKey(const Hades_HMap*, const void*);

/** defined in "hades_hmap.h"
 * void* Hades_AddToHMap(Hades_HMap* map, void* key, void* value);
 *  Associate a key with a value in a map.
 *
 * Parameters:
 *     map - add to
 *     key - associate with a value
 *   value - associate with a key
 *
 * Postconditions:
 *  Returns null if no value previously associated with that key - otherwise
 *  returns pointer to value previously associated with the key.
 */
void* Hades_AddToHMap(Hades_HMap*, void*, void*);

/** defined in "hades_hmap.h"
 * Hades_HMapEntry* Hades_RmFromHMap(Hades_HMap* map, void* key);
 *  Remove an association from a hash map.
 *
 * Parameters:
 *       map - remove from
 *       key - of entry to remove
 *
 * Postconditions:
 *  Returns the entry that was associated with the key, or NULL if key doesn't
 *  exist in map.
 */
Hades_HMapEntry* Hades_RmFromHMap(Hades_HMap*, const void*);

/** defined in "hades_hmap.h"
 * void* Hades_GetFromHMap(const Hades_HMap* map, const void* key);
 *  Get a value from a hash map via an associated key.
 *
 * Parameters:
 *     map - contains value
 *     key - associated with value
 *
 * Postconditions:
 *  Returns NULL if key doesn't exist in map.
 */
void* Hades_GetFromHMap(const Hades_HMap*, const void*);

/** defined in "hades_hmap.h"
 * Hades_HMapNode*
 * Hades_GetNodeFromHMap(const Hades_HMap* map, const void* key);
 *  Get a node from a hash map via an associated key.
 *
 * Parameters:
 *  map - contains node
 *  key - associated with node
 *
 * Postconditions:
 *  Returns null if key doesn't exist in map.
 */
Hades_HMapNode* Hades_GetNodeFromHMap(const Hades_HMap*, const void*);

/** defined in "hades_hmap.h"
 * Hades_Iter* Hades_IterHMap(const Hades_HMap* map);
 *  Iterate the entries in a map.
 *
 * Parameters:
 *  map - to iterate
 *
 * Postconditions:
 *  The iterator returned iterates HMapEntries
 */
Hades_Iter* Hades_IterHMap(const Hades_HMap*);

#endif
