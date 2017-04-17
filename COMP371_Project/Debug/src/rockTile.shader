#version 330 core

in vec3 pos;

out vec4 color;

void main()
{
	if(pos.y < 0)
		color = vec4(-pos.y, -pos.y, -pos.y, 0.01f);
	else
		color = vec4(pos.y, pos.y, pos.y, 0.01f);
}