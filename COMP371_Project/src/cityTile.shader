#version 330 core
in vec2 TexCoord;
in vec3 pos;
in float texType;
out vec4 color;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform sampler2D ourTexture3;
void main()
{
float col = pos.y/3;
if(col > 1.0f)
col = 1.0f;
float col2 = col;
if(col2 >= 0.01f)
col2 = 1.0f;
//color = vec4(col2, col, col2, 1.0f);
if(texType == 0.0f)
color = texture(ourTexture1, TexCoord);
if(texType == 1.0f)
color = texture(ourTexture2, TexCoord)  * vec4(col, col2, col, 1.0f);
if(texType == 2.0f)
color = texture(ourTexture3, TexCoord);
}