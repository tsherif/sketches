#version 440

layout(location=0) in vec4 position;
layout(location=1) in vec3 normal;

uniform mat4 proj;
uniform mat4 view;
uniform vec2 offset;

out vec3 vPosition;
out vec2 vUV;
out vec3 vNormal;

void main() {
    vec4 worldPosition = position;
    worldPosition.xy += offset;
    vPosition = worldPosition.xyz;
    vNormal = normal;
    gl_Position = proj * view * worldPosition;
};