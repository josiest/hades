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
typedef struct Hades_SpriteIterator Hades_SpriteIterator;
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
 * void Hades_DestroySprite(Hades_Game* game, Hades_Sprite sprite);
 *  Destroy a specific sprite
 *
 * Parameters
 *    game - game to destroy sprite in
 *  sprite - sprite to destroy
 *
 * Postconditions
 *  The specified sprite is completely destroyed
 */
void Hades_DestroySprite(Hades_Game*, Hades_Sprite);

/** defined in "hades_sprite.h"
 * void Hades_SetUpdateTextureFunction(Hades_Game* game, Hades_Sprite sprite,
 *                                     void (*UpdateTexture)(SDL_Texture*));
 *  Define how a specific sprite renders its texture.
 *
 *  Parameters
 *            game - game that contains sprite
 *          sprite - sprite to set UpdateTexture function for
 *   UpdateTexture - pointer to function telling sprite how to render texture
 */
void Hades_SetUpdateTextureFunction(Hades_Game*, Hades_Sprite,
                                    void (*UpdateTexture)(SDL_Texture*));

/** defined in "hades_sprite.h"
 * void
 * Hades_SetSpriteUpdateFunction(Hades_Game* game, Hades_Sprite sprite,
 *                               void (*Update)(Hades_Game*, Hades_Sprite));
 *  Define how a specific sprite changes each frame.
 *
 *  Parameters
 *     game - game that contains the sprite
 *   sprite - sprite to set Update function for
 *   Update - pointer to function telling sprite how to update
 */
void Hades_SetSpriteUpdateFunction(Hades_Game*, Hades_Sprite,
                                   void (*)(Hades_Game*, Hades_Sprite));

/** defined in "hades_sprite.h"
 * void Hades_MoveSprite(Hades_Game* game, Hades_Sprite sprite,
 *                       int dx, int dy);
 *  Move a sprite by dx and dy pixels
 *
 *  Parameters
 *     game - game that contains the sprite
 *   sprite - sprite to move
 *   dx, dy - vector to move by
 */
void Hades_MoveSprite(Hades_Game*, Hades_Sprite, int, int);

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
 * void Hades_DestroySpriteMap(Hades_Sprite_* sprites[], size_t* size);
 *  Destroy a sprite map
 *
 * Parameters
 *  sprites - map to destroy
 *     size - of the sprite map
 *
 * Postconditions
 *  size is set to zero and all sprites are destroyed.
 */
void Hades_DestroySpriteMap(Hades_Sprite_*[], size_t*);

/** defined in "hades_sprite.h"
 * Hades_Sprite_* Hades_GetSprite(Hades_Sprite_* sprites[], Hades_Sprite id,
 *                                Hades_Sprite_** prev);
 *  Retrieve the specified sprite instance.
 *
 * Parameters
 *  sprites - contains the sprite
 *       id - of the sprite
 *     prev - previous sprite in map
 *
 * Postconditions
 *  If sprite doesn't exist in the game or if game doesn't exist, returns null
 */
Hades_Sprite_* Hades_GetSprite(Hades_Sprite_*[], Hades_Sprite, Hades_Sprite_**);

/** defined in "hades_sprite.h"
 * size_t Hades_NextSpriteID(Hades_Game* game);
 *  Get the next sprite id
 *
 * Parameters
 *  game - to grab id from
 *
 * Postconditions
 *  every id returned is unique
 */
size_t Hades_NextSpriteID(Hades_Game*);

/** defined in "hades_sprite.h"
 * Hades_SpriteIterator* Hades_IterateSprites(Hades_Sprite_* sprites[]);
 *  iterate a sprite map
 *
 * Parameters
 *  sprites - map to iterate
 */
Hades_SpriteIterator* Hades_IterateSprites(Hades_Sprite_*[]);

/** defined in "hades_sprite.h"
 * void Hades_CloseSpriteIterator(Hades_SpriteIterator** iter);
 *  close a sprite iterator
 *
 * Parameters
 *  iter - the iterator to close
 *
 * Postconditions
 *  iter points to null
 */
void Hades_CloseSpriteIterator(Hades_SpriteIterator**);

/** defined in "hades_sprite.h"
 * Hades_Sprite_* Hades_NextSprite_(Hades_SpriteIterator** iter);
 *
 * Parameters
 *  iter - to get the next sprite from
 *
 * Preconditions
 *  there is a next sprite to grab
 *
 * Postconditions
 *  iter will be written with the next sprite iterator node
 */
Hades_Sprite_* Hades_NextSprite_(Hades_SpriteIterator**);

#endif
