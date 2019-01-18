#ifndef HADES_OBJSET_H
#define HADES_OBJSET_H

#include "hades_structure.h"
#include <stddef.h>
#include <stdbool.h>

/** defined in "hades_objset.h"
 * Hades_ObjSetNode
 *  used for creating object sets.
 *
 * Fields
 *               size_t id - of object
 *  Hades_ObjSetNode* next - node in bucket
 */
typedef struct Hades_ObjSetNode Hades_ObjSetNode;
struct Hades_ObjSetNode {
    size_t id;
    Hades_ObjSetNode* next;
};

/** defined in "hades_objset.h"
 * void Hades_ClearObjSet(Hades_ObjSetNode* set[], size_t* size);
 *  Clear the objects from a set.
 *
 * Parameters
 *   set - to clear
 *  size - of the set
 *
 * Postconditions
 *  If size is null, nothing will be written to it.
 */
void Hades_ClearObjSet(Hades_ObjSetNode*[], size_t*);

/** defined in "hades_objset.h"
 * bool Hades_SetHasObj(Hades_ObjSetNode* set[], size_t id);
 *  Determine if an object set contains the given id.
 *
 * Parameters
 *  set - to look in
 *   id - to look for
 */
bool Hades_SetHasObj(Hades_ObjSetNode*[], size_t);

/** defined in "hades_objset.h"
 * bool Hades_AddObjToSet(Hades_ObjSetNode* set[], size_t* size, size_t id);
 *  Add an object to a set
 *
 * Preconditions:
 *  size isn't null
 *
 * Parameters
 *   set - to add to
 *  size - of set
 *    id - of object to add
 */
bool Hades_AddObjToSet(Hades_ObjSetNode*[], size_t*, size_t);

/** defined in "hades_objset.h"
 * bool Hades_RmObjFromSet(Hades_ObjSetNode* set[], size_t* size, size_t id);
 *  Remove an object from a set.
 *
 * Preconditions:
 *  size isn't null
 *
 * Parameters:
 *   set - to remove from
 *  size - of the set
 *    id - of object to remove
 */
bool Hades_RmObjFromSet(Hades_ObjSetNode*[], size_t*, size_t);

/** defined in "hades_objset.h"
 * Hades_ObjSetNode*
 * Hades_GetObjNodeFromSet(Hades_ObjSetNode* set[], size_t id,
 *                         Hades_ObjSetNode** prevptr);
 *  Get an object node from a set.
 *
 * Parameters:
 *      set - to get the object node from
 *       id - of the object node to get
 *  prevptr - to overwrite with the previous node
 *
 * Postconditions:
 *  Returns null if object doesn't exist in set.
 */
Hades_ObjSetNode* Hades_GetObjNodeFromSet(Hades_ObjSetNode*[], size_t,
                                          Hades_ObjSetNode**);

#endif
