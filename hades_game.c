/** hades_game.c
 */

/* Table of Contents
 *
 * --- Creating and Deleting Games --- 24
 *
 * Hades_CreateGame   26
 * Hades_DestroyGame  71
 *
 * --- Game Functions --- 91
 *
 * Hades_RunGame    93
 */

#include "hades_game.h"
#include "hades_hmap.h"
#include "hades_iter.h"
#include "hades_structure.h"
#include "hades_error.h"
#include "hades_texture.h"
#include "hades_sprite.h"
#include "hades_object.h"
#include "hades_objstruct.h"
#include "hades_objset.h"
#include "hades_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

// --- Creating and Deleting Games ---

Hades_Game* Hades_NewGame(const char* title, size_t w, size_t h)
{
    if (SDL_Init(SDL_INIT_VIDEO)) {
        Hades_SetErrorSDL("CreateGame: SDL could not initialize");
        return NULL;
    }
    // Create the game

    SDL_Rect scrcopy = {
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h
    };
    Hades_Game* game = malloc(sizeof(Hades_Game));
    memcpy(&game->scrdim, &scrcopy, sizeof(SDL_Rect));

    strncpy(game->title, title, Hades_MaxStrLength);

    game->window = NULL;
    game->window = SDL_CreateWindow(title, game->scrdim.x, game->scrdim.y,
                                    (int) w, (int)  h, SDL_WINDOW_SHOWN);
    if (!game->window) {
        Hades_SetErrorSDL("CreateGame: Window could not be created");
        Hades_DestroyGame(game);
        return NULL;
    }

    game->renderer = NULL;
    game->renderer = SDL_CreateRenderer(game->window, -1,
                                        SDL_RENDERER_ACCELERATED);
    if (!game->renderer) {
        Hades_SetErrorSDL("CreateGame: Renderer could not be created");
        Hades_DestroyGame(game);
        return NULL;
    }
    SDL_SetRenderDrawColor(game->renderer, 0xff, 0xff, 0xff, 0xff);

    game->next_texID = 1;
    game->texs = Hades_NewHMap(Hades_HashTex, Hades_TexEq,
                               NULL, Hades_FreeTex);

    game->next_sprID = 1;
    game->sprs = Hades_NewHMap(Hades_HashSpr, Hades_SprEq,
                               NULL, Hades_FreeSpr);

    game->objc = 0;
    game->next_objID = 0;
    for (int i = 0; i < Hades_MaxBuckets; i++) {
        game->objs[i] = NULL;
    }

    game->timer = Hades_CreateTimer();
    game->max_tpf = 1000/60;

    return game;
}

void Hades_DestroyGame(Hades_Game* game)
{
    if (game) {
        Hades_ClearObjMap(game->objs, &(game->objc));

        Hades_DelHMap(game->sprs);
        Hades_DelHMap(game->texs);

        if (game->renderer) {
            SDL_DestroyRenderer(game->renderer);
        }
        if (game->window) {
            SDL_DestroyWindow(game->window);
        }
        free(game);
    }
    if (SDL_WasInit(SDL_INIT_VIDEO)) {
        SDL_Quit();
    }
}

// --- Game functions ---

bool Hades_RunGame(Hades_Game* game)
{
    if (!game) {
        Hades_SetGameError("RunGame: Cannot run a null game");
        return false;
    }
    game->Start(game);
    bool has_quit = false;
    SDL_Event event;

    while (!has_quit) {
        Hades_StartTimer(game->timer);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                has_quit = true;
            }
        }

        SDL_SetRenderDrawColor(game->renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(game->renderer);

        Hades_Iter* iter = Hades_IterHMap(game->sprs, Hades_FreeSprEntry);
        while (Hades_IterHasNext(iter)) {
            Hades_HMapEntry* entry = (Hades_HMapEntry*)
                Hades_NextFromIter(iter);
            Hades_Sprite spr = *(Hades_Sprite*) entry->value;

            Hades_Texture* tex = (Hades_Texture*)
                Hades_GetFromHMap(game->texs, &spr.tex);
            int tw, th;
            SDL_QueryTexture(tex->sdl, NULL, NULL, &tw, &th);

            Hades_Color oldcol = {0, 0, 0};
            SDL_GetTextureColorMod(tex->sdl, &oldcol.r, &oldcol.g, &oldcol.b);

            if (spr.SetTexture) {
                spr.SetTexture(tex);
            }
            Hades_RenderSpr(game, spr);
            SDL_SetTextureColorMod(tex->sdl, oldcol.r, oldcol.g, oldcol.b);

            if (spr.Update) {
                spr.Update(game, &spr);
            }
            free(entry);
        }
        Hades_CloseIter(iter);
        iter = NULL;
        SDL_RenderPresent(game->renderer);

        Hades_ObjStructIter* objIter = Hades_IterObjMap(game->objs);
        while (objIter) {
            Hades_ObjStruct* obj = Hades_NextObjStructFromIter(&objIter);
            if (obj->Update) {
                obj->Update(game, obj->id);
            }
        }
        Hades_CloseObjStructIter(&objIter);

        Hades_ObjStructIter* outiter = Hades_IterObjMap(game->objs);
        while (outiter) {
            Hades_ObjStruct* this = Hades_NextObjStructFromIter(&outiter);
            Hades_ObjStructIter* initer = Hades_CpObjStructIter(outiter);
            while (initer) {
                Hades_ObjStruct* other = Hades_NextObjStructFromIter(&initer);

                if (Hades_CollidesWith(*this, *other)) {
                    if (!Hades_SetHasObj(this->clsnv, other->id)) {

                        if (this->OnClsnEnter) {
                            this->OnClsnEnter(game, this->id, other->id);
                        }
                        if (other->OnClsnEnter) {
                            other->OnClsnEnter(game, other->id, this->id);
                        }
                        Hades_AddObjToSet(this->clsnv, &(this->clsnc),
                                          other->id);
                        Hades_AddObjToSet(other->clsnv, &(other->clsnc),
                                          this->id);

                    } else {
                        if (this->OnClsnStay) {
                            this->OnClsnStay(game, this->id, other->id);
                        }
                        if (other->OnClsnStay) {
                            other->OnClsnStay(game, other->id, this->id);
                        }
                    }
                } else if (Hades_SetHasObj(this->clsnv, other->id)) {
                    if (this->OnClsnExit) {
                        this->OnClsnExit(game, this->id, other->id);
                    }
                    if (other->OnClsnExit) {
                        other->OnClsnExit(game, other->id, this->id);
                    }
                    Hades_RmObjFromSet(this->clsnv, &(this->clsnc), other->id);
                    Hades_RmObjFromSet(other->clsnv, &(other->clsnc), this->id);
                }
            }
            Hades_CloseObjStructIter(&initer);
        }
        Hades_CloseObjStructIter(&outiter);

        int ticks = Hades_GetTimerTicks(game->timer);
        if (ticks < game->max_tpf) {
            SDL_Delay(game->max_tpf - ticks);
        }
    }
    return true;
}

void Hades_SetFramerateCap(Hades_Game* game, size_t fps)
{
    game->max_tpf = 1000 / fps;
}
