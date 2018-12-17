/** hades_texture.c
 */

/* Table of Contents
 *
 *  Hades_GetTextureCount   17
 *  Hades_LoadTexture       25
 */

#include "hades_texture.h"
#include "hades_structure.h"
#include "hades_game.h"
#include "hades_error.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

size_t Hades_GetTextureCount(Hades_Game* game)
{
    if (!game) {
        return 0;
    }
    return game->texture_count;
}

bool Hades_LoadTexture(Hades_Game* game, const char* path,
                       Hades_Color* colorkey)
{
    if (!game) {
        return false;
    }
    if (game->texture_count == Hades_MaxTextureCount) {
        Hades_SetGameError("Reached max texture count. Cannot load more");
        return false;
    }

    SDL_Surface* loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL) {
        Hades_SetErrorIMG("Could not load image");
        return false;
    }
    if (colorkey) {
        SDL_SetColorKey(loaded_surface, SDL_TRUE,
                        SDL_MapRGB(loaded_surface->format, colorkey->r,
                                   colorkey->g, colorkey->b));
    }

    SDL_Texture*
    texture = SDL_CreateTextureFromSurface(game->renderer, loaded_surface);
    SDL_FreeSurface(loaded_surface);
    if (!texture) {
        Hades_SetErrorSDL("Unable to create texture from loaded surface");
        return false;
    }

    game->textures[game->texture_count] = texture;
    game->texture_count += 1;
    return true;
}
