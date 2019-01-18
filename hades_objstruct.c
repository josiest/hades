#include "hades_objstruct.h"
#include "hades_objset.h"
#include "hades_game.h"
#include <string.h>
#include <stdlib.h>

void Hades_ClearObjMap(Hades_ObjStruct* map[], size_t* size)
{
    for (int i = 0; i < Hades_MaxBuckets; i++) {
        while (map[i]) {
            Hades_ObjStruct* tmp = map[i];
            map[i] = tmp->next;
            Hades_ClearObjSet(tmp->clsnv, &tmp->clsnc);
            free(tmp);
        }
        map[i] = NULL;
    }
    *size = 0;
}

Hades_ObjStruct*
Hades_GetObjStructFromMap(Hades_ObjStruct* map[], Hades_Object id,
                          Hades_ObjStruct** prevptr)
{
    Hades_ObjStruct* prev = NULL,
                   * obj = NULL;
    Hades_ObjStructIter* iter = Hades_IterObjMap(map);
    while (iter) {
        obj = Hades_NextObjStructFromIter(&iter);
        if (obj->id == id) {
            if (prevptr) {
                *prevptr = prev;
            }
            break;
        }
        prev = obj;
    }
    Hades_CloseObjStructIter(&iter);
    return obj;
}

Hades_Object Hades_NextObjID(Hades_Game* game)
{
    return (game->next_objID)++;
}

bool Hades_CollidesWith(const Hades_ObjStruct this, const Hades_ObjStruct other)
{
    return (this.x + this.w) > other.x && this.x < (other.x + other.w) &&
           (this.y + this.h) > other.y && this.y < (other.y + other.h);
}

Hades_ObjStructIter* Hades_IterObjMap(Hades_ObjStruct* objv[])
{
    Hades_ObjStructIter* head = NULL,
                       * tail = NULL;

    for (int i = 0; i < Hades_MaxBuckets; i++) {
        Hades_ObjStruct* curr = objv[i];
        while (curr) {
            Hades_ObjStructIter copy = {curr, NULL};
            Hades_ObjStructIter* tmp = (Hades_ObjStructIter*)
                malloc(sizeof(Hades_ObjStructIter));
            memcpy(tmp, &copy, sizeof(Hades_ObjStructIter));

            if (!tail) {
                head = tmp;
            } else {
                tail->next = tmp;
            }
            tail = tmp;

            curr = curr->next;
        }
    }
    return head;
}

void Hades_CloseObjStructIter(Hades_ObjStructIter** iter)
{
    while (*iter) {
        Hades_ObjStructIter* tmp = *iter;
        *iter = tmp->next;
        free(tmp);
    }
}

Hades_ObjStruct* Hades_NextObjStructFromIter(Hades_ObjStructIter** iter)
{
    Hades_ObjStructIter* tmp = *iter;
    Hades_ObjStruct* obj = tmp->obj;
    *iter = tmp->next;
    free(tmp);
    return obj;
}

Hades_ObjStructIter* Hades_CpObjStructIter(Hades_ObjStructIter* iter)
{
    Hades_ObjStructIter* head = NULL,
                       * tail = NULL,
                       * curr = iter;

    while (curr) {
        Hades_ObjStructIter* tmp = (Hades_ObjStructIter*)
            malloc(sizeof(Hades_ObjStructIter));
        memcpy(tmp, curr, sizeof(Hades_ObjStructIter));

        if (!head) {
            head = tmp;
        } else {
            tail->next = tmp;
        }
        tail = tmp;

        curr = curr->next;
    }
    return head;
}
