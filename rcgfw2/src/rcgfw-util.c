#include "rcgfw.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

RcgfwUInt64 GetArraySize(void *arr, RcgfwUInt64 size)
{
	return size / sizeof(arr[0]);
}

const char *const GetPath(const char *name, const char *ext, const char *path)
{
	char *ret = calloc(strlen(name) + strlen(ext) + strlen(path) + 1, sizeof(char));
	strcpy(ret, path);
	strcat(ret, name);
	strcat(ret, ext);
	return (const char *const) ret;
}