#include "hades_stdhash.h"
#include <stdio.h>

size_t Hades_HashID(const void* id)
{
    return *(const size_t*)id % Hades_MaxBuckets;
}

bool Hades_IDEq(const void* a, const void* b)
{
    return *(const size_t*)a == *(const size_t*)b;
}
