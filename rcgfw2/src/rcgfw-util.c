#include "rcgfw.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *RcgfwReadFile(const char *const path)
{
	FILE *fp = fopen(path, "r");

	fseek(fp, 0L, SEEK_END);
	rcgfw_size_t fsize = ftell(fp);
	rewind(fp);

	char *src = calloc(fsize, sizeof(char));
	fread(src, fsize, 1, fp);

	fclose(fp);

	return (const char*) src;
}

void RcgfwFreeFileData(const char *src)
{
	free((void*) src);
	src = NULL;
}

void __rcgfw__shift_array_left(rcgfw_uint32_t *arr, int endIndex)
{
	rcgfw_uint32_t i = RCGFW_ARR_SIZE(arr, rcgfw_uint32_t);
	rcgfw_uint32_t temp;

	for(; i > endIndex; i--)
	{
		arr[i - 1] = arr[i];
		if(i + 1 > RCGFW_ARR_SIZE(arr, rcgfw_uint32_t))
			arr[i] = 0;
		else
			arr[i] = arr[i + 1];
	} 
}

void __rcgfw__shift_array_right(rcgfw_uint32_t *arr, int endIndex)
{
	rcgfw_uint32_t i = 0;
	rcgfw_uint32_t temp;

	for(; i < RCGFW_ARR_SIZE(arr, rcgfw_uint32_t); i++)
	{
		temp = arr[i];
		arr[i + 1] = temp;
		if(i - 1 < 0)
			arr[i] = 0;
		else
			arr[i] = arr[i - 1];
	}
}