#version 450

layout (set = 0, binding = 0) uniform sampler2D tex;
layout (location = 0) in vec2 inUV;
layout (location = 1) in vec3 inNormal;
layout (location = 0) out vec4 outColor;

void main(void)
{
	vec3 lightDir = normalize(vec3(0.3, -1.0, -0.5));
	float diffuse = max(dot(inNormal, lightDir), 0.0);
	float ambient = 0.4;
	vec3 lighting = (ambient + diffuse) * vec3(0.7);
	vec4 texColor = texture(tex, inUV);
	outColor = vec4(texColor.rgb * lighting, texColor.a);
}
