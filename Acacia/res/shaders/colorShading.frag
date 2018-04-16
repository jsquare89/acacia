#version 450

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

//uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;
	//texture(u_Texture, TextCoord);
	//mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
}
