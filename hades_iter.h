#ifndef HADES_ITER_H
#define HADES_ITER_H

#include <stdbool.h>

typedef struct Hades_Iter Hades_Iter;
typedef struct Hades_IterNode Hades_IterNode;

/** defined in "hades_iter.h"
 * struct Hades_Iter;
 *  For iterating data structures.
 *
 * Fields
 *      Hades_IterNode* top - top node
 *  Hades_Consumer FreeData - deallocate the data in a node
 */
struct Hades_Iter {
    Hades_IterNode* top;
    Hades_IterNode* curr;
};

/** defined in "hades_iter.h"
 * struct Hades_IterNode;
 *  Stores info on current iteration
 *
 * Fields
 *            void* data - part of the iterated data
 *  Hades_IterNode* next - next node
 */
struct Hades_IterNode {
    void* data;
    Hades_IterNode* next;
};

/** defined in "hades_iter.h"
 * void Hades_CloseIter(Hades_Iter* iterator);
 *  Close and deallocate an iterator.
 *
 * Parameters:
 *  iterator - to close
 */
void Hades_CloseIter(Hades_Iter*);

/** defined in "hades_iter.h"
 * bool Hades_IterHasNext(Hades_Iter* iterator);
 *  Check to see if iterator has a next item.
 *
 * Parameters:
 *  iterator - to check in
 *
 * Preconditions
 *  iterator isn't null.
 */
bool Hades_IterHasNext(Hades_Iter*);

/** defined in "hades_iter.h"
 * void* Hades_NextFromIter(Hades_Iter* iterator);
 *  Get next item from iterator.
 *
 * Parameters:
 *  iterator - to get item from
 *
 * Preconditions:
 *  iterator isn't null and has a next item.
 */
void* Hades_NextFromIter(Hades_Iter*);

/** defined in "hades_iter.h"
 * Hades_Iter* Hades_CpIter(Hades_Iter* iterator);
 *  Create a shallow copy of iterator.
 *
 * Parameters:
 *  iterator - to copy
 */
Hades_Iter* Hades_CpIter(Hades_Iter*);

#endif
