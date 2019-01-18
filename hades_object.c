#include "hades_object.h"
#include "hades_objstruct.h"
#include "hades_objset.h"
#include "hades_game.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

Hades_Object Hades_NewRectObj(Hades_Game* game, int x, int y,
                              size_t w, size_t h)
{
    Hades_ObjStruct copy = {
        Hades_NextObjID(game), x, y, w, h,
        NULL, 0, {NULL}, NULL, NULL, NULL, NULL
    };
    Hades_ObjStruct* obj;
    obj = (Hades_ObjStruct*) malloc(sizeof(Hades_ObjStruct));
    memcpy(obj, &copy, sizeof(Hades_ObjStruct));

    int i = obj->id % Hades_MaxBuckets;
    obj->next = game->objs[i];
    game->objs[i] = obj;

    game->objc += 1;
    return obj->id;
}

bool Hades_RmObj(Hades_Game* game, Hades_Object id)
{
    if (!game) {
        return false;
    }
    Hades_ObjStruct* prev = NULL,
                   * obj = Hades_GetObjStructFromMap(game->objs, id, &prev);
    if (!obj) {
        return false;
    }
    if (prev) {
        prev->next = obj->next;
    } else {
        game->objs[id % Hades_MaxBuckets] = obj->next;
    }
    Hades_ClearObjSet(obj->clsnv, &obj->clsnc);
    free(obj);
    game->objc -= 1;
    return true;
}

bool Hades_DefObjClsnEnter(Hades_Game* game, Hades_Object id,
                           Hades_ClsnFunc OnClsnEnter)
{
    Hades_ObjStruct* obj = Hades_GetObjStructFromMap(game->objs, id, NULL);
    if (!obj) {
        return false;
    }
    obj->OnClsnEnter = OnClsnEnter;
    return true;
}

bool Hades_DefObjClsnStay(Hades_Game* game, Hades_Object id,
                          Hades_ClsnFunc OnClsnStay)
{
    Hades_ObjStruct* obj = Hades_GetObjStructFromMap(game->objs, id, NULL);
    if (!obj) {
        return false;
    }
    obj->OnClsnStay = OnClsnStay;
    return true;
}

bool Hades_DefObjClsnExit(Hades_Game* game, Hades_Object id,
                          Hades_ClsnFunc OnClsnExit)
{
    Hades_ObjStruct* obj = Hades_GetObjStructFromMap(game->objs, id, NULL);
    if (!obj) {
        return false;
    }
    obj->OnClsnExit = OnClsnExit;
    return true;
}

bool Hades_DefObjUpdate(Hades_Game* game, Hades_Object id,
                        Hades_ObjFunc Update)
{
    Hades_ObjStruct* obj = Hades_GetObjStructFromMap(game->objs, id, NULL);
    if (!obj) {
        return false;
    }
    obj->Update = Update;
    return true;
}

bool Hades_MvObjBy(Hades_Game* game, Hades_Object id, int dx, int dy)
{
    Hades_ObjStruct* obj = Hades_GetObjStructFromMap(game->objs, id, NULL);
    if (!obj) {
        return false;
    }
    obj->x += dx;
    obj->y += dy;
    return true;
}

bool Hades_MvObjTo(Hades_Game* game, Hades_Object id, int x, int y)
{
    Hades_ObjStruct* obj = Hades_GetObjStructFromMap(game->objs, id, NULL);
    if (!obj) {
        return false;
    }
    obj->x = x;
    obj->y = y;
    return true;
}
