#include "hades_object.h"
#include "hades_structure.h"
#include "hades_game.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

Hades_Object Hades_CreateRectObject(Hades_Game* game, int x, int y,
                                    size_t w, size_t h)
{
    Hades_Object_ copy = {Hades_NextObject(game), NULL, x, y, w, h, NULL};
    Hades_Object_* object = (Hades_Object_*) malloc(sizeof(Hades_Object_));
    memcpy(object, &copy, sizeof(Hades_Object_));

    int i = object->id % Hades_MaxBuckets;
    object->next = game->objects[i];
    game->objects[i] = object;

    game->object_count += 1;
    return object->id;
}

bool Hades_DestroyObject(Hades_Game* game, Hades_Object id)
{
    if (!game) {
        return false;
    }
    Hades_Object_* prev = NULL;
    Hades_Object_* object = Hades_GetObject(game->objects, id, &prev);
    if (!object) {
        return false;
    }
    if (prev) {
        prev->next = object->next;
    }
    free(object);
    game->object_count -= 1;
    return true;
}

bool
Hades_SetObjectCollisionStayFunction(Hades_Game* game, Hades_Object id,
                                     Hades_CollisionFunction* OnCollisionStay)
{
    Hades_Object_* object = Hades_GetObject(game->objects, id, NULL);
    if (!object) {
        return false;
    }
    object->OnCollisionStay = OnCollisionStay;
    return true;
}

bool Hades_SetObjectUpdateFunction(Hades_Game* game, Hades_Object id,
                                   Hades_ObjectUpdateFunction* Update)
{
    Hades_Object_* object = Hades_GetObject(game->objects, id, NULL);
    if (!object) {
        return false;
    }
    object->Update = Update;
    return true;
}

bool Hades_MoveObjectBy(Hades_Game* game, Hades_Object id, int dx, int dy)
{
    Hades_Object_* object = Hades_GetObject(game->objects, id, NULL);
    if (!object) {
        return false;
    }
    object->x += dx;
    object->y += dy;
    return true;
}

bool Hades_MoveObjectTo(Hades_Game* game, Hades_Object id, int x, int y)
{
    Hades_Object_* object = Hades_GetObject(game->objects, id, NULL);
    if (!object) {
        return false;
    }
    object->x = x;
    object->y = y;
    return true;
}

void Hades_DestroyObjectMap(Hades_Object_* objects[], size_t* size)
{
    for (int i = 0; i < Hades_MaxBuckets; i++) {
        while (objects[i]) {
            Hades_Object_* temp = objects[i];
            objects[i] = temp->next;
            free(temp);
        }
        objects[i] = NULL;
    }
    *size = 0;
}

Hades_Object_* Hades_GetObject(Hades_Object_* objects[], Hades_Object id,
                               Hades_Object_** prevptr)
{
    Hades_Object_* prev = NULL,
                 * object = NULL;
    Hades_ObjectIterator* iter = Hades_IterateObjects(objects);
    while (iter) {
        object = Hades_NextObject_(&iter);
        if (object->id == id) {
            if (prevptr) {
                *prevptr = prev;
            }
            break;
        }
        prev = object;
    }
    Hades_CloseObjectIterator(&iter);
    return object;
}

Hades_Object Hades_NextObject(Hades_Game* game)
{
    return (game->current_object)++;
}

bool Hades_CollidesWith(const Hades_Object_ this, const Hades_Object_ other)
{
    return (this.x + this.w) > other.x && this.x < (other.x + other.w) &&
           (this.y + this.h) > other.y && this.y < (other.y + other.h);
}

Hades_ObjectIterator* Hades_IterateObjects(Hades_Object_* objects[])
{
    Hades_ObjectIterator* head = NULL,
                        * tail = NULL;

    for (int i = 0; i < Hades_MaxBuckets; i++) {
        Hades_Object_* current = objects[i];
        while (current) {
            Hades_ObjectIterator* temp = (Hades_ObjectIterator*)
                malloc(sizeof(Hades_ObjectIterator));
            temp->object = current;
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

void Hades_CloseObjectIterator(Hades_ObjectIterator** iter)
{
    while (*iter) {
        Hades_ObjectIterator* temp = *iter;
        *iter = temp->next;
        free(temp);
    }
}

Hades_Object_* Hades_NextObject_(Hades_ObjectIterator** iter)
{
    Hades_ObjectIterator* temp = *iter;
    Hades_Object_* object = temp->object;
    *iter = temp->next;
    free(temp);
    return object;
}

Hades_ObjectIterator* Hades_CopyObjectIterator(Hades_ObjectIterator* iter)
{
    Hades_ObjectIterator* head = NULL,
                        * tail = NULL,
                        * current = iter;

    while (current) {
        Hades_ObjectIterator* temp = (Hades_ObjectIterator*)
            malloc(sizeof(Hades_ObjectIterator));
        temp->object = current->object;
        temp->next = current->next;

        if (!head) {
            head = temp;
        } else {
            tail->next = temp;
        }
        tail = temp;

        current = current->next;
    }
    return head;
}
