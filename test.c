#include <stdio.h>
#include <SDL2/SDL.h>
#include "hades_game.h"
#include "hades_texture.h"
#include "hades_sprite.h"
#include "hades_object.h"
#include "hades_error.h"

// R1 Functions

void Test_R1SetTexture(SDL_Texture* tex)
{
    SDL_SetTextureColorMod(tex, 255, 0, 0);
}

void Test_R1OnClsnEnter(Hades_Game* game, Hades_Object* this,
                        Hades_Object* other)
{
    for (int i = 1; i <= 10; i++) {
        printf("%d\n", i);
    }
}

void Test_R1OnClsnStay(Hades_Game* game, Hades_Object* this,
                       Hades_Object* other)
{
    puts("Kablam!");
}

void Test_R1OnClsnExit(Hades_Game* game, Hades_Object* this,
                       Hades_Object* other)
{
    for (int i = 10; i > 0; i--) {
        printf("%d\n", i);
    }
}

void Test_R1UpdateSprite(Hades_Game* game, Hades_Sprite* sprite)
{
    Hades_MvSprBy(*sprite, 2, 0);
}

void Test_R1UpdateObject(Hades_Game* game, Hades_Object* object)
{
    Hades_MvObjBy(object, 2, 0);
}

// R2 Functions

void Test_R2SetTexture(SDL_Texture* tex)
{
    SDL_SetTextureColorMod(tex, 0, 0, 255);
}

void Test_R2OnClsnStay(Hades_Game* game, Hades_Object* this,
                       Hades_Object* other)
{
    puts("Kapow!");
}

// Main Game

void Test_Start(Hades_Game* game) {
    Hades_Color green = {0, 255, 0};

    size_t heltex = Hades_LoadTex(game, "hello.png", NULL);
    size_t sqrtex = Hades_LoadTex(game, "square.png", &green);

    Hades_NewSpr(game, heltex, NULL, NULL);

    size_t r1_size = 64;
    SDL_Rect r1_rect = {100, 40, r1_size, r1_size};
    Hades_Sprite* r1_spr = Hades_NewSpr(game, sqrtex, NULL, &r1_rect);
    r1_spr->SetTexture = Test_R1SetTexture;
    r1_spr->Update = Test_R1UpdateSprite;

    Hades_Object* r1_obj =
        Hades_NewRectObj(game, r1_rect.x, r1_rect.y, r1_rect.w, r1_rect.h);
    r1_obj->OnClsnEnter = Test_R1OnClsnEnter;
    r1_obj->OnClsnStay = Test_R1OnClsnStay;
    r1_obj->OnClsnExit = Test_R1OnClsnExit;
    r1_obj->Update = Test_R1UpdateObject;

    size_t r2_size = 40;
    SDL_Rect r2_rect = {200, 40, r2_size, r2_size};
    Hades_Sprite* r2_spr = Hades_NewSpr(game, sqrtex, NULL, &r2_rect);
    r2_spr->SetTexture = Test_R2SetTexture;

    Hades_Object* r2_obj =
        Hades_NewRectObj(game, r2_rect.x, r2_rect.y, r2_size, r2_size);
    r2_obj->OnClsnStay = Test_R2OnClsnStay;

    Hades_SetFramerateCap(game, 30);
}

int main(int argc, char* argv[]) {
    Hades_Game* test = Hades_NewGame("Test", 640, 480);
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
