#ifndef RCGFW_UTILS_H
#define RCGFW_UTILS_H

/*
	sb = Size Bytes
	esb = Element Size Bytes
*/
#define RCGFW_ARR_SIZE(arr, elemType) sizeof(arr) / sizeof(elemType)

const char *RcgfwReadFile(const char *const path);
void RcgfwFreeFileData(const char *src);

#endif /* RCGFW_UTILS_H */