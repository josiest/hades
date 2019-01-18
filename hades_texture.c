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
    return (game->next_texID)++;
}

size_t Hades_HashTex(const void* tex)
{
    if (!tex) {
        return 0;
    }
    return ((const Hades_Texture*) tex)->id;

}

bool Hades_TexEq(const void* a, const void* b)
{
    if (!a && !b) {
        return true;
    } else if (!a || !b) {
        return false;
    }
    return ((const Hades_Texture*)a)->id == ((const Hades_Texture*)b)->id;
}

void Hades_FreeTex(void* vt)
{
    Hades_Texture* tex = (Hades_Texture*)vt;
    SDL_DestroyTexture(tex->sdl);
    free(tex);
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

    SDL_Texture* tex = NULL;
    tex = SDL_CreateTextureFromSurface(game->renderer, surf);
    SDL_FreeSurface(surf);
    if (!tex) {
        Hades_SetErrorSDL("Unable to create texture from loaded surface");
        return 0;
    }

    const Hades_Texture texcpy = {Hades_NextTexID(game), tex};
    Hades_Texture* htex = (Hades_Texture*) malloc(sizeof(Hades_Texture));
    memcpy(htex, &texcpy, sizeof(Hades_Texture));

    size_t* key = (size_t*) malloc(sizeof(size_t));
    memcpy(key, &htex->id, sizeof(size_t));

    Hades_AddToHMap(game->texs, key, htex);
    return htex->id;
}
