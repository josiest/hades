#ifndef HADES_ITER_H
#define HADES_ITER_H

#include <stdbool.h>

typedef struct Hades_Iter Hades_Iter;
typedef struct Hades_IterNode Hades_IterNode;
typedef void (*Hades_Consumer)(void*);

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
    Hades_Consumer FreeData;
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
 * Hades_Iter* Hades_NewIter(Hades_Consumer FreeData);
 *  Create a new iterator.
 *
 * Parameters:
 *  FreeData - deallocate data in a node
 *
 * Postconditions:
 *  If FreeNode is null, free is used.
 */
Hades_Iter* Hades_NewIter(Hades_Consumer);

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

#endif
