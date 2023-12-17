#ifndef RCGFW_PROGRAM_H
#define RCGFW_PROGRAM_H

#include "defs.h"
#include "types.h"

RCGFWshaderprogram rcgfwCreateProgram(void);
void rcgfwDestroyProgram(void);
void rcgfwLinkProgram(void);
void rcgfwUseProgram(void);

#endif