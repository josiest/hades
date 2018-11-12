/** hades_game.h
 * Hades interface for building and running games
 */

/* Table of Contents
 *
 * Constants    28
 * Hades_Game   32
 *
 * --- Creating and Deleting Games --- 57
 *
 * Hades_CreateGame   59
 * Hades_DestroyGame  84
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
    Hades_MaxTitleLength = 1000, /** Maximum buffer length for a game title */
    Hades_MaxTextureCount = 200
};

/** Defined in "hades_game.h"
 *  Hades_Game
 *
 * Used to run a game
 *
 *  Fields
 *
 *             char title[] - title of the game window
 *      SDL_Rect screen_dim - dimensions of the game window
 *       SDL_Window* window - points to the game window
 *   SDL_Renderer* renderer - points to the renderer
 */
typedef struct Hades_Game_ {
    char title[Hades_MaxTitleLength];
    SDL_Rect screen_dim;

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* textures[Hades_MaxTextureCount];
    size_t texture_count;

    void (*Start)(struct Hades_Game_*);
} Hades_Game;

// --- Creating and Destroying Games ---

/** Defined in "hades_game.h"
 * Hades_Game* Hades_CreateGame(const char* title, int w, int h);
 *
 *  Create a new game.
 *
 *  Parameters
 *
 *   title - title for game window
 *       w - width of the screen
 *       h - height of the screen
 *
 *  Preconditions
 *   title doesn't exceed max length
 *   width and height are not negative
 *
 *  Postconditions
 *   If game can't be initialized properly, CreateGame will return null and
 *   set the corresponding error message.
 *
 *  Note
 *   Caller is responsible for using Hades_DestroyGame to safely destroy the
 *   game.
 */
Hades_Game* Hades_CreateGame(const char*, int, int);

/** Defined in "hades_game.h"
 * void Hades_DestroyGame(Hades_Game* game);
 *  Safely destroy a game.
 */
void Hades_DestroyGame(Hades_Game*);

// --- Game Functions ---

/** Defined in "hades_game.h"
 * Hades_bool Hades_RunGame(Hades_Game* game);
 *  Run a game
 *
 * Parameters
 *  game - game to run
 *
 * Preconditions
 *  game has been initialized
 *
 * Postconditions
 *  If game fails to run, RunGame will return false and set the corresponding
 *  error message.
 */
Hades_bool Hades_RunGame(Hades_Game*);

#endif
