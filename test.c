#include <stdio.h>
#include <SDL2/SDL.h>
#include "hades_game.h"
#include "hades_structure.h"
#include "hades_texture.h"
#include "hades_sprite.h"
#include "hades_object.h"
#include "hades_error.h"

enum Test_Textures {
    Test_HelloTexture=0, Test_RectTexture=1
};

// R1 Functions

void Test_R1SetTexture(SDL_Texture* texture)
{
    SDL_SetTextureColorMod(texture, 255, 0, 0);
}

void Test_R1OnCollisionEnter(Hades_Game* game, Hades_Object this,
                             Hades_Object other)
{
    for (int i = 1; i <= 10; i++) {
        printf("%d\n", i);
    }
}

void Test_R1OnCollisionStay(Hades_Game* game, Hades_Object this,
                            Hades_Object other)
{
    puts("Kablam!");
}

void Test_R1OnCollisionExit(Hades_Game* game, Hades_Object this,
                            Hades_Object other)
{
    for (int i = 10; i > 0; i--) {
        printf("%d\n", i);
    }
}

void Test_R1UpdateSprite(Hades_Game* game, Hades_Sprite sprite)
{
    Hades_MoveSprite(game, sprite, 2, 0);
}

void Test_R1UpdateObject(Hades_Game* game, Hades_Object object)
{
    Hades_MoveObjectBy(game, object, 2, 0);
}

// R2 Functions

void Test_R2SetTexture(SDL_Texture* texture)
{
    SDL_SetTextureColorMod(texture, 0, 0, 255);
}

void Test_R2OnCollisionStay(Hades_Game* game, Hades_Object this,
                            Hades_Object other)
{
    puts("Kapow!");
}

// Main Game

void Test_Start(Hades_Game* game) {
    Hades_Color green = {0, 255, 0};

    Hades_LoadTexture(game, "hello.png", NULL);
    Hades_LoadTexture(game, "square.png", &green);

    Hades_CreateSprite(game, Test_HelloTexture, NULL, NULL);

    size_t r1_size = 64;
    SDL_Rect r1_rect = {100, 40, r1_size, r1_size};
    Hades_Sprite r1_spr;
    r1_spr = Hades_CreateSprite(game, Test_RectTexture, NULL, &r1_rect);
    Hades_SetSpriteTextureFunction(game, r1_spr, &Test_R1SetTexture);
    Hades_SetSpriteUpdateFunction(game, r1_spr, &Test_R1UpdateSprite);

    Hades_Object r1_obj;
    r1_obj = Hades_CreateRectObject(game, r1_rect.x, r1_rect.y,
                                    r1_rect.w, r1_rect.h);

    Hades_SetObjectCollisionEnterFunction(game, r1_obj,
                                          &Test_R1OnCollisionEnter);
    Hades_SetObjectCollisionStayFunction(game, r1_obj,
                                         &Test_R1OnCollisionStay);
    Hades_SetObjectCollisionExitFunction(game, r1_obj,
                                         &Test_R1OnCollisionExit);
    Hades_SetObjectUpdateFunction(game, r1_obj, &Test_R1UpdateObject);

    size_t r2_size = 40;
    SDL_Rect r2_rect = {200, 40, r2_size, r2_size};
    Hades_Sprite r2_spr;
    r2_spr = Hades_CreateSprite(game, Test_RectTexture, NULL, &r2_rect);
    Hades_SetSpriteTextureFunction(game, r2_spr, &Test_R2SetTexture);

    Hades_Object r2_obj;
    r2_obj = Hades_CreateRectObject(game, r2_rect.x, r2_rect.y,
                                    r2_size, r2_size);
    Hades_SetObjectCollisionStayFunction(game, r2_obj, &Test_R2OnCollisionStay);

    Hades_SetFramerateCap(game, 30);
}

int main(int argc, char* argv[]) {
    Hades_Game* test = Hades_CreateGame("Test", 640, 480);
    if (!test) {
        puts(Hades_GetError());
        return 0;
    }
    test->Start = &Test_Start;
    if (!Hades_RunGame(test)) {
        puts(Hades_GetError());
    }
    Hades_DestroyGame(test);
    return 0;
}
