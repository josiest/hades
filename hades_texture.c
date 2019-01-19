#include "hades_texture.h"
#include "hades_hmap.h"
#include "hades_structure.h"
#include "hades_game.h"
#include "hades_error.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>

size_t Hades_NextTexID(Hades_Game* game)
{
    if (!game) {
        Hades_SetGameError("NextTexID called with null game");
        return 0;
    }
    return (game->next_texID)++;
}

void Hades_FreeTex(void* vt)
{
    if (!vt) {
        Hades_SetGameError("FreeTex called with null texture");
    }
    SDL_Texture* tex = (SDL_Texture*)vt;
    SDL_DestroyTexture(tex);
}

size_t Hades_LoadTex(Hades_Game* game, const char* path,
                     const Hades_Color* colkey)
{
    SDL_Surface* surf = IMG_Load(path);
    if (!surf) {
        Hades_SetErrorIMG("Could not load image");
        return 0;
    }
    if (colkey) {
        SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, colkey->r,
                                                   colkey->g, colkey->b));
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(game->renderer, surf);
    SDL_FreeSurface(surf);
    if (!tex) {
        Hades_SetErrorSDL("Unable to create texture from loaded surface");
        return 0;
    }

    size_t* idp = (size_t*) malloc(sizeof(size_t));
    *idp = Hades_NextTexID(game);

    Hades_AddToHMap(game->texs, idp, tex);
    return *idp;
}
