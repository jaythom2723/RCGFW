#ifndef RCGFW_ENT_H
#define RCGFW_ENT_H

#include "defs.h"

#define RCGFW_X  0
#define RCGFW_Y  1
#define RCGFW_SX 2
#define RCGFW_SY 3
#define RCGFW_RZ 4

typedef float  RcgfwTransformComponent[5];
typedef float* RcgfwVertexData;

typedef struct RcgfwBaseEntity
{
	int id;
	RcgfwTransformComponent transform;
	RcgfwVertexData vertices;
	RcgfwVao vao;
} RcgfwBaseEntity;



#endif /* RCGFW_ENT_H */