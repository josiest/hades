/** hades_game.h
 * Hades interface for building and running games
 */

/* Table of Contents
 *
 * Constants    27
 * Hades_Game   31
 *
 * --- Creating and Deleting Games --- 54
 *
 * Hades_CreateGame   56
 * Hades_DestroyGame  83
 *
 * --- Game Functions --- 90
 *
 * Hades_RunGame 92
 */

#ifndef HADES_GAME_H
#define HADES_GAME_H

#include <SDL2/SDL.h>
#include "hades_game.h"
#include "hades_bool.h"

enum {
    Hades_MaxTitleLength = 1000 /** Maximum buffer length for a game title */
};

/** Defined in "hades_game.h"
 *  Hades_Game
 *
 * Used to run a game
 *
 *  Members
 *
 *             char title[] - title of the game window
 *      SDL_Rect screen_dim - dimensions of the game window
 *       SDL_Window* window - points to the game window
 *   SDL_Renderer* renderer - points to the renderer
 *      Hades_bool was_init - states if game is fully initialized or not
 */
typedef struct Hades_Game_ {
    char title[Hades_MaxTitleLength];
    SDL_Rect screen_dim;

    SDL_Window* window;
    SDL_Renderer* renderer;

    Hades_bool was_init;
} Hades_Game;

// --- Creating and Destroying Games ---

/** Defined in "hades_game.h"
 * Hades_bool Hades_CreateGame(Hades_Game** game, const char* title,
 *                             SDL_Rect screen_dim);
 *
 * Create a new game and write it to the inner `game` pointer.
 *
 * If outer `game` pointer is null, or if inner `game` pointer isn't null, or
 * if game title is too long, or if the game fails to initialize for any
 * reason, the function will short circuit and set the relevant error message.
 *
 *  Parameters
 *
 *       game - pointer to pointer to game
 *      title - title for game window
 * screen_dim - dimensions of game window
 *
 *  Return value
 *
 * true on success, false on failure
 *
 *  Note
 *
 * Caller is responsible for using Hades_DestroyGame to safely destroy the
 * game.
 */
Hades_bool Hades_CreateGame(Hades_Game**, const char*, SDL_Rect);

/** Defined in "hades_game.h"
 * void Hades_DestroyGame(Hades_Game* game);
 *
 * Safely destroy `game`
 */
void Hades_DestroyGame(Hades_Game*);

// --- Game Functions ---

/** Defined in "hades_game.h"
 * Hades_bool Hades_RunGame(Hades_Game* game);
 *
 * Run `game`.
 *
 * If `game` is not fully initialized, the function will short circuit and set
 * any relevant error message.
 *
 *  Parameters
 *
 * Hades_Game* game - pointer to a game
 *
 *  Return value
 *
 * true on success, false on failure
 */
Hades_bool Hades_RunGame(Hades_Game*);

#endif
