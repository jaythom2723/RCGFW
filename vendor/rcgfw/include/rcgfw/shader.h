#ifndef RCGFW_SHADER_H
#define RCGFW_SHADER_H

#include "defs.h"

void RcgfwShaderCreate(const char *src, RcgfwShaderType type);
const char *const RcgfwShaderLoad(const char *const path);
void RcgfwShaderDelete(void *offset);

void RcgfwProgramAttachShader(void *offset);
void RcgfwProgramDetachShader(void *offset);
void RcgfwProgramLink(void);
void RcgfwProgramUse(void);

#endif /* RCGFW_SHADER_H */