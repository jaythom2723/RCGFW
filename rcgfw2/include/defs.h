#ifndef RCGFW_DEFS_H
#define RCGFW_DEFS_H

#define RCGFW_RES_DIR "./res"
#define RCGFW_SHDR_DIR RCGFW_RES_DIR"/shdr/"
#define RCGFW_IMG_DIR RCGFW_RES_DIR"/img/"

#define RCGFW_TRUE 1
#define RCGFW_FALSE 0

typedef unsigned long  RcgfwUInt64;
typedef unsigned int   RcgfwUInt32;
typedef unsigned short RcgfwUInt16;
typedef unsigned char  RcgfwUInt8;

typedef struct RcgfwState RcgfwState;
typedef RcgfwUInt32 RcgfwShader, RcgfwShaderProgram, RcgfwVbo, RcgfwVao;

typedef enum RcgfwShaderTypes
{
	RCGFW_FRAGMENT_SHADER = 0x8B30,
	RCGFW_VERTEX_SHADER = 0x8B31,
	RCGFW_GEOMETRY_SHADER = 0x8DD9,
	RCGFW_COMPUTE_SHADER = 0x91B9,
	RCGFW_TESS_CONTROL_SHADER = 0x8E88,
	RCGFW_TESS_EVALUATION_SHADER = 0x8E87,
} RcgfwShaderType;

typedef enum RcgfwErrorCodes
{
	ERR_MEM_ALLOC_FAILURE = -1,
	ERR_SHDR_COMP_FAILURE = -2,
	ERR_PGRM_LINK_FAILURE = -4,
	ERR_GPU_VAO_INVALID_OP = -8,
	ERR_GPU_VBO_INVALID_OP = -16
} RcgfwErrorCode;

#endif /* RCGFW_DEFS_H */