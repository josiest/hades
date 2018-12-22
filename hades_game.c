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

#include "hades_structure.h"
#include "hades_error.h"
#include "hades_game.h"
#include "hades_texture.h"
#include "hades_sprite.h"
#include "hades_object.h"
#include "hades_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

// --- Creating and Deleting Games ---

Hades_Game* Hades_CreateGame(const char* title, int w, int h)
{
    if (SDL_Init(SDL_INIT_VIDEO)) {
        Hades_SetErrorSDL("CreateGame: SDL could not initialize");
        return NULL;
    }
    // Create the game

    Hades_Game* game = malloc(sizeof(Hades_Game));
    game->screen_dim.x = SDL_WINDOWPOS_UNDEFINED;
    game->screen_dim.y = SDL_WINDOWPOS_UNDEFINED;
    game->screen_dim.w = w;
    game->screen_dim.h = h;

    strncpy(game->title, title, Hades_MaxTitleLength);

    game->window = NULL;
    game->window = SDL_CreateWindow(title, game->screen_dim.x,
                                    game->screen_dim.y, w, h, SDL_WINDOW_SHOWN);
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

    game->texture_count = 0;
    for (int i = 0; i < Hades_MaxTextureCount; i++) {
        game->textures[i] = NULL;
    }

    game->sprite_count = 0;
    game->current_sprite = 0;
    for (int i = 0; i < Hades_MaxBuckets; i++) {
        game->sprites[i] = NULL;
    }

    game->object_count = 0;
    game->current_object = 0;
    for (int i = 0; i < Hades_MaxBuckets; i++) {
        game->objects[i] = NULL;
    }

    game->dead_count = 0;
    for (int i = 0; i < Hades_MaxBuckets; i++) {
        game->dead_objects[i] = NULL;
    }

    game->timer = Hades_CreateTimer();
    game->max_tpf = 1000/60;

    return game;
}

void Hades_DestroyGame(Hades_Game* game)
{
    if (game) {
        Hades_DestroyObjectMap(game->objects, &(game->object_count));
        Hades_DestroySpriteMap(game->sprites, &(game->sprite_count));
        for (int i = 0; i < game->texture_count; i++) {
            SDL_DestroyTexture(game->textures[i]);
        }
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

        Hades_SpriteIterator* iter = Hades_IterateSprites(game->sprites);
        while (iter) {
            Hades_Sprite_* current = Hades_NextSprite_(&iter);

            SDL_Texture* texture = game->textures[current->texture];

            Hades_Color old_color = {0, 0, 0};
            SDL_GetTextureColorMod(texture, &(old_color.r), &(old_color.g),
                                   &(old_color.b));

            if (current->SetTexture) {
                current->SetTexture(texture);
            }
            Hades_RenderSprite(game, current);
            SDL_SetTextureColorMod(texture, old_color.r, old_color.g,
                                   old_color.b);

            if (current->Update) {
                current->Update(game, current->id);
            }
        }
        Hades_CloseSpriteIterator(&iter);
        SDL_RenderPresent(game->renderer);

        Hades_ObjectIterator* objIter = Hades_IterateObjects(game->objects);
        while (objIter) {
            Hades_Object_* object = Hades_NextObject_(&objIter);
            if (object->Update) {
                object->Update(game, object->id);
            }
        }
        Hades_CloseObjectIterator(&objIter);

        Hades_ObjectIterator* outiter = Hades_IterateObjects(game->objects);
        while (outiter) {
            Hades_Object_* this = Hades_NextObject_(&outiter);
            Hades_ObjectIterator* initer = Hades_CopyObjectIterator(outiter);
            while (initer) {
                Hades_Object_* other = Hades_NextObject_(&initer);

                if (Hades_CollidesWith(*this, *other)) {

                    if (!Hades_SetContainsObject(this->collision_set,
                                                 other->id)) {

                        if (this->OnCollisionEnter) {
                            this->OnCollisionEnter(game, this->id, other->id);
                        }
                        if (other->OnCollisionEnter) {
                            other->OnCollisionEnter(game, other->id, this->id);
                        }
                        Hades_AddObjectToSet(this->collision_set,
                                             &this->collision_count,
                                             other->id);
                        Hades_AddObjectToSet(other->collision_set,
                                             &other->collision_count,
                                             this->id);

                    } else {
                        if (this->OnCollisionStay) {
                            this->OnCollisionStay(game, this->id, other->id);
                        }
                        if (other->OnCollisionStay) {
                            other->OnCollisionStay(game, other->id, this->id);
                        }
                    }
                } else if (Hades_SetContainsObject(this->collision_set,
                                                   other->id)) {
                    if (this->OnCollisionExit) {
                        this->OnCollisionExit(game, this->id, other->id);
                    }
                    if (other->OnCollisionExit) {
                        other->OnCollisionExit(game, other->id, this->id);
                    }
                    Hades_RemoveObjectFromSet(this->collision_set,
                                              &this->collision_count,
                                              other->id);
                    Hades_RemoveObjectFromSet(other->collision_set,
                                              &other->collision_count,
                                              this->id);
                }
            }
            Hades_CloseObjectIterator(&initer);
        }
        Hades_CloseObjectIterator(&outiter);

        Hades_ObjectSetNode* iter = Hades_IterateObjectSet(game->dead_objects);
        while (iter) {
            Hades_ObjectSetNode* current = Hades_NextObjectNode(&iter);
            Hades_DestroyObject_(game, id);
        }
        Hades_CloseObjectNodeIterator(&iter);

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

// --- Private Interface ---
