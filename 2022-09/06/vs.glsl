#version 440

layout(std140, column_major) uniform;
layout(location=0) in vec4 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;

layout(std140, column_major) uniform SceneUniforms {
    mat4 proj;
    vec4 eyePosition;
    vec4 lightPosition;
};       
uniform mat4 view;
uniform mat4 world;

out  vec3 vPosition;
out  vec2 vUV;
out  vec3 vNormal;

void main() {
    vec4 worldPosition = world * position;
    vPosition = worldPosition.xyz;
    vUV = uv;
    vNormal = normal;
    gl_Position = proj * view * worldPosition;
};