/** hades_game.c
 */

/* Table of Contents
 *
 * --- Creating and Deleting Games --- 23
 *
 * Hades_CreateGame   25
 * Hades_DestroyGame  62
 *
 * --- Game Functions --- 78
 *
 * Hades_RunGame    80
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "hades_game.h"
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

    return game;
}

void Hades_DestroyGame(Hades_Game* game)
{
    if (game) {
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

        SDL_RenderPresent(game->renderer);
    }
    return Hades_true;
}
