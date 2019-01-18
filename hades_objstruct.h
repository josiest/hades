#ifndef HADES_OBJSTRUCT_H
#define HADES_OBJSTRUCT_H

#include "hades_structure.h"
#include <stddef.h>
#include <stdbool.h>

typedef int Hades_Object;
typedef struct Hades_Game Hades_Game;

typedef void (*Hades_ClsnFunc)(Hades_Game*, Hades_Object, Hades_Object);
typedef void (*Hades_ObjFunc)(Hades_Game*, Hades_Object);

typedef struct Hades_ObjSetNode Hades_ObjSetNode;
typedef struct Hades_ObjStruct Hades_ObjStruct;
typedef struct Hades_ObjStructIter Hades_ObjStructIter;

/** defined in "hades_object.h"
 * struct Hades_Object;
 *  used for detecting collisions
 *
 * Fields
 *    size_t id - of object
 *
 * Rect Fields
 *     int x, y - upper left corner
 *  size_t w, h - width and height
 *
 * User-Defined Functions
 *
 * OnCollisionStay(Hades_Game* game, Hades_Object* this,
 *                 Hades_Object* other);
 *  Define how an object collides with another
 *
 *  Parameters
 *       game - contains the objects
 *       this - being collided with
 *      other - colliding into
 *
 *  Preconditions
 *   game exists, and this and other exist in game
 *
 *  Postconditions
 *   called for every frame the two objects collide
 */
struct Hades_ObjStruct {
    Hades_Object id;
    int x, y;
    size_t w, h;
    Hades_ObjStruct* next;

    size_t clsnc;
    Hades_ObjSetNode* clsnv[Hades_MaxBuckets];

    Hades_ClsnFunc OnClsnEnter,
                   OnClsnStay,
                   OnClsnExit;

    Hades_ObjFunc Update;
};

/** defined in "hades_objstruct.h"
 * void Hades_ClearObjMap(Hades_ObjStruct* map[], size_t* size);
 *  Clear all associations from an object map.
 *
 * Parameters
 *   map - to clear
 *  size - of the map
 *
 * Postconditions
 *  size is set to 0
 */
void Hades_ClearObjMap(Hades_ObjStruct*[], size_t*);

/** defined in "hades_objstruct.h"
 * Hades_ObjStruct*
 * Hades_GetObjStructFromMap(Hades_ObjStruct* map[], Hades_Object id,
 *                           Hades_ObjStruct** prevptr);
 *  Get an object struct from a map by id.
 *
 * Parameters
 *      map - contains object
 *       id - of object
 *  prevptr - to overwrite with prev node
 *
 * Postconditions
 *  Returns null if object not in map. If prevptr is not null, GetObject will
 *  overwrite the object's previous node to prevptr.
 */
Hades_ObjStruct*
Hades_GetObjStructFromMap(Hades_ObjStruct*[], Hades_Object, Hades_ObjStruct**);

/** defined in "hades_objstruct.h"
 * Hades_Object Hades_NextObjID(Hades_Game* game);
 *  Get the next object id.
 *
 * Parameters
 *  game - contains the id
 *
 * Preconditions
 *  game is not null
 *
 * Postconditions
 *  Every id is unique.
 */
Hades_Object Hades_NextObjID(Hades_Game*);

/** defined in "hades_objstruct.h"
 * bool Hades_CollidesWith(const Hades_ObjStruct this,
 *                         const Hades_ObjStruct other);
 *  Determine if two objects are colliding.
 *
 * Parameters
 *   this - being collided with
 *  other - colliding into
 *
 * Postconditions
 *  true if the two objects are colliding.
 */
bool Hades_CollidesWith(const Hades_ObjStruct, const Hades_ObjStruct);

/** defined in "hades_objstruct.h"
 * typedef struct Hades_ObjStructIter Hades_ObjStructIter;
 *  Used for iterating an ObjStruct bucket array.
 *
 * Fields
 *       Hades_ObjStruct* obj - object
 *  Hades_ObjStructIter* next - next node
 */
struct Hades_ObjStructIter {
    Hades_ObjStruct* obj;
    Hades_ObjStructIter* next;
};

/** defined in "hades_objstruct.h"
 * Hades_ObjStructIter* Hades_IterObjMap(Hades_ObjStruct* objs[]);
 *  Iterate an ObjStruct bucket array.
 *
 * Parameters
 *  objs - objects to iterate
 */
Hades_ObjStructIter* Hades_IterObjMap(Hades_ObjStruct*[]);

/** defined in "hades_objstruct.h"
 * void Hades_CloseObjStructIter(Hades_ObjStructIter** iter);
 *  Close an ObjStructIter.
 *
 * Parameters
 *  iter - to close
 */
void Hades_CloseObjStructIter(Hades_ObjStructIter**);

/** defined in "hades_objstruct.h"
 * Hades_ObjStruct* Hades_NextObjStructFromIter(Hades_ObjStructIter** iter);
 *  Get the next ObjStruct from an ObjStructIter.
 *
 * Parameters:
 *  iter - contains object
 */
Hades_ObjStruct* Hades_NextObjStructFromIter(Hades_ObjStructIter**);

/** defined in "hades_objstruct.h"
 * Hades_ObjStructIter* Hades_CpObjStructIter(Hades_ObjStructIter* iter);
 *  Copy an ObjStructIter.
 *
 * Parameters:
 *  iter - to copy
 */
Hades_ObjStructIter* Hades_CpObjStructIter(Hades_ObjStructIter*);

#endif
