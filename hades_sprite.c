#include "hades_sprite.h"
#include "hades_hmap.h"
#include "hades_texture.h"
#include "hades_game.h"
#include "hades_error.h"
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <stdio.h>

Hades_Sprite* Hades_NewSpr(Hades_Game* game, size_t tex,
                           const SDL_Rect* srcrect, const SDL_Rect* dstrect)
{
    if (!game) {
        Hades_SetGameError("NewSpr called with null game");
        return NULL;
    }
    Hades_Sprite* spr;
    if ((spr = (Hades_Sprite*) malloc(sizeof(Hades_Sprite))) != NULL) {
        const Hades_Sprite sprcpy = {
            Hades_NextSprID(game), tex, NULL, NULL, NULL, NULL
        };
        memcpy(spr, &sprcpy, sizeof(Hades_Sprite));
    } else {
        Hades_SetGameError("Ran out of memory");
        return NULL;
    }

    if (srcrect != NULL) {
        if ((spr->src = (SDL_Rect*) malloc(sizeof(SDL_Rect))) != NULL) {
            memcpy(spr->src, srcrect, sizeof(SDL_Rect));
        } else {
            Hades_SetGameError("Ran out of memory");
            return NULL;
        }
    }
    if (dstrect != NULL) {
        if ((spr->dst = (SDL_Rect*) malloc(sizeof(SDL_Rect))) != NULL) {
            memcpy(spr->dst, dstrect, sizeof(SDL_Rect));
        } else {
            Hades_SetGameError("Ran out of memory");
            return NULL;
        }
    }
    size_t* idp;
    if ((idp = (size_t*) malloc(sizeof(size_t))) != NULL) {
        *idp = spr->id;
        Hades_AddToHMap(game->sprs, idp, spr);
    } else {
        Hades_SetGameError("Ran out of memory");
        return NULL;
    }
    return spr;
}

void Hades_FreeSpr(void* vspr)
{
    Hades_Sprite* spr = (Hades_Sprite*) vspr;
    if (spr->src != NULL) {
        free(spr->src);
    }
    if (spr->dst != NULL) {
        free(spr->dst);
    }
    free(spr);
}

void Hades_MvSprBy(Hades_Sprite spr, int dx, int dy)
{
    spr.dst->x += dx;
    spr.dst->y += dy;
}

void Hades_MvSprTo(Hades_Sprite spr, int x, int y)
{
    spr.dst->x = x;
    spr.dst->y = y;
}

void Hades_RenderSpr(Hades_Game* game, const Hades_Sprite spr)
{
    if (!game) {
        Hades_SetGameError("RenderSpr called with null game");
        return;
    }
    SDL_Texture* tex;
    if ((tex = (SDL_Texture*) Hades_GetFromHMap(game->texs, &spr.tex))
            != NULL) {
        SDL_RenderCopy(game->renderer, tex, spr.src, spr.dst);
    } else {
        Hades_SetGameError("Sprite texture doesn't exist");
    }
}

size_t Hades_NextSprID(Hades_Game* game)
{
    if (!game) {
        Hades_SetGameError("NextSprID called with null game");
        return 0;
    }
    return (game->next_sprID)++;
}
