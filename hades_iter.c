#include "hades_iter.h"
#include <stdlib.h>
#include <string.h>

void Hades_CloseIter(Hades_Iter* iter)
{
    while (iter->top) {
        Hades_IterNode* tmp = iter->top;
        iter->top = iter->top->next;
        free(tmp);
    }
    free(iter);
}

bool Hades_IterHasNext(Hades_Iter* iter)
{
    return iter->curr != NULL;
}

void* Hades_NextFromIter(Hades_Iter* iter)
{
    void* data = iter->curr->data;
    iter->curr = iter->curr->next;
    return data;
}

Hades_Iter* Hades_CpIter(Hades_Iter* itercpy)
{
    Hades_Iter* iter = (Hades_Iter*) malloc(sizeof(Hades_Iter));
    memcpy(iter, itercpy, sizeof(Hades_Iter));
    return iter;
}
