#version 330

layout (location = 0) in vec3 pos;

out vec4 vCol;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = view * projection * model * vec4(pos, 1.0);
	vCol = vec4(clamp(pos, 0.0, 1.0), 1.0);
}