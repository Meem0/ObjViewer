#version 450

layout (location = 0) in vec3 pos;

uniform mat4 model;

void main()
{
	gl_Position = model * vec4(pos.x, pos.y, pos.z, 1.0);
}
