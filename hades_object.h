#ifndef HADES_OBJECT_H
#define HADES_OBJECT_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct Hades_Game Hades_Game;
typedef int Hades_Object;

/** Function type for collision functions */
typedef void (*Hades_ClsnFunc)(Hades_Game*, Hades_Object, Hades_Object);
/** Function type for object game-loop functions */
typedef void (*Hades_ObjFunc)(Hades_Game*, Hades_Object);


/** defined in "hades_object.h"
 * Hades_Object Hades_NewRectObj(Hades_Game* game, int x, int y,
 *                               size_t w, size_t h);
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
Hades_Object Hades_NewRectObj(Hades_Game*, int, int, size_t, size_t);

/** defined in "hades_object.h"
 * bool Hades_RmObj(Hades_Game* game, Hades_Object object);
 *  Remove an object from the game.
 *
 * Parameters:
 *    game - contains the object
 *  object - to remove
 *
 * Postconditions:
 *  returns false if object doesn't exist in the game.
 */
bool Hades_RmObj(Hades_Game*, Hades_Object);

/** defined in "hades_object.h"
 * bool Hades_DefObjClsnEnter(Hades_Game* game, Hades_Object obj,
 *                            Hades_ClsnFunc OnClsnEnter);
 *  Define how an object acts when it enters a collision with another.
 *
 * Parameters
 *         game - contains the object
 *          obj - object to modify
 *  OnClsnEnter - collision enter function
 *
 * Postconditions:
 *  Returns false if obj doesn't exist in game.
 */
bool Hades_DefObjClsnEnter(Hades_Game*, Hades_Object, Hades_ClsnFunc);

/** defined in "hades_object.h"
 * bool Hades_DefObjClsnStay(Hades_Game* game, Hades_Object obj,
 *                           Hades_ClsnFunc OnClsnStay);
 *  Define how an object acts when colliding with another.
 *
 * Parameters
 *        game - contains the object
 *         obj - object to modify
 *  OnClsnStay - collision stay function
 *
 * Postconditions:
 *  Returns false if obj doesn't exist in game.
 */
bool Hades_DefObjClsnStay(Hades_Game*, Hades_Object, Hades_ClsnFunc);

/** defined in "hades_object.h"
 * bool Hades_DefObjClsnExit(Hades_Game* game, Hades_Object obj,
 *                           Hades_ClsnFunc OnClsnExit);
 *  Define how on object acts when it stops colliding with another.
 *
 * Parameters:
 *        game - contains the object
 *         obj - object to modify
 *  OnClsnExit - collision exit function
 *
 * Postconditions:
 *  Returns false if obj doesn't exist in game.
 */
bool Hades_DefObjClsnExit(Hades_Game*, Hades_Object, Hades_ClsnFunc);

/** defined in "hades_objet.h"
 * bool Hades_DefObjUpdate(Hades_Game* game, Hades_Object obj,
 *                         Hades_ObjFunc Update);
 *  Define how an object behaves for each frame.
 *
 * Parameters:
 *    game - contains the object
 *     obj - object to modify
 *  Update - update function
 *
 * Postconditions:
 *  Returns false if obj doesn't exist in game.
 */
bool Hades_DefObjUpdate(Hades_Game*, Hades_Object, Hades_ObjFunc);

/** defined in "hades_object.h"
 * bool Hades_MvObjBy(Hades_Game* game, Hades_Object obj, int dx, int dy);
 *  Move an object by a displacement vector.
 *
 * Parameters:
 *    game - contains the object
 *     obj - object to move
 *  dx, dy - displacement vector
 *
 * Postconditions:
 *  Returns false if obj doesn't exist in game.
 */
bool Hades_MvObjBy(Hades_Game*, Hades_Object, int, int);

/** defined in "hades_object.h"
 * bool Hades_MvObjTo(Hades_Game* game, Hades_Object obj, int x, int y);
 *  Move an object to a position.
 *
 * Parameters:
 *  game - contains the object
 *   obj - object to move
 *  x, y - position to move to
 *
 * Postconditions:
 *  Returns false if obj doesn't exist in game.
 */
bool Hades_MvObjTo(Hades_Game*, Hades_Object, int, int);

#endif
