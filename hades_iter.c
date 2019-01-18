#include "hades_iter.h"
#include <stdlib.h>
#include <string.h>

Hades_Iter* Hades_NewIter(Hades_Consumer FreeData)
{
    Hades_Iter cpy = {NULL, FreeData};
    Hades_Iter* iter = (Hades_Iter*) malloc(sizeof(Hades_Iter));
    memcpy(iter, &cpy, sizeof(Hades_Iter));
    return iter;
}

void Hades_CloseIter(Hades_Iter* iter)
{
    while (iter->top) {
        iter->FreeData(iter->top->data);
        Hades_IterNode* tmp = iter->top;
        iter->top = iter->top->next;
        free(tmp);
    }
    free(iter);
}

bool Hades_IterHasNext(Hades_Iter* iter)
{
    return iter->top != NULL;
}

void* Hades_NextFromIter(Hades_Iter* iter)
{
    void* data = iter->top->data;
    Hades_IterNode* tmp = iter->top;
    iter->top = iter->top->next;
    free(tmp);
    return data;
}
