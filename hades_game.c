/** hades_game.c
 */

/* Table of Contents
 *
 * --- Creating and Deleting Games --- 23
 *
 * Hades_CreateGame   25
 * Hades_DestroyGame  80
 *
 * --- Game Functions --- 96
 *
 * Hades_RunGame    98
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "hades_game.h"
#include "hades_error.h"
#include "hades_bool.h"

// --- Creating and Deleting Games ---

Hades_bool Hades_CreateGame(Hades_Game** game, const char* title,
                            SDL_Rect screen_dim)
{
    // Defensive Code
    if (!game) {
        Hades_SetGameError("CreateGame: Cannot write game "
                           "to a null outer pointer");
        return Hades_false;
    }
    if (*game) {
        Hades_SetGameError("CreateGame: Cannot overwrite inner game pointer");
        return Hades_false;
    }
    if (SDL_Init(SDL_INIT_VIDEO)) {
        Hades_SetErrorSDL("CreateGame: SDL could not initialize");
        return Hades_false;
    }

    // Create the game

    *game = malloc(sizeof(Hades_Game));
    (*game)->was_init = Hades_false;
    (*game)->screen_dim = screen_dim;

    strncpy((*game)->title, title, Hades_MaxTitleLength);
    if (((*game)->title)[Hades_MaxTitleLength-1] != '\0') {
        Hades_SetGameError("CreateGame: Game title is too long");
        Hades_DestroyGame(*game);
        return Hades_false;
    }

    (*game)->window = NULL;
    (*game)->window = SDL_CreateWindow(title, screen_dim.x, screen_dim.y,
                                       screen_dim.w, screen_dim.h,
                                       SDL_WINDOW_SHOWN);
    if (!(*game)->window) {
        Hades_SetErrorSDL("CreateGame: Window could not be created");
        Hades_DestroyGame(*game);
        return Hades_false;
    }

    (*game)->renderer = NULL;
    (*game)->renderer = SDL_CreateRenderer((*game)->window, -1,
                                           SDL_RENDERER_ACCELERATED);
    if (!(*game)->renderer) {
        Hades_SetErrorSDL("CreateGame: Renderer could not be created");
        Hades_DestroyGame(*game);
        return Hades_false;
    }
    SDL_SetRenderDrawColor((*game)->renderer, 0xff, 0xff, 0xff, 0xff);

    (*game)->was_init = Hades_true;
    return Hades_true;
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
    if (!(game->was_init)) {
        Hades_SetGameError("RunGame: Game is not completely initialized");
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
