/** hades_error.c
 */

#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "hades_error.h"

const char* Hades_GetError()
{
    return SDL_GetError();
}

void Hades_SetGameError(const char* description)
{
    const char* fmt = "%s!\n";
    char message[Hades_MaxErrorLength];
    snprintf(message, Hades_MaxErrorLength, fmt, description);
    SDL_SetError(message);
}

void Hades_SetErrorSDL(const char* description)
{
    const char* fmt = "%s! SDL_Error: %s\n";
    char message[Hades_MaxErrorLength];
    snprintf(message, Hades_MaxErrorLength, fmt, description, SDL_GetError());
    SDL_SetError(message);
}
