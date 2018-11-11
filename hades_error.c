/** hades_error.c
 */

#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "hades_error.h"

const char* Hades_GetError()
{
    return SDL_GetError();
}

void Hades_SetGameError(const char* description)
{
    SDL_SetError("%s!\n", description);
}

void Hades_SetErrorSDL(const char* description)
{
    SDL_SetError("%s! SDL Error %s\n", description, SDL_GetError());
}

void Hades_SetErrorIMG(const char* description)
{
    IMG_SetError("%s! SDL_image Error %s\n", description, IMG_GetError());
}
