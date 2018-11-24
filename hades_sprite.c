/** hades_sprite.c
 */

/* Table of Contents
 *
 * - Public Interface -     26
 * --------------------
 *
 * Hades_CreateSprite       30
 * Hades_DestroySprite      50
 *
 * - Private Interface -
 * ---------------------
 *
 * Hades_RenderSprite       64
 * Hades_CreateSpriteMap
 * Hades_DestroySpriteMap
 * Hades_GetSprite
 */

#include "hades_structure.h"
#include "hades_sprite.h"
#include "hades_game.h"
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

// Public Interface

const Hades_Sprite Hades_NullSprite = -1;

Hades_Sprite Hades_CreateSprite(Hades_Game* game, int texture,
                                SDL_Rect* srcrect, SDL_Rect* dstrect)
{
    Hades_Sprite_*
    spriteToAdd = (Hades_Sprite_*) malloc(sizeof(Hades_Sprite_));

    spriteToAdd->id = Hades_NextIDFromGame(game);;
    spriteToAdd->texture = texture;
    spriteToAdd->src = NULL;
    if (srcrect) {
        spriteToAdd->src = (SDL_Rect*) malloc(sizeof(SDL_Rect));
        memcpy(spriteToAdd->src, srcrect, sizeof(SDL_Rect));
    }
    spriteToAdd->dst = NULL;
    if (dstrect) {
        spriteToAdd->dst = (SDL_Rect*) malloc(sizeof(SDL_Rect));
        memcpy(spriteToAdd->dst, dstrect, sizeof(SDL_Rect));
    }
    spriteToAdd->UpdateTexture = NULL;

    // hash into map
    size_t i = game->sprite_count % Hades_MaxSpriteBuckets;
    spriteToAdd->next = game->sprites[i];
    game->sprites[i] = spriteToAdd;
    game->sprite_count += 1;

    return spriteToAdd->id;
}

void Hades_DestroySprite(Hades_Game* game, Hades_Sprite id)
{
    Hades_Sprite_* prevSprite = NULL;
    Hades_Sprite_* spriteToDestroy = Hades_GetSprite(game, id, &prevSprite);
    if (spriteToDestroy) {
        if (prevSprite) {
            prevSprite->next = spriteToDestroy->next;
        }
        if (spriteToDestroy->src) {
            free(spriteToDestroy->src);
        }
        if (spriteToDestroy->dst) {
            free(spriteToDestroy->dst);
        }
        free(spriteToDestroy);
        game->sprite_count -= 1;
    }
}

void Hades_SetUpdateTextureFunction(Hades_Game* game, Hades_Sprite sprite,
                                    void (*UpdateTexture)(SDL_Texture*))
{
    Hades_Sprite_* sprite_ = game->sprites[sprite];
    sprite_->UpdateTexture = UpdateTexture;
}

// --- Private Interface ---

void Hades_RenderSprite(Hades_Game* game, Hades_Sprite_* sprite)
{
    SDL_RenderCopy(game->renderer, game->textures[sprite->texture],
                   sprite->src, sprite->dst);
}

void Hades_DestroySpriteMap(Hades_Game* game)
{
    for (int i = 0; i < Hades_MaxSpriteBuckets; i++) {
        while (game->sprites[i]) {
            Hades_Sprite_* temp = game->sprites[i];
            game->sprites[i] = temp->next;
            if (temp->src) {
                free(temp->src);
            }
            if (temp->dst) {
                free(temp->dst);
            }
            free(temp);
        }
    }
    game->sprite_count = 0;
}

Hades_Sprite_* Hades_GetSprite(Hades_Game* game, Hades_Sprite id,
                               Hades_Sprite_** prev_pointer)
{
    if (!game) {
        return NULL;
    }
    size_t i = game->sprite_count % Hades_MaxSpriteBuckets;
    Hades_Sprite_* prev = NULL;
    for (Hades_Sprite_* current = game->sprites[i];
            current != NULL; current = current->next) {
        if (current->id == id) {
            if (prev_pointer) {
                *prev_pointer = prev;
            }
            return current;
        }
        prev = current;
    }
    return NULL;
}
