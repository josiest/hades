/** hades_sprite.h
 * Render textures in a game
 */

/* Table of Contents
 *
 * Constants
 * Hades_SpriteNode
 * Hades_CreateSprite
 * Hades_DestroyAllSprites
 */

#ifndef HADES_SPRITE_H
#define HADES_SPRITE_H

// forward declarations for circular dependencies
typedef struct Hades_Sprite_ Hades_Sprite_;

#include <SDL2/SDL.h>
#include "hades_game.h"
#include "hades_bool.h"

typedef int Hades_Sprite;               /** Front-end sprite */
const Hades_Sprite Hades_NullSprite;    /** null sprite */

/** defined in "hades_sprite.h"
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
    struct Hades_Sprite_* next;
};

/** defined in "hades_sprite.h"
 * Hades_Sprite Hades_CreateSprite(Hades_Game* game, int texture,
 *                                 SDL_Rect* srcrect, SDL_Rect* dstrect);
 *  Create a new sprite.
 *
 * Parameters
 *     game - game to add sprite to
 *  texture - name or index of texture to use
 *  srcrect - what part of the texture to render
 *  dstrect - where to render the sprite
 *
 * Preconditions
 *  texture is a valid index that has a loaded texture associated with it.
 *  src- and dst- rect have no negative numbers and are not bigger than
 *  the screen.
 *
 * Postconditions
 *  If src- or dst- rect are null, CreateSprite uses the default "area vector"
 *  for the specified texture.
 */
Hades_Sprite Hades_CreateSprite(Hades_Game*, int, SDL_Rect*, SDL_Rect*);

/** defined in "hades_sprite.h"
 * void Hades_DestroyAllSprites(Hades_Game* game);
 *  Safely destroy all sprites in the game.
 *
 * Parameters
 *  game - the game to destroy sprites in
 *
 * Postconditions
 *  no sprites are left undestroyed
 */
void Hades_DestroyAllSprites(Hades_Game*);

/** defined in "hades_sprite.h"
 * void Hades_RenderSprite(Hades_Game* game);
 *  Render the loaded sprite.
 *
 * Parameters
 *  game - the game to render the sprite in
 *
 * Preconditions
 *  game has been initialized, texture loaded and sprite created
 *
 * Postconditions
 *  the sprite will be rendered to the game
 */
void Hades_RenderSprite(Hades_Game*);

#endif
