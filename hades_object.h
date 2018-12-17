#ifndef HADES_OBJECT_H
#define HADES_OBJECT_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct Hades_Object_ Hades_Object_;
typedef struct Hades_ObjectIterator Hades_ObjectIterator;
typedef int Hades_Object;

typedef struct Hades_Game Hades_Game;

typedef void (Hades_CollisionFunction)(Hades_Game*, Hades_Object, Hades_Object);
typedef void (Hades_ObjectUpdateFunction)(Hades_Game*, Hades_Object);

Hades_Object Hades_CreateRectObject(Hades_Game*, int, int, size_t, size_t);
bool Hades_DestroyObject(Hades_Game*, Hades_Object);
bool Hades_SetObjectCollisionStayFunction(Hades_Game*, Hades_Object,
                                          Hades_CollisionFunction*);
bool Hades_SetObjectUpdateFunction(Hades_Game*, Hades_Object,
                                   Hades_ObjectUpdateFunction*);

bool Hades_MoveObjectBy(Hades_Game*, Hades_Object, int, int);
bool Hades_MoveObjectTo(Hades_Game*, Hades_Object, int, int);

void Hades_DestroyObjectMap(Hades_Object_*[], size_t*);
Hades_Object_* Hades_GetObject(Hades_Object_*[], Hades_Object, Hades_Object_**);
Hades_Object Hades_NextObject(Hades_Game*);

bool Hades_CollidesWith(const Hades_Object_, const Hades_Object_);

Hades_ObjectIterator* Hades_IterateObjects(Hades_Object_*[]);
void Hades_CloseObjectIterator(Hades_ObjectIterator**);
Hades_Object_* Hades_NextObject_(Hades_ObjectIterator**);
Hades_ObjectIterator* Hades_CopyObjectIterator(Hades_ObjectIterator*);

#endif
