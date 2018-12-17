/** hades_game.h
 * Hades interface for building and running games
 */

/* Table of Contents
 *
 * Constants    31
 * Hades_Game   37
 *
 * --- Creating and Deleting Games --- 65
 *
 * Hades_CreateGame   66
 * Hades_DestroyGame  91
 *
 * --- Game Functions --- 98
 *
 * Hades_RunGame 100
 *
 * --- Private Interface ---
 * 
 * Hades_NextIDFromGame
 */

#ifndef HADES_GAME_H
#define HADES_GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct Hades_Game Hades_Game;

// ---------------------
// - Private Interface -
// ---------------------

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
 * bool Hades_RunGame(Hades_Game* game);
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
bool Hades_RunGame(Hades_Game*);

/** Defined in "hades_game.h"
 * void Hades_SetFramerateCap(Hades_Game* game, size_t fps);
 *  Cap the framerate
 *
 * Parameters
 *  game - the game to cap the frame rate of
 *   fps - max frames per second
 */
void Hades_SetFramerateCap(Hades_Game*, size_t);

#endif
