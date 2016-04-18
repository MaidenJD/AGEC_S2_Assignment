#version 120

in vec3 coord3d;

uniform mat4 transformation;

void main(void)
{
	gl_Position = transformation * vec4(coord3d, 1.0);
}