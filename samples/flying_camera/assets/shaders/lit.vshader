#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 norm;

out vec2 uv;
out vec3 normal;
out vec4 vCol;
out vec3 fragPos;
out vec4 directionalLightSpacePos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 directionalLightTransform;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	directionalLightSpacePos = directionalLightTransform * model * vec4(pos, 1.0);
	vCol = vec4(clamp(pos, 0.0f, 1.0), 1.0);
	uv = tex;
	normal = mat3(transpose(inverse(model))) * norm;
	fragPos = (model * vec4(pos, 1.0)).xyz;
}