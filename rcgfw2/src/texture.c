#include "texture.h"

#include <stdlib.h>

#include <glad/glad.h>

void RcgfwTextureCreate(RcgfwTexture texture, const char *const src)
{
	glGenTextures(1, &texture[RCGFW_TEX_GLTEX]);
	glBindTexture(GL_TEXTURE_2D, texture[RCGFW_TEX_GLTEX]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture[RCGFW_TEX_WIDTH], texture[RCGFW_TEX_HEIGHT], 0, GL_RGBA, GL_UNSIGNED_BYTE, src);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void RcgfwTextureBind(RcgfwTexture texture)
{
	if(texture == NULL)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		return;
	}

	glBindTexture(GL_TEXTURE_2D, texture[RCGFW_TEX_GLTEX]);
}

void RcgfwTextureDelete(RcgfwTexture texture)
{
	glDeleteTextures(1, &texture[RCGFW_TEX_GLTEX]);
	free(texture);
}