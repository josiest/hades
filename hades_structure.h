/** Hades_Structure
 * data structures for the game engine
 */

#ifndef HADES_STRUCTURE_H
#define HADES_STRUCTURE_H

#include <stddef.h>
#include <SDL2/SDL.h>

enum {
    Hades_MaxTitleLength = 1000, /** Maximum buffer length for a game title */
    Hades_MaxTextureCount = 200,
    Hades_MaxBuckets = 149,
};

typedef struct Hades_Game Hades_Game;
typedef struct Hades_Sprite_ Hades_Sprite_;
typedef struct Hades_SpriteIterator Hades_SpriteIterator;
typedef struct Hades_Object_ Hades_Object_;
typedef struct Hades_ObjectIterator Hades_ObjectIterator;
typedef struct Hades_Timer Hades_Timer;
typedef int Hades_Sprite; /** Front-end sprite */
typedef int Hades_Object;
typedef void (Hades_CollisionFunction)(Hades_Game*, Hades_Object, Hades_Object);

const Hades_Sprite Hades_NullSprite;    /** null sprite */
const Hades_Object Hades_NullObject;

// --- Sprite ---

/** defined in "hades_structure.h"
 * Hades_Sprite_
 *  used for rendering a texture
 *  back-end sprite data structure
 *
 * Fields
 *       id - used for hashing into sprite map
 *  texture - index of texture
 *      src - where on the texture to copy
 *      dst - where to render sprite
 *     next - pointer to next sprite in bucket
 */
struct Hades_Sprite_ {
    Hades_Sprite id;
    int texture;
    SDL_Rect* src, * dst;
    Hades_Sprite_* next;
    void (*UpdateTexture)(SDL_Texture*);
    void (*Update)(Hades_Game*, Hades_Sprite);
};

/** defined in "hades_structure.h"
 * Hades_SpriteIterator
 *  Iterate a sprite map
 *
 * Fields
 *  sprite - current sprite
 *    next - next iterator node
 */
struct Hades_SpriteIterator {
    Hades_Sprite_* sprite;
    Hades_SpriteIterator* next;
};

/** defined in "hades_structure.h"
 * Hades_Object_
 *  used for detecting collisions
 *  back-end object data structure
 *
 * Fields
 *     Hades_Object id - used for hashing
 *  Hades_Object_ next - next object in bucket
 *
 * Rect Fields
 *     int x, y - upper left corner
 *  size_t w, h - width and height
 *
 * User-Defined Functions
 *
 * OnCollisionStay(Hades_Game* game, Hades_Object this, HadesObject other);
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
struct Hades_Object_ {
    Hades_Object id;
    Hades_Object_* next;
    int x, y;
    size_t w, h;
    Hades_CollisionFunction* OnCollisionStay;
};

/** defined in "hades_structure.h"
 * Hades_ObjectIterator
 *  Iterate over an object map
 * 
 * Fields
 *       Hades_Object_* object
 *  Hades_ObjectIterator* next
 */
struct Hades_ObjectIterator {
    Hades_Object_* object;
    Hades_ObjectIterator* next;
};

/** Defined in "hades_structure.h"
 *  Hades_Game
 *
 * Used to run a game
 *
 *  Fields
 *
 *             char title[] - title of the game window
 *      SDL_Rect screen_dim - dimensions of the game window
 *       SDL_Window* window - points to the game window
 *   SDL_Renderer* renderer - points to the renderer
 */
struct Hades_Game {
    char title[Hades_MaxTitleLength];
    SDL_Rect screen_dim;

    SDL_Window* window;
    SDL_Renderer* renderer;


    SDL_Texture* textures[Hades_MaxTextureCount];
    size_t texture_count;

    size_t current_sprite;
    Hades_Sprite_* sprites[Hades_MaxBuckets];
    size_t sprite_count;

    size_t current_object;
    Hades_Object_* objects[Hades_MaxBuckets];
    size_t object_count;

    size_t max_tpf;
    Hades_Timer* timer;

    void (*Start)(Hades_Game*);
};

#endif
