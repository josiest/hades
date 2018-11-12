/** hades_texture.h
 * Hades interface for loading textures
 */

/* Table of Contents
 *
 *  Hades_GetTextureCount    18
 *  Hades_LoadTexture        33
 */

#ifndef HADES_TEXTURE_H
#define HADES_TEXTURE_H

#include <stddef.h>
#include "hades_game.h"
#include "hades_bool.h"

/** Defined in "hades_texture.h"
 * Hades_GetTextureCount
 *  Get the amount of texture currently loaded
 *
 * Parameters
 *  game - game to query
 *
 * Preconditions
 *  all textures have been added via Hades_LoadTexture
 *
 * Postconditions
 *  if game is null, returns 0
 */
size_t Hades_GetTextureCount(Hades_Game*);

/** Defined in "hades_texture.h"
 * Hades_LoadTexture
 *  Load a texture into a game
 *
 * Parameters
 *  game - the game to load the texture into
 *  path - the path of the image to load
 *
 * Preconditions
 *  game has been initialized*
 *  image in path is png
 *
 * Postconditions
 *  If successful, GetTextureCount updates texture count and returns true.
 *  The index used for the texture is the same as texture count before
 *  updating. The user is responsible for keeping track of what indeces
 *  correspond to what images.
 *
 *  If GetTextureCount fails, it will return false and set the corresponding
 *  error message.
 */
Hades_bool Hades_LoadTexture(Hades_Game*, const char*);

#endif
