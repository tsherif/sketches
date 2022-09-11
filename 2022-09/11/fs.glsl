#version 440
layout(std140, column_major) uniform SceneUniforms {
    mat4 proj;
    vec4 eyePosition;
    vec4 lightPosition;
    vec4 lightDirection;
    vec4 viewLightPosition;
};

uniform mat4 view;
uniform sampler2D tex;
uniform sampler2D normalMap;

in vec3 vPosition;
in mat3 vTBN;
in vec2 vUV;

out vec4 fragColor;

void main() {
    vec3 color = texture(tex, vUV).rgb;
    vec3 normal = texture(normalMap, vUV).xyz * 2.0 - 1.0;
    normal = normalize(vTBN * normal);

    mat3 view3 = mat3(view);

    vec3 eyeVec = view3 * normalize(eyePosition.xyz - vPosition);
    vec3 lightVec = view3 * normalize(lightPosition.xyz - vPosition);
    vec3 viewLightDir = view3 * normalize(-lightDirection.xyz);
    
    vec3 diffuse = vec3(0.0);
    vec3 highlight = vec3(0.0);
    vec3 lightColor = vec3(0.0);

    lightColor = vec3(0.4);
    vec3 halfway = normalize(eyeVec + lightVec);
    diffuse += lightColor * max(dot(lightVec, normal), 0.0);
    highlight += lightColor * pow(max(dot(halfway, normal), 0.0), 100.0);

    vec4 viewPosition = view * vec4(vPosition, 1.0);
    lightColor = vec3(0.7);
    lightVec = normalize(viewLightPosition.xyz - viewPosition.xyz);
    halfway = normalize(eyeVec + lightVec);
    diffuse += lightColor * max(dot(lightVec, normal), 0.0);
    highlight += lightColor * pow(max(dot(halfway, normal), 0.0), 100.0);

    lightColor = vec3(0.4);
    diffuse += lightColor * max(dot(normalize(viewLightDir), normal), 0.0);;
    
    float ambient = 0.1;
    fragColor = vec4(color * (diffuse + highlight + ambient), 1.0);
};