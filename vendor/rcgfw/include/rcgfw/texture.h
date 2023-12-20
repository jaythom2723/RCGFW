#ifndef RCGFW_TEXTURE_H
#define RCGFW_TEXTURE_H

#include "defs.h"

void RcgfwTextureCreate(RcgfwTexture texture, const char *const src);
void RcgfwTextureBind(RcgfwTexture texture);
void RcgfwTextureDelete(RcgfwTexture texture);

#endif /* RCGFW_TEXTURE_H */