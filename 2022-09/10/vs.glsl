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
};       
uniform mat4 view;
uniform mat4 world;

out  vec3 vPosition;
out  vec3 vNormal;
out  vec3 vTangent;
out  vec2 vUV;

void main() {
    vec4 worldPosition = world * position;
    vPosition = worldPosition.xyz;
    vUV = uv;
    vNormal = mat3(world) * normal;
    vTangent = mat3(world) * tangent;
    gl_Position = proj * view * worldPosition;
};