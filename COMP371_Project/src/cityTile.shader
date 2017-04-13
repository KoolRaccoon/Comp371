#version 330 core
in vec2 TexCoord;
in vec3 pos;
out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
	float col = pos.y/3;
	if(col > 1.0f)
		col = 1.0f;
	color = vec4(col, col, col, 1.0f);
    //color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 2.0f);
}