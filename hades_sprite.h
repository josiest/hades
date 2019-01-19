#ifndef HADES_SPRITE_H
#define HADES_SPRITE_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct Hades_Sprite Hades_Sprite;
typedef struct Hades_Game Hades_Game;
typedef struct Hades_Texture Hades_Texture;
typedef void (*Hades_TexFunc)(Hades_Texture*);
typedef void (*Hades_SprFunc)(Hades_Game*, Hades_Sprite*);

/** defined in "hades_sprite.h"
 * struct Hades_Sprite;
 *  For rendering textures.
 *
 * Fields
 *                 size_t id - of sprite
 *                size_t tex - id of texture
 *             SDL_Rect* src - where on the texture to copy
 *             SDL_Rect* dst - where to render sprite
 *  Hades_TexFunc SetTexture - defines how sprite is rendered
 *      Hades_SprFunc Update - defines how sprite behaves each frame.
 */
struct Hades_Sprite {
    size_t id, tex;
    SDL_Rect* src, * dst;
    Hades_TexFunc SetTexture;
    Hades_SprFunc Update;
};

/** defined in "hades_sprite.h"
 * size_t Hades_HashSpr(const void* sprite);
 *  Hash a sprite
 *
 * Parameters:
 *  sprite - to hash
 */
size_t Hades_HashSpr(const void*);

/** defined in "hades_sprite.h"
 * bool Hades_SprEq(void* a, void* b);
 *  Compare two sprites for equality
 *
 * Parameters:
 *  a, b - the two sprites to comare
 */
bool Hades_SprEq(const void*, const void*);

/** defined in "hades_sprite.h"
 * Hades_Sprite* Hades_NewSpr(Hades_Game* game, size_t tex,
 *                            const SDL_Rect* srcrect, const SDL_Rect* dstrect);
 *  Create a new sprite.
 *
 * Parameters
 *     game - to add sprite to
 *      tex - id of texture to use
 *  srcrect - part of the texture to render
 *  dstrect - where to render the sprite
 *
 * Preconditions
 *  tex is the id of a texture loaded into the game.
 *
 * Postconditions
 *  If src- or dst- rect are null, NewSpr uses the default "area vector"
 *  for the specified texture. Otherwise, src- and dst- rect are copied.
 */
Hades_Sprite* Hades_NewSpr(Hades_Game*, size_t,
                           const SDL_Rect*, const SDL_Rect*);

/** defined in "hades_sprite.h"
 * void Hades_FreeSpr(void* sprite);
 *  Deallocate a sprite.
 *
 * Parameters
 *  sprite - to delete
 */
void Hades_FreeSpr(void*);

/** defined in "hades_sprite.h"
 * void Hades_MvSprBy(const Hades_Sprite sprite, int dx, int dy);
 *  Move a sprite by dx and dy pixels
 *
 * Parameters
 *  sprite - to move
 *  dx, dy - to move by
 *
 * Preconditions
 *  sprite isn't null
 *
 * Postconditions
 *  Returns false if sprite doesn't exist in game.
 */
void Hades_MvSprBy(const Hades_Sprite, int, int);

/** defined in "hades_sprite.h"
 * void Hades_MvSprTo(const Hades_Sprite sprite, int x, int y);
 *  Move a sprite to a position.
 *
 * Parameters:
 *  sprite - to move
 *    x, y - position to move to
 *
 * Preconditions:
 *  sprite isn't null
 */
void Hades_MvSprTo(const Hades_Sprite, int, int);

/** defined in "hades_sprite.h"
 * void Hades_RenderSpr(Hades_Game* game, const Hades_Sprite sprite);
 *  Render the loaded sprite.
 *
 * Parameters
 *    game - contains the sprite
 *  sprite - to render
 *
 * Preconditions
 *  game has been initialized, texture loaded and sprite created
 */
void Hades_RenderSpr(Hades_Game*, const Hades_Sprite);

/** defined in "hades_sprite.h"
 * size_t Hades_NextSprID(Hades_Game* game);
 *  Get the next sprite id
 *
 * Parameters
 *  game - to grab id from
 *
 * Postconditions
 *  every id returned is unique
 */
size_t Hades_NextSprID(Hades_Game*);

#endif
