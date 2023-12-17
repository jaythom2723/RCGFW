#ifndef RCGFW_H
#define RCGFW_H

#include "defs.h"
#include "types.h"
#include "resource.h"

#include "display.h"
#include "shader.h"
#include "program.h"
#include "buffer.h"
#include "arrobj.h"

void rcgfwInit(RCGFWdisplayprops props);
void rcgfwClose(void);
void rcgfwDraw(RCGFWvertexarray vao);

#endif