#include "hades_objset.h"

void Hades_ClearObjSet(Hades_ObjSetNode* set[], size_t* size)
{
    for (int i = 0; i < Hades_MaxBuckets; i++) {
        Hades_ObjSetNode* top = set[i];
        while (top) {
            Hades_ObjSetNode* tmp = top;
            top = top->next;
            free(tmp);
        }
    }
    if (size) {
        *size = 0;
    }
}

bool Hades_SetHasObj(Hades_ObjSetNode* set[], size_t id)
{
    Hades_ObjSetNode* obj = NULL;
    obj = Hades_GetObjNodeFromSet(set, id, NULL);
    if (obj) {
        return true;
    }
    return false;
}

bool Hades_AddObjToSet(Hades_ObjSetNode* set[], size_t* size, size_t id)
{
    if (Hades_GetObjNodeFromSet(set, id, NULL)) {
        return false;
    }

    int i = id % Hades_MaxBuckets;
    Hades_ObjSetNode copy = {id, set[i]};
    set[i] = (Hades_ObjSetNode*) malloc(sizeof(Hades_ObjSetNode));
    memcpy(set[i], &copy, sizeof(Hades_ObjSetNode));
    *size += 1;
    return true;
}

bool Hades_RmObjFromSet(Hades_ObjSetNode* set[], size_t* size, size_t id)
{
    Hades_ObjSetNode* node = NULL,
                    * prev = NULL;
    node = Hades_GetObjNodeFromSet(set, id, &prev);
    if (!node) {
        return false;
    }
    if (prev) {
        prev->next = node->next;
    } else {
        set[id % Hades_MaxBuckets] = node->next;
    }
    free(node);
    *size -= 1;
    return true;
}

Hades_ObjSetNode*
Hades_GetObjNodeFromSet(Hades_ObjSetNode* set[], size_t id,
                        Hades_ObjSetNode** prevptr)
{
    int i = id % Hades_MaxBuckets;
    Hades_ObjSetNode* curr = set[i],
                    * prev = NULL;
    while (curr) {
        if (curr->id == id) {
            if (prevptr) {
                *prevptr = prev;
            }
            return curr;
        }
        prev = curr;
        curr = curr->next;
    }
    return NULL;
}
