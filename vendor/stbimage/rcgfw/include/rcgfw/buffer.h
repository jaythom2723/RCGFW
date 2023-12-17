#ifndef RCGFW_BUFFER_H
#define RCGFW_BUFFER_H

#include "defs.h"
#include "types.h"

void rcgfwCreateBuffer(float *data, RCGFWsize sizedata);
void rcgfwUnbindBuffers(void);
void rcgfwBindBuffer(void *offset);

#endif