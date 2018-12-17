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

    spriteToAdd->id = Hades_NextSpriteID(game);;
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
    spriteToAdd->Update = NULL;

    // hash into map
    size_t i = game->sprite_count % Hades_MaxBuckets;
    spriteToAdd->next = game->sprites[i];
    game->sprites[i] = spriteToAdd;
    game->sprite_count += 1;

    return spriteToAdd->id;
}

void Hades_DestroySprite(Hades_Game* game, Hades_Sprite id)
{
    Hades_Sprite_* prevSprite = NULL;
    Hades_Sprite_* spriteToDestroy = Hades_GetSprite(game->sprites, id,
                                                     &prevSprite);
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

void Hades_SetSpriteUpdateFunction(Hades_Game* game, Hades_Sprite sprite,
                                   void (*Update)(Hades_Game*, Hades_Sprite))
{
    Hades_Sprite_* sprite_ = game->sprites[sprite];
    sprite_->Update = Update;
}

void Hades_MoveSprite(Hades_Game* game, Hades_Sprite sprite, int dx, int dy)
{
    Hades_Sprite_* sprite_ = game->sprites[sprite];
    sprite_->dst->x += dx;
    sprite_->dst->y += dy;
}

// --- Private Interface ---

void Hades_RenderSprite(Hades_Game* game, Hades_Sprite_* sprite)
{
    SDL_RenderCopy(game->renderer, game->textures[sprite->texture],
                   sprite->src, sprite->dst);
}

void Hades_DestroySpriteMap(Hades_Sprite_* sprites[], size_t* size)
{
    for (int i = 0; i < Hades_MaxBuckets; i++) {
        while (sprites[i]) {
            Hades_Sprite_* temp = sprites[i];
            sprites[i] = temp->next;
            if (temp->src) {
                free(temp->src);
            }
            if (temp->dst) {
                free(temp->dst);
            }
            free(temp);
        }
    }
    *size = 0;
}

Hades_Sprite_* Hades_GetSprite(Hades_Sprite_* sprites[], Hades_Sprite id,
                               Hades_Sprite_** prevptr)
{
    Hades_SpriteIterator* iter = Hades_IterateSprites(sprites);

    Hades_Sprite_* prev = NULL;
    Hades_Sprite_* current = NULL;
    while (iter) {
        current = Hades_NextSprite_(&iter);

        if (current->id == id) {
            if (prevptr) {
                *prevptr = prev;
            }
            break;
        }
        prev = current;
    }
    Hades_CloseSpriteIterator(&iter);
    return current;
}

size_t Hades_NextSpriteID(Hades_Game* game)
{
    return (game->current_sprite)++;
}

Hades_SpriteIterator* Hades_IterateSprites(Hades_Sprite_* sprites[])
{
    Hades_SpriteIterator* head = NULL;
    Hades_SpriteIterator* tail = NULL;

    for (int i = 0; i < Hades_MaxBuckets; i++) {
        Hades_Sprite_* current = sprites[i];
        while (current) {

            Hades_SpriteIterator* temp = (Hades_SpriteIterator*)
                malloc(sizeof(Hades_SpriteIterator));
            temp->sprite = current;
            temp->next = NULL;

            if (!tail) {
                head = temp;
            } else {
                tail->next = temp;
            }
            tail = temp;

            current = current->next;
        }
    }
    return head;
}

void Hades_CloseSpriteIterator(Hades_SpriteIterator** iter)
{
    while (*iter) {
        Hades_SpriteIterator* temp = *iter;
        *iter = temp->next;
        free(temp);
    }
}

Hades_Sprite_* Hades_NextSprite_(Hades_SpriteIterator** iter)
{
    Hades_SpriteIterator* temp = *iter;
    Hades_Sprite_* sprite = temp->sprite;
    *iter = temp->next;
    free(temp);
    return sprite;
}
