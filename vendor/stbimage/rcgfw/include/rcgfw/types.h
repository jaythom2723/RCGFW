#ifndef RCGFW_TYPES_H
#define RCGFW_TYPES_H

typedef float RCGFWcolor[3];

typedef unsigned char RCGFWu8;
typedef RCGFWu8 RCGFWbool;
typedef unsigned short RCGFWu16;
typedef unsigned int RCGFWu32;
typedef unsigned long RCGFWu64;
typedef unsigned long long RCGFWsize;

typedef RCGFWu32 RCGFWvertexbuffer;
typedef RCGFWu32 RCGFWvertexarray;

typedef enum rcgfw_shader_type
{
    RCGFW_FRAGMENT_SHADER = 0x8B30,
    RCGFW_VERTEX_SHADER,
    RCGFW_GEOMETRY_SHADER = 0x8DD9,
    RCGFW_COMPUTE_SHADER = 0x91B9
} RCGFWshaderType;

typedef RCGFWu32 RCGFWshader;
typedef RCGFWu32 RCGFWshaderprogram;

typedef struct rcgfw_display_props
{
    unsigned int width, height;
    char *title;
} RCGFWdisplayprops;

typedef struct rcgfw_display RCGFWdisplay;
typedef struct rcgfw_state RCGFWstate;

#endif