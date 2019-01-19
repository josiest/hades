#ifndef HADES_OBJECT_H
#define HADES_OBJECT_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct Hades_Object Hades_Object;
typedef struct Hades_ObjSetNode Hades_ObjSetNode;
typedef struct Hades_Game Hades_Game;

typedef void (*Hades_ClsnFunc)(Hades_Game*, Hades_Object*, Hades_Object*);
typedef void (*Hades_ObjFunc)(Hades_Game*, Hades_Object*);

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
struct Hades_Object {
    size_t id;
    int x, y;
    size_t w, h;

    size_t clsnc;
    Hades_ObjSetNode* clsnv[Hades_MaxBuckets];

    Hades_ClsnFunc OnClsnEnter,
                   OnClsnStay,
                   OnClsnExit;

    Hades_ObjFunc Update;
};

/** defined in "hades_object.h"
 * Hades_Object* Hades_NewRectObj(Hades_Game* game, int x, int y,
 *                                size_t w, size_t h);
 *  Create a rect object in the game.
 *
 * Parameters:
 *  game - to contain the rect
 *  x, y - upper left corner
 *  w, h - width and height
 *
 * Postconditions
 *  The object is given a unique id.
 */
Hades_Object* Hades_NewRectObj(Hades_Game*, int, int, size_t, size_t);

/** defined in "hades_object.h"
 * void Hades_FreeObj(void* object);
 *  Deallocate an object
 *
 * Parameters:
 *  object - to deallocate
 */
void Hades_FreeObj(void*);

/** defined in "hades_object.h"
 * bool Hades_MvObjBy(Hades_Object* object, int dx, int dy);
 *  Move an object by a displacement vector.
 *
 * Parameters:
 *  object - to move
 *  dx, dy - displacement vector
 *
 * Postconditions:
 *  Returns false if obj doesn't exist in game.
 */
bool Hades_MvObjBy(Hades_Object*, int, int);

/** defined in "hades_object.h"
 * bool Hades_MvObjTo(Hades_Object* object, int x, int y);
 *  Move an object to a position.
 *
 * Parameters:
 *  object - to move
 *    x, y - position to move to
 *
 * Postconditions:
 *  Returns false if obj doesn't exist in game.
 */
bool Hades_MvObjTo(Hades_Object*, int, int);

/** defined in "hades_object.h"
 * size_t Hades_NextObjID(Hades_Game* game);
 *  Generate the next object id.
 *
 * Parameters:
 *  game - to get id from
 *
 * Preconditions:
 *  Has been called less than SIZE_MAX-1 times.
 *
 * Postconditions
 *  Every id is unique.
 */
size_t Hades_NextObjID(Hades_Game* game);
/** defined in "hades_object.h"
 * size_t Hades_HashObj(const void* object);
 *  Hash an object
 *
 * Parameters
 *  object - to hash
 */
size_t Hades_HashObj(const void*);

/** defined in "hades_object.h"
 * bool Hades_ObjsEq(const void* a, const void* b);
 *  Compare to objects for equality
 *
 * Parameters
 *  a, b - the objects to compare
 */
bool Hades_ObjEq(const void*, const void*);

/** defined in "hades_object.h"
 * bool Hades_ClsnWith(const Hades_Object this, const Hades_Object other);
 *  Determine if two objects are colliding with each other.
 *
 * Parameters:
 *  this, other - the objects to test
 */
bool Hades_ClsnWith(const Hades_Object, const Hades_Object);

#endif
