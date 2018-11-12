/** hades_sprite.c
 */

/* Table of Contents
 *
 * Hades_CreateSprite
 * Hades_DestroyAllSprites
 */

#include <stdlib.h>
#include <SDL2/SDL.h>
#include "hades_sprite.h"
#include "hades_game.h"

const Hades_Sprite Hades_NullSprite = -1;

Hades_Sprite Hades_CreateSprite(Hades_Game* game, int texture,
                                SDL_Rect* srcrect, SDL_Rect* dstrect)
{
    game->sprite = (Hades_Sprite_*) malloc(sizeof(Hades_Sprite_));
    game->sprite->id = 0;
    game->sprite->texture = texture;
    game->sprite->src = srcrect;
    game->sprite->dst = dstrect;
    game->sprite->next = NULL;
    return game->sprite->id;
}

void Hades_DestroyAllSprites(Hades_Game* game)
{
    free(game->sprite);
    game->sprite = NULL;
}

void Hades_RenderSprite(Hades_Game* game)
{
    SDL_RenderCopy(game->renderer, game->textures[game->sprite->texture],
                   game->sprite->src, game->sprite->dst);
}
