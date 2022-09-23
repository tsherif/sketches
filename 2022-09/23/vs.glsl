#version 440

layout(std140, column_major) uniform;
layout(location=0) in vec4 position;
layout(location=1) in vec3 normal;

layout(std140, column_major) uniform SceneUniforms {
    mat4 proj;
    vec4 eyePosition;
    vec4 lightPosition;
    vec4 lightDirection;
};       
uniform mat4 view;
uniform vec2 offset;

out  vec3 vPosition;
out  vec2 vUV;
out  vec3 vNormal;

void main() {
    vec4 worldPosition = position;
    worldPosition.xy += offset;
    vPosition = worldPosition.xyz;
    vNormal = normal;
    gl_Position = proj * view * worldPosition;
};