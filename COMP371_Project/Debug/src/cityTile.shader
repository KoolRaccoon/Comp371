#version 330 core
in vec2 TexCoord;
in vec3 pos;
out vec4 color;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	float col = pos.y/3;
	if(col > 1.0f)
		col = 1.0f;
	float col2 = col;
	if(col2 >= 0.01f)
		col2 = 1.0f;
	color = vec4(col, col2, col, 1.0f);

    //color = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 2.0f);
    //color = texture(texture1, TexCoord);
}