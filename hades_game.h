#ifndef HADES_GAME_H
#define HADES_GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct Hades_HMap Hades_HMap;

typedef struct Hades_Game Hades_Game;
typedef struct Hades_Timer Hades_Timer;

enum {
    Hades_MaxStrLength = 1000,
};

/** Defined in "hades_game.h"
 *  Hades_Game
 *
 * Used to run a game
 *
 *  Fields
 *
 *             char title[] - title of the game window
 *          SDL_Rect scrdim - dimensions of the game window
 *       SDL_Window* window - points to the game window
 *   SDL_Renderer* renderer - points to the renderer
 */
struct Hades_Game {
    char title[Hades_MaxStrLength];
    SDL_Rect scrdim;

    SDL_Window* window;
    SDL_Renderer* renderer;

    size_t next_texID;
    Hades_HMap* texs;

    size_t next_sprID;
    Hades_HMap* sprs;

    size_t next_objID;
    Hades_HMap* objs;
    /*size_t objc;
    Hades_ObjStruct* objs[Hades_MaxBuckets];*/

    size_t max_tpf;
    Hades_Timer* timer;

    void (*Start)(Hades_Game*);
};

/** Defined in "hades_game.h"
 * Hades_Game* Hades_NewGame(const char* title, size_t w, size_t h);
 *  Create a new game.
 *
 *  Parameters
 *
 *   title - title for game window
 *    w, h - width and height of the screen
 *
 *  Preconditions
 *   title doesn't exceed max length
 *
 *  Postconditions
 *   If game can't be initialized properly, CreateGame will return null and
 *   set the corresponding error message.
 *
 *  Note
 *   Caller is responsible for using Hades_DestroyGame to safely deallocate the
 *   game.
 */
Hades_Game* Hades_NewGame(const char*, size_t, size_t);

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
