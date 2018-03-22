
#version 450

in vec3 textureCoords;
out vec4 out_Color;

unifrom samplerCube cubeMap;

void main(void){
	out_Color = texture(cubeMap, textureCoords);
}
