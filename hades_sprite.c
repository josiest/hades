#include "hades_sprite.h"
#include "hades_hmap.h"
#include "hades_texture.h"
#include "hades_structure.h"
#include "hades_game.h"
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <stdio.h>

size_t Hades_HashSpr(const void* sprite)
{
    if (!sprite) {
        return 0;
    }
    return ((const Hades_Sprite*)sprite)->id;
}

bool Hades_SprEq(const void* a, const void* b)
{
    if (!a && !!b) {
        return false;
    } else if (!a || !b) {
        return true;
    }
    return ((const Hades_Sprite*)a)->id == ((const Hades_Sprite*)b)->id;
}

Hades_Sprite* Hades_NewSpr(Hades_Game* game, size_t tex,
                           const SDL_Rect* srcrect, const SDL_Rect* dstrect)
{
    const Hades_Sprite sprcpy = {
        Hades_NextSprID(game), tex, NULL, NULL, NULL, NULL
    };
    Hades_Sprite* spr = (Hades_Sprite*) malloc(sizeof(Hades_Sprite));
    memcpy(spr, &sprcpy, sizeof(Hades_Sprite));

    if (srcrect) {
        spr->src = (SDL_Rect*) malloc(sizeof(SDL_Rect));
        memcpy(spr->src, srcrect, sizeof(SDL_Rect));
    }
    if (dstrect) {
        spr->dst = (SDL_Rect*) malloc(sizeof(SDL_Rect));
        memcpy(spr->dst, dstrect, sizeof(SDL_Rect));
    }
    size_t* idp = (size_t*) malloc(sizeof(size_t));
    memcpy(idp, &spr->id, sizeof(size_t));
    Hades_AddToHMap(game->sprs, idp, spr);
    return spr;
}

void Hades_FreeSpr(void* vspr)
{
    Hades_Sprite* spr = (Hades_Sprite*) vspr;
    if (spr->src) {
        free(spr->src);
    }
    if (spr->dst) {
        free(spr->dst);
    }
    free(spr);
}

void Hades_MvSprBy(const Hades_Sprite spr, int dx, int dy)
{
    spr.dst->x += dx;
    spr.dst->y += dy;
}

void Hades_MvSprTo(const Hades_Sprite spr, int x, int y)
{
    spr.dst->x = x;
    spr.dst->y = y;
}

void Hades_RenderSpr(Hades_Game* game, const Hades_Sprite spr)
{
    void* htex = Hades_GetFromHMap(game->texs, &spr.tex);
    SDL_RenderCopy(game->renderer, ((Hades_Texture*) htex)->sdl,
                   spr.src, spr.dst);
}

size_t Hades_NextSprID(Hades_Game* game)
{
    return (game->next_sprID)++;
}

void Hades_FreeSprEntry(void* ve)
{
    Hades_HMapEntry* e = (Hades_HMapEntry*) ve;
    free(e->key);
    Hades_FreeSpr(e->value);
    free(e);
}
