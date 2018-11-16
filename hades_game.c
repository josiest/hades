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

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "hades_game.h"
#include "hades_texture.h"
#include "hades_error.h"
#include "hades_bool.h"

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
    for (int i = 0; i < Hades_MaxSpriteBuckets; i++) {
        game->sprites[i] = NULL;
    }
    game->current_id = 0;

    return game;
}

void Hades_DestroyGame(Hades_Game* game)
{
    if (game) {
        Hades_DestroySpriteMap(game);
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

Hades_bool Hades_RunGame(Hades_Game* game)
{
    if (!game) {
        Hades_SetGameError("RunGame: Cannot run a null game");
        return Hades_false;
    }
    game->Start(game);
    Hades_bool has_quit = Hades_false;
    SDL_Event event;

    while (!has_quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                has_quit = Hades_true;
            }
        }

        SDL_SetRenderDrawColor(game->renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(game->renderer);

        for (int i = 0; i < Hades_MaxSpriteBuckets; i++) {
            for (Hades_Sprite_* current = game->sprites[i];
                    current != NULL;
                    current = current->next) {
                Hades_RenderSprite(game, current);
            }
        }
        SDL_RenderPresent(game->renderer);
    }
    return Hades_true;
}

// --- Private Interface ---

size_t Hades_NextIDFromGame(Hades_Game* game)
{
    return (game->current_id)++;
}
