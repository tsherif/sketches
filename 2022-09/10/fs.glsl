#version 440
layout(std140, column_major) uniform SceneUniforms {
    mat4 proj;
    vec4 eyePosition;
    vec4 lightPosition;
    vec4 lightDirection;
};

uniform sampler2D tex;

in vec3 vPosition;
in vec3 vNormal;
in vec3 vTangent;
in vec2 vUV;

out vec4 fragColor;

void main() {
    vec3 color = texture(tex, vUV).rgb;
    vec3 normal = normalize(vNormal);
    vec3 eyeVec = normalize(eyePosition.xyz - vPosition);
    vec3 lightVec = normalize(lightPosition.xyz - vPosition);
    vec3 halfway = normalize(eyeVec + lightVec);
    float diffuse = max(dot(lightVec, normal), 0.0);
    float highlight = pow(max(dot(halfway, normal), 0.0), 100.0);
    float directionalDiffuse = max(dot(normalize(-lightDirection.xyz), normal), 0.0);;
    float ambient = 0.1;
    fragColor = vec4(color * (diffuse + directionalDiffuse + highlight + ambient), 1.0);
    fragColor = vec4(normalize(vTangent), 1.0);
};