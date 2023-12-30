#ifndef RCGFW_ENT_H
#define RCGFW_ENT_H

#include "defs.h"

#include <cglm/cglm.h>

typedef vec3 RcgfwCompColor;
typedef mat4 RcgfwCompTransform;
typedef float* RcgfwVertexData;

typedef struct RcgfwBaseEntity
{
	RcgfwTexture texture;
	RcgfwCompTransform transform;
	RcgfwCompColor color;
} RcgfwBaseEntity;

RcgfwBaseEntity *RcgfwEntityCreate(const char *const texture_name);
void RcgfwEntityDestroy(RcgfwBaseEntity *ent);

void RcgfwEntityDraw(RcgfwBaseEntity *ent);

void RcgfwEntitySetTransform(RcgfwCompTransform transform, RcgfwBaseEntity *ent);
void RcgfwEntitySetColor(RcgfwCompColor color, RcgfwBaseEntity *ent);

#endif /* RCGFW_ENT_H */