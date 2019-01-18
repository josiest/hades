#ifndef HADES_TEXTURE_H
#define HADES_TEXTURE_H

#include "hades_structure.h"
#include <stddef.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct Hades_Color Hades_Color;
typedef struct Hades_Texture Hades_Texture;
typedef struct Hades_Game Hades_Game;

/** defined in "hades_texture.h"
 * size_t Hades_NextTexID(Hades_Game* game);
 *  Generate the next texture id.
 *
 * Parameters:
 *  game - to get id from
 *
 * Postconditions
 *  Each id is unique.
 */
size_t Hades_NextTexID(Hades_Game*);

/** defined in "hades_texture.h"
 * struct Hades_Color;
 *  Stores color information
 *
 * Fields:
 *  size_t r, g, b - color values for red green and blue respectively.
 */
struct Hades_Color {
    uint8_t r, g, b;
};

/** defined in "hades_texture.h"
 * struct Hades_Texture;
 *  stores SDL_Texture information.
 *
 * Fields:
 *         size_t id - of the texture
 *  SDL_Texture* sdl - SDL information
 */
struct Hades_Texture {
    size_t id;
    SDL_Texture* sdl;
};

/** defined in "hades_texture.h"
 * size_t Hades_HashTex(const void* texture);
 *  hash a texture
 *
 * Parameters:
 *  texture - to hash
 *
 * Postconditions:
 *  if texture is null, returns 0.
 */
size_t Hades_HashTex(const void*);

/** defined in "hades_texture.h"
 * bool Hades_TexEq(const void* a, const void* b);
 *  determine if two textures are equal
 *
 * Parameters:
 *  a, b - ids of textures being compared
 */
bool Hades_TexEq(const void*, const void*);

/** Defined in "hades_texture.h"
 * void Hades_FreeTex(void* texture);
 *  Deallocate a Hades_Texture
 *
 * Parameters
 *  texture - to free
 */
void Hades_FreeTex(void*);

/** Defined in "hades_texture.h"
 * size_t Hades_LoadTex(Hades_Game* game, const char* path,
 *                      Hades_Color* colorkey);
 *  Load a texture into a game
 *
 * Parameters
 *      game - the game to load the texture into
 *      path - the path of the image to load
 *  colorkey - the RGB color to set the color key to
 *
 * Preconditions
 *  game has been initialized*
 *  image in path is png
 *
 * Postconditions
 *  Returns id of texture if successfull, otherwise returns 0 and sets
 *  the corresponding error message.
 *
 *  When rendered, any parts of the texture with the same color as color key
 *  will not be shown. If colorkey is null, the colorkey won't be set.
 */
size_t Hades_LoadTex(Hades_Game*, const char*, const Hades_Color*);

#endif
