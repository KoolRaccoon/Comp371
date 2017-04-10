#version 330 core

in vec3 pos;

out vec4 color;

void main()
{
	color = vec4(1-pos.y, pos.y, 1-pos.y, 0.01f);
}