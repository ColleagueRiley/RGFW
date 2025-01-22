#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) out vec3 fragColor;

layout(push_constant, std430) uniform pc {
    vec2 mouse_data;
};

vec2 positions[3] = vec2[](vec2 (-0.6, -0.75), vec2 (0.6, -0.75), vec2 (0, 0.75));
vec3 colors[3] = vec3[](vec3 (1.0, 0.0, 0.0), vec3 (0.0, 1.0, 0.0), vec3 (0.0, 0.0, 1.0));

void main()
{
    gl_Position = vec4(positions[gl_VertexIndex]+mouse_data, 0.0, 1.0);
    fragColor = colors[gl_VertexIndex];
}
