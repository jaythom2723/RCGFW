#include "resource.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

const char *RcgfwLoad(const char *path)
{
	/* get the size of the file */
	FILE *file = fopen(path, "r");
	assert(file != NULL);

	fseek(file, 0l, SEEK_END);
	size_t size = ftell(file);
	rewind(file);

	char *src = calloc(size, sizeof(char));
	fread(src, 1, size, file);
	assert(src != NULL);

	return (const char*) src;
}