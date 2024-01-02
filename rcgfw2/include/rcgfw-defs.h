#ifndef RCGFW_DEFS_H
#define RCGFW_DEFS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define RCGFW_RES_DIR 				"./res"
#define RCGFW_SHDR_DIR 				RCGFW_RES_DIR"/shdr/"
#define RCGFW_IMG_DIR 				RCGFW_RES_DIR"/img/"

#define RCGFW_TEX_WIDTH 			0
#define RCGFW_TEX_HEIGHT 			1
#define RCGFW_TEX_CHANNELS 			2
#define RCGFW_TEX_GLTEX 			3

#define RCGFW_TRUE 					1
#define RCGFW_FALSE 				0

#define RCGFW_NEW_TEXTURE			calloc(4, sizeof(rcgfw_uint32_t))

typedef long unsigned int 			rcgfw_size_t;
typedef unsigned int 				rcgfw_uint32_t;
typedef unsigned short 				rcgfw_uint16_t;
typedef unsigned char 				rcgfw_uint8_t;

typedef struct rcgfw_state 			rcgfw_state_t;
typedef rcgfw_uint32_t 				rcgfw_shader_t, rcgfw_program_t, rcgfw_vbo_t, rcgfw_vao_t, rcgfw_ibo_t;
typedef rcgfw_uint32_t 				*rcgfw_texture_t;

typedef enum rcgfw_list_types
{
	RCGFW_SHADER,
	RCGFW_TEXTURE
} rcgfw_list_type_t;

typedef enum rcgfw_shader_types
{
	RCGFW_FRAGMENT_SHADER 			= 0X8B30,
	RCGFW_VERTEX_SHADER 			= 0x8B31,
	RCGFW_GEOMETRY_SHADER 			= 0x8DD9,
	RCGFW_COMPUTE_SHADER 			= 0x91B9,
	RCGFW_TESS_CONTROL_SHADER 		= 0x8E88,
	RCGFW_TESS_EVALUATION_SHADER	= 0x8E87
} rcgfw_shader_type_t;

#ifdef __rcgfw__use_error_handler
typedef enum rcgfw_error_codes
{
	__RCGFW__ERR_MEM_ALLOC_FAILURE 			= -1,
	__RCGFW__ERR_SHDR_COMP_FAILURE			= -2,
	__RCGFW__ERR_PGRM_LINK_FAILURE			= -4,
	__RCGFW__ERR_GPU_VAO_INVALID_OP			= -8,
	__RCGFW__ERR_GPU_VBO_INVALID_OP 		= -16,
	__RCGFW__ERR_GPU_IBO_INVALID_OP			= -32,
	__RCGFW__ERR_GLFW_WND_CREATE_FAILURE	= -64,
	__RCGFW__ERR_GLFW_INIT_FAILURE 			= -128,
	__RCGFW__ERR_GLAD_INIT_FAILURE			= -256
} rcgfw_error_code_t;
#endif /* __rcgfw__use_error_handler */

struct rcgfw_state
{
	GLFWwindow *hdl_wnd;
	rcgfw_uint32_t wnd_width, wnd_height;
	char *wnd_title;

	rcgfw_shader_t *shaders;
	rcgfw_shader_t *shaderptr;
	rcgfw_shader_t *shaderend;
	rcgfw_program_t program;

	rcgfw_vao_t vao;
};

typedef void (*RcgfwErrCallback)(struct rcgfw_state *);

#endif /* RCGFW_DEFS_H */
