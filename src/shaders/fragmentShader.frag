#version 450 core

out vec4 colour;

uniform vec4 uniColour;

void main()
{
	colour = uniColour;
}