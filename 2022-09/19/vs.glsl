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
    vec4 headlightPosition;
};

uniform mat4 view;
uniform mat4 world;

out vec3 vTangentEyeVec;
out vec3 vTangentLightVec;
out vec3 vTangentLightDir;
out vec3 vTangentHeadlightVec;
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
    vec3 worldLightVec = normalize(lightPosition.xyz - worldPosition.xyz);
    vec3 worldLightDir = normalize(lightDirection.xyz);

    mat3 inverseView = transpose(mat3(view));
    vec4 viewPosition = view * worldPosition;
    vec3 worldHeadlightVec = inverseView * normalize(headlightPosition.xyz - viewPosition.xyz);

    vTangentEyeVec = inverseTBN * worldEyeVec;
    vTangentLightVec = inverseTBN * worldLightVec;
    vTangentLightDir = inverseTBN * worldLightDir;
    vTangentHeadlightVec = inverseTBN * worldHeadlightVec;

    gl_Position = proj * viewPosition;
};