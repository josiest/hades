#ifndef HADES_STDHASH_H
#define HADES_STDHASH_H

#include <stddef.h>
#include <stdbool.h>

enum {
    Hades_MaxBuckets=149
};

/** defined in "hades_hmap.h"
 * size_t Hades_HashID(const void* id);
 *  Hash id (size_t).
 *
 * Parameters:
 *  id - to hash
 */
size_t Hades_HashID(const void*);

/** defined in "hades_hmap.h"
 * bool Hades_IDEq(const void* a, const void* b);
 *  Compare two ids (size_t) for equality.
 *
 * Parametetrs:
 *  a, b - the ids to compare
 */
bool Hades_IDEq(const void*, const void*);

#endif
