#version 330

in vec2 uv;
in vec3 normal;
in vec4 vCol;
in vec3 fragPos;
in vec4 directionalLightSpacePos;

out vec4 color;

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

struct Light
{
	vec3 color;
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight
{
	Light base;
	vec3 direction;
};

struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

struct SpotLight
{
	PointLight base;
	vec3 direction;
	float edge;
};

struct OmniShadowMap
{
	samplerCube shadowMap;
	float farPlane;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

uniform DirectionalLight directionalLight;

uniform int pointLightCount;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform int spotLightCount;
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform sampler2D mainTex;
uniform vec3 mainColor;

uniform sampler2D directionalShadowMap;
uniform OmniShadowMap omniShadowMaps[MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS];

uniform Material material;

uniform vec3 eyePosition;

vec3 sampleOffsetDirections[20] = vec3[]
(
	vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1),
	vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
	vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
	vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
	vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float CalculateDirectionalShadowFactor(DirectionalLight light)
{
	vec3 projCoords = directionalLightSpacePos.xyz / directionalLightSpacePos.w;
	projCoords = projCoords * 0.5 + 0.5;

	float current = projCoords.z;

	vec3 lightDir = normalize(light.direction);

	float bias = max(0.05 * (1.0 - dot(normalize(normal), lightDir)), 0.0005);

	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(directionalShadowMap, 0);
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			float pcfDepth = texture(directionalShadowMap, projCoords.xy + vec2(x,y) * texelSize).r;
			shadow += current - bias > pcfDepth ? 1.0 : 0.0;
		}
	}

	shadow /= 9.0;

	if (projCoords.z > 1.0)
		shadow = 0.0;

	return shadow;
}

float CalculateOmniShadowFactor(PointLight light, int shadowIndex)
{
	vec3 fragToLight = fragPos - light.position;
	float current = length(fragToLight);

	float shadow = 0.0;
	float bias = 0.15;
	int samples = 20;

	float viewDistance = length(eyePosition - fragPos);
	float diskRadius = (1.0 + viewDistance / omniShadowMaps[shadowIndex].farPlane) / 25.0;

	for (int i = 0; i < samples; i++) {
		float closest = texture(omniShadowMaps[shadowIndex].shadowMap, fragToLight + sampleOffsetDirections[i] * diskRadius).r;
		closest *= omniShadowMaps[shadowIndex].farPlane;
		if (current - bias > closest)
			shadow += 1.0;
	}

	shadow /= float(samples);
	return shadow;
}

vec4 CalculateLightByDirection(Light light, vec3 direction, float shadowFactor)
{
	vec4 ambientColor = vec4(light.color, 1.0) * light.ambientIntensity;

	float diffuseFactor = max(dot(normalize(normal), normalize(direction)), 0.0);
	vec4 diffuseColor = vec4(light.color, 1.0) * light.diffuseIntensity * diffuseFactor;

	vec4 specularColor = vec4(0.0, 0.0, 0.0, 0.0);
	if (diffuseFactor > 0.0) {
		vec3 fragToEye = normalize(eyePosition - fragPos);
		vec3 reflectedVertex = normalize(reflect(direction, normalize(normal)));

		float specularFactor = dot(fragToEye, reflectedVertex);
		if (specularFactor > 0.0) {
			specularFactor = pow(specularFactor, material.shininess);
			specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.0);
		}
	}

	return ambientColor + (1.0 - shadowFactor) * (diffuseColor + specularColor);
}

vec4 CalculateDirectionalLight()
{
	float shadowFactor = CalculateDirectionalShadowFactor(directionalLight);
	return CalculateLightByDirection(directionalLight.base, directionalLight.direction, shadowFactor);
}

vec4 CalculatePointLight(PointLight light, int shadowIndex)
{
	vec3 direction = fragPos - light.position;
	float distance = length(direction);
	direction = normalize(direction);

	float shadowFactor = CalculateOmniShadowFactor(light, shadowIndex);

	vec4 color = CalculateLightByDirection(light.base, direction, shadowFactor);
	float attenuation = light.exponent * distance * distance +
						light.linear * distance +
						light.constant;

	return color / attenuation;
}

vec4 CalculateSpotLight(SpotLight light, int shadowIndex)
{
	vec3 rayDirection = normalize(fragPos - light.base.position);
	float lightFactor = dot(rayDirection, light.direction);

	vec4 color = vec4(0, 0, 0, 0);

	if (lightFactor > light.edge)
		color = CalculatePointLight(light.base, shadowIndex);
	float smoothFactor = 1 - (1 - lightFactor) / (1 - light.edge);

	return color * smoothFactor;
}

vec4 CalculatePointLights()
{
	vec4 totalColor = vec4(0, 0, 0, 0);

	for (int i = 0; i < pointLightCount; i++)
		totalColor += CalculatePointLight(pointLights[i], i);

	return totalColor;
}

vec4 CalculateSpotLights()
{
	vec4 totalColor = vec4(0, 0, 0, 0);

	for (int i = 0; i < spotLightCount; i++)
		totalColor += CalculateSpotLight(spotLights[i], pointLightCount + i);

	return totalColor;
}

void main()
{
	vec4 finalColor = CalculateDirectionalLight();
	finalColor += CalculatePointLights();
	finalColor += CalculateSpotLights();

    // In case if there are not any active light sources
    if (finalColor == vec4(0, 0, 0, 0))
        finalColor == vec4(1, 1, 1, 1);

	color = texture(mainTex, uv) * finalColor + vec4(mainColor, 1.0);
}