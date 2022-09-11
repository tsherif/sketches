#version 440

uniform mat4 view;
uniform sampler2D tex;
uniform sampler2D normalMap;

in vec3 vTangentEyeVec;
in vec3 vTangentLightVec;
in vec3 vTangentLightDir;
in vec3 vTangentHeadlightVec;
in vec2 vUV;

out vec4 fragColor;

void main() {
    vec3 color = texture(tex, vUV).rgb;
    vec3 tangentNormal = texture(normalMap, vUV).xyz * 2.0 - 1.0;

    vec3 tangentEyeVec = normalize(vTangentEyeVec);
    vec3 tangentLightVec = normalize(vTangentLightVec);
    vec3 tangentLightDir = normalize(vTangentLightDir);
    vec3 tangentHeadlightVec = normalize(vTangentHeadlightVec);
    
    vec3 diffuse = vec3(0.0);
    vec3 highlight = vec3(0.0);
    vec3 ambient = vec3(0.0);
    vec3 lightColor = vec3(0.0);
    vec3 halfway = vec3(0.0);

    lightColor = vec3(0.4);
    halfway = normalize(tangentEyeVec + tangentLightVec);
    diffuse += lightColor * max(dot(tangentLightVec, tangentNormal), 0.0);
    highlight += lightColor * pow(max(dot(halfway, tangentNormal), 0.0), 100.0);

    lightColor = vec3(0.7);
    halfway = normalize(tangentEyeVec + tangentHeadlightVec);
    diffuse += lightColor * max(dot(tangentHeadlightVec, tangentNormal), 0.0);
    highlight += lightColor * pow(max(dot(halfway, tangentNormal), 0.0), 100.0);

    lightColor = vec3(0.4);
    diffuse += lightColor * max(dot(-tangentLightDir, tangentNormal), 0.0);
    
    ambient += 0.1;
    fragColor = vec4(color * (diffuse + highlight + ambient), 1.0);
};