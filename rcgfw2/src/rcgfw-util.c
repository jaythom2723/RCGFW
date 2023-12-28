#include "rcgfw.h"

#include <stdio.h>

RcgfwUInt64 GetArraySize(void *arr, RcgfwUInt64 size)
{
	return size / sizeof(arr[0]);
}