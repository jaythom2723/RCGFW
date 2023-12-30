#include "ent.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "rcgfw.h"
#include "texture.h"

extern const char *RcgfwLoadImage(RcgfwTexture texture, const char *path);
extern void RcgfwFreeImage(const char *imgData);
extern const char *const GetPath(const char *name, const char *ext, const char *path);

RcgfwBaseEntity *RcgfwCreateEntity(const char *const texture_name)
{
	RcgfwBaseEntity *ret = (RcgfwBaseEntity*) calloc(1, sizeof(RcgfwBaseEntity));
	assert(ret != NULL);

	ret->texture = RCGFW_NEW_TEXTURE;
	const char *const path = GetPath(texture_name, ".png", RCGFW_IMG_DIR);
	const char *data = RcgfwLoadImage(ret->texture, path);
	RcgfwTextureCreate(ret->texture, data);
	RcgfwFreeImage(data);
	free((void*) path);

	return ret;
}

void RcgfwEntityDraw(RcgfwBaseEntity *ent)
{
	RcgfwSetMatrix4("transform", ent->transform);
	RcgfwSetVector3("color", ent->color);
	RcgfwTextureBind(ent->texture);
	RcgfwWindowDraw();
}

void RcgfwEntityDestroy(RcgfwBaseEntity *ent)
{
	RcgfwTextureDelete(ent->texture);
	free(ent);
	ent = NULL;
}

void RcgfwEntitySetTransform(RcgfwCompTransform transform, RcgfwBaseEntity *ent)
{
	glm_mat4_copy(transform, ent->transform);
}

void RcgfwEntitySetColor(RcgfwCompColor color, RcgfwBaseEntity *ent)
{
	glm_vec3_copy(color, ent->color);
}