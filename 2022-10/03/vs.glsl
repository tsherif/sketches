#version 440

#define NUM_LIGHTS 4

layout(location=0) in vec4 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec3 tangent;
layout(location=3) in vec2 uv;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 world;
uniform vec3 eyePosition;
uniform vec3 lightPositions[NUM_LIGHTS];

out vec3 vTangentEyeVec;
out vec3 vTangentLightVecs[NUM_LIGHTS];
out vec2 vUV;

void main() {
    vUV = uv;
    
    vec3 worldNormal = mat3(world) * normal;
    vec3 bitangent = cross(normal, tangent);
    mat3 inverseTBN =  transpose(
        mat3(
            tangent,
            bitangent,
            worldNormal
        )
    );

    vec4 worldPosition = world * position;
    vec3 worldEyeVec = normalize(eyePosition.xyz - worldPosition.xyz);
    vTangentEyeVec = inverseTBN * worldEyeVec;

    for (int i = 0; i < NUM_LIGHTS; ++i) {
        vec3 lightPosition = lightPositions[i];
        vec3 worldLightVec = normalize(lightPosition.xyz - worldPosition.xyz);
        vTangentLightVecs[i] = inverseTBN * worldLightVec;
    }

    gl_Position = proj * view * worldPosition;
};