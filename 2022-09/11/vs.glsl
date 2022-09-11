#version 440

layout(std140, column_major) uniform;
layout(location=0) in vec4 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec3 tangent;
layout(location=3) in vec2 uv;

layout(std140, column_major) uniform SceneUniforms {
    mat4 proj;
    vec4 eyePosition;
    vec4 lightPosition;
    vec4 lightDirection;
    vec4 viewLightPosition;
};       
uniform mat4 view;
uniform mat4 world;

out  vec3 vPosition;
out  mat3 vTBN;
out  vec2 vUV;

void main() {
    vec4 worldPosition = world * position;
    
    vPosition = worldPosition.xyz;
    vUV = uv;
    
    vec3 bitangent = cross(normal, tangent);
    mat3 view3 = mat3(view) * mat3(world);
    vTBN =  mat3 (
        normalize(view3 * tangent),
        normalize(view3 * bitangent),
        normalize(view3 * normal)
    );

    gl_Position = proj * view * worldPosition;
};