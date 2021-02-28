#version 330

in vec2 uv;
in vec3 normal;

out vec4 color;

uniform sampler2D mainTex;
uniform vec3 mainColor;

void main()
{
	color = vec4(1.0, 0.0, 0.0, 1.0) + texture(mainTex, uv);
}