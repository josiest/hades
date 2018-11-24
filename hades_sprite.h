/** hades_sprite.h
 * Render textures in a game
 */

/* Table of Contents
 *
 * - Public Interface -     34
 * --------------------
 *
 * Hades_Sprite             38
 * Hades_NullSprite         39
 * Hades_CreateSprite       66
 * Hades_DestroySprite      88
 *
 * - Private Interface -    101
 * ---------------------
 *
 * Hades_RenderSprite       103
 * Hades_DestroySpriteMap   119
 * Hades_GetSprite          134
 */

#ifndef HADES_SPRITE_H
#define HADES_SPRITE_H

#include <SDL2/SDL.h>
#include "hades_bool.h"

typedef struct Hades_Game Hades_Game;
typedef struct Hades_Sprite_ Hades_Sprite_;
typedef int Hades_Sprite;

// --------------------
// - Public Interface -
// --------------------

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
 *  for the specified texture. Otherwise, src- and dst- rect are copied.
 */
Hades_Sprite Hades_CreateSprite(Hades_Game*, int, SDL_Rect*, SDL_Rect*);

/** defined in "hades_sprite.h"
 * void Hades_DestroySprite(Hades_Game* game, Hades_Sprite* sprite);
 *  Destroy a specific sprite
 *
 * Parameters
 *    game - game to destroy sprite in
 *  sprite - pointer to sprite to destroy
 *
 * Postconditions
 *  The specified sprite is completely destroyed, and the sprite is set to null
 */
void Hades_DestroySprite(Hades_Game*, Hades_Sprite*);

// --- Private Interface ----

/** defined in "hades_sprite.h"
 * void Hades_RenderSprite(Hades_Game* game, Hades_Sprite_* sprite);
 *  Render the loaded sprite.
 *
 * Parameters
 *    game - the game to render the sprite in
 *  sprite - pointer to the sprite to render
 *
 * Preconditions
 *  game has been initialized, texture loaded and sprite created
 *
 * Postconditions
 *  the sprite will be rendered to the game
 */
void Hades_RenderSprite(Hades_Game*, Hades_Sprite_*);

/** defined in "hades_sprite.h"
 * void Hades_DestroySpriteMap(Hades_Game* game);
 *  Safely destroy all sprites in the game.
 *
 * Parameters
 *  game - the game to destroy sprites in
 *
 * Precodnitions
 *  All Sprites have been added via Hades_CreateSprite
 *
 * Postconditions
 *  no sprites are left undestroyed
 */
void Hades_DestroySpriteMap(Hades_Game*);

/** defined in "hades_sprite.h"
 * Hades_Sprite_* Hades_GetSprite(Hades_Game* game, Hades_Sprite sprite,
 *                                Hades_Sprite_** prev_pointer);
 *  Retrieve the specified sprite instance.
 *
 * Parameters
 *    game - the game to get the sprite from
 *  sprite - the id of the sprite to retrieve
 *
 * Postconditions
 *  If sprite doesn't exist in the game or if game doesn't exist, returns null
 */
Hades_Sprite_* Hades_GetSprite(Hades_Game*, Hades_Sprite, Hades_Sprite_**);

#endif
