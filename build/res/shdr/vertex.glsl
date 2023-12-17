#version 330 core

layout (location=0) in vec2 aPos;
layout (location=1) in vec3 aColor;

out vec4 color;

void main()
{
	gl_Position = vec4(aPos, 1.0, 0.0);
	color = vec4(aColor, 1.0);
}