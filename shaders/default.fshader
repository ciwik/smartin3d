#version 330

in vec2 uv;
in vec3 normal;

out vec4 color;

uniform sampler2D mainTex;
uniform vec3 mainColor;

void main()
{
	color = texture(mainTex, uv);
	//color = vec4(mainColor, 1.0);
}