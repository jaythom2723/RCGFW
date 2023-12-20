#ifndef RCGFW_RESOURCE_H
#define RCGFW_RESOURCE_H

#include "defs.h"

const char *RcgfwLoad(const char *path);
const char *RcgfwLoadImage(RcgfwTexture texture, const char *path);

void RcgfwFreeImage(const char *imgData);

#endif /* RCGFW_RESOURCE_H */