#include "resource.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stbimage/stb_image.h>

const char *RcgfwLoad(const char *path)
{
	/* get the size of the file */
	FILE *file = fopen(path, "r");
	(void) assert(file != NULL);

	fseek(file, 0l, SEEK_END);
	size_t size = ftell(file);
	rewind(file);

	char *src = calloc(size, sizeof(char));
	fread(src, 1, size, file);
	(void) assert(src != NULL);

	return (const char*) src;
}

const char *RcgfwLoadImage(RcgfwTexture texture, const char *path)
{
	unsigned char *img = stbi_load(path, &texture[RCGFW_TEX_WIDTH], &texture[RCGFW_TEX_HEIGHT], &texture[RCGFW_TEX_CHANNELS], 0);
	(void) assert(img != NULL);
	return img;
}

void RcgfwFreeImage(const char *imgData)
{
	stbi_image_free((void*) imgData);
}