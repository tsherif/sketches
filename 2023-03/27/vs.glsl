#version 440

layout(location=0) in vec4 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec3 tangent;
layout(location=3) in vec2 uv;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 world;
uniform vec3 eyePosition;
uniform vec3 lightPosition1;
uniform vec3 lightPosition2;
uniform vec3 lightPosition3;
uniform vec3 lightPosition4;

out vec3 vTangentEyeVec;
out vec3 vTangentLightVec1;
out vec3 vTangentLightVec2;
out vec3 vTangentLightVec3;
out vec3 vTangentLightVec4;
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

    vTangentLightVec1 = inverseTBN * normalize(lightPosition1.xyz - worldPosition.xyz);
    vTangentLightVec2 = inverseTBN * normalize(lightPosition2.xyz - worldPosition.xyz);
    vTangentLightVec3 = inverseTBN * normalize(lightPosition3.xyz - worldPosition.xyz);
    vTangentLightVec4 = inverseTBN * normalize(lightPosition4.xyz - worldPosition.xyz);

    gl_Position = proj * view * worldPosition;
}