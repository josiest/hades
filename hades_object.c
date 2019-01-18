#include "hades_object.h"
#include "hades_objset.h"
#include "hades_hmap.h"
#include "hades_game.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

Hades_Object* Hades_NewRectObj(Hades_Game* game, int x, int y,
                               size_t w, size_t h)
{
    Hades_Object objcpy = {
        Hades_NextObjID(game), x, y, w, h,
        0, {NULL}, NULL, NULL, NULL, NULL
    };
    Hades_Object* obj;
    obj = (Hades_Object*) malloc(sizeof(Hades_Object));
    memcpy(obj, &objcpy, sizeof(Hades_Object));

    void* idp = malloc(sizeof(size_t));
    memcpy(idp, &obj->id, sizeof(size_t));
    Hades_AddToHMap(game->objs, idp, obj);

    return obj;
}

void Hades_FreeObj(void* vobj)
{
    Hades_Object* obj = (Hades_Object*) vobj;
    Hades_ClearObjSet(obj->clsnv, &obj->clsnc);
    free(obj);
}


bool Hades_MvObjBy(Hades_Object* obj, int dx, int dy)
{
    obj->x += dx;
    obj->y += dy;
    return true;
}

bool Hades_MvObjTo(Hades_Object* obj, int x, int y)
{
    obj->x = x;
    obj->y = y;
    return true;
}

size_t Hades_NextObjID(Hades_Game* game)
{
    return (game->next_objID)++;
}

size_t Hades_HashObj(const void* obj)
{
    if (!obj) {
        return 0;
    }
    return ((const Hades_Object*)obj)->id;
}

bool Hades_ObjEq(const void* a, const void* b)
{
    if (!a) {
        return b == NULL;
    }
    if (!b) {
        return false;
    }
    return ((const Hades_Object*)a)->id == ((const Hades_Object*)b)->id;
}

bool Hades_ClsnWith(const Hades_Object this, const Hades_Object other)
{
    return (this.x + this.w) > other.x && this.x < (other.x + other.w) &&
           (this.y + this.h) > other.y && this.y < (other.y + other.h);
}
