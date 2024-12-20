#version 440

const float PI = 3.14159265359;

uniform mat4 view;
uniform sampler2D colorMap;
uniform sampler2D normalMap;
uniform sampler2D metallicRoughnessMap;

in vec3 vTangentEyeVec;
in vec3 vTangentLightVec;
in vec3 vTangentLightDir;
in vec3 vTangentHeadlightVec;
in vec2 vUV;

out vec4 fragColor;

float distributionGGX(vec3 normal, vec3 halfway, float roughness) {
    float a      = roughness * roughness;
    float a2     = a * a;
    float NdotH  = max(dot(normal, halfway), 0.0);
    float NdotH2 = NdotH * NdotH;
    
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
    
    return num / denom;
}

float geometrySchlickGGX(float nDotV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;

    float num   = nDotV;
    float denom = nDotV * (1.0 - k) + k;
    
    return num / denom;
}

float geometrySmith(vec3 normal, vec3 viewVec, vec3 lightVec, float roughness)
{
    float nDotV = max(dot(normal, viewVec), 0.0);
    float nDotL = max(dot(normal, lightVec), 0.0);
    float ggx2  = geometrySchlickGGX(nDotV, roughness);
    float ggx1  = geometrySchlickGGX(nDotL, roughness);
    
    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 f0) {
    return f0 + (1.0 - f0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}  

void main() {
    vec3 color = texture(colorMap, vUV).rgb;
    vec3 tangentNormal = texture(normalMap, vUV).xyz * 2.0 - 1.0;
    vec2 metallicRoughness = texture(metallicRoughnessMap, vUV).xy;
    float metalness = metallicRoughness.x;
    float roughness = metallicRoughness.y;

    vec3 f0 = vec3(0.04); 
    f0 = mix(f0, color, metalness);

    vec3 tangentEyeVec = normalize(vTangentEyeVec);
    vec3 tangentLightVec = normalize(vTangentLightVec);
    vec3 tangentLightDir = normalize(vTangentLightDir);
    vec3 tangentHeadlightVec = normalize(vTangentHeadlightVec);
    
    vec3 light = vec3(0.0);
    vec3 ambient = vec3(0.0);
    vec3 lightColor = vec3(0.0);
    vec3 halfway = vec3(0.0);
    float ndf = 0.0;
    float g = 0.0;
    vec3 f = vec3(0.0);
    vec3 kS = vec3(0.0);
    vec3 kD = vec3(0.0);
    vec3 numerator = vec3(0.0);
    float denominator = 0.0;
    vec3 specular = vec3(0.0);        
    float nDotL = 0.0;   

    lightColor = vec3(20.0);
    halfway = normalize(tangentEyeVec + tangentLightVec);
    ndf = distributionGGX(tangentNormal, halfway, roughness);        
    g = geometrySmith(tangentNormal, tangentEyeVec, tangentLightVec, roughness);      
    f = fresnelSchlick(max(dot(halfway, tangentEyeVec), 0.0), f0);       
    kS = f;
    kD = vec3(1.0) - kS;
    kD *= 1.0 - metalness;     
    numerator = ndf * g * f;
    denominator = 4.0 * max(dot(tangentNormal, tangentEyeVec), 0.0) * max(dot(tangentNormal, tangentLightVec), 0.0) + 0.0001;
    specular = numerator / denominator;  
    nDotL = max(dot(tangentNormal, tangentLightVec), 0.0);                
    light += (kD * lightColor / PI + specular) * lightColor * nDotL; 

    lightColor = vec3(10.0);
    halfway = normalize(tangentEyeVec + tangentHeadlightVec);
    ndf = distributionGGX(tangentNormal, halfway, roughness);        
    g = geometrySmith(tangentNormal, tangentEyeVec, tangentLightVec, roughness);      
    f = fresnelSchlick(max(dot(halfway, tangentEyeVec), 0.0), f0);       
    kS = f;
    kD = vec3(1.0) - kS;
    kD *= 1.0 - metalness;     
    numerator = ndf * g * f;
    denominator = 4.0 * max(dot(tangentNormal, tangentEyeVec), 0.0) * max(dot(tangentNormal, tangentHeadlightVec), 0.0) + 0.0001;
    specular = numerator / denominator;  
    nDotL = max(dot(tangentNormal, tangentHeadlightVec), 0.0);                
    light += (kD * lightColor / PI + specular) * lightColor * nDotL; 

    lightColor = vec3(5.0);
    halfway = normalize(tangentEyeVec - tangentLightDir);
    ndf = distributionGGX(tangentNormal, halfway, roughness);        
    g = geometrySmith(tangentNormal, tangentEyeVec, tangentLightVec, roughness);      
    f = fresnelSchlick(max(dot(halfway, tangentEyeVec), 0.0), f0);       
    kS = f;
    kD = vec3(1.0) - kS;
    kD *= 1.0 - metalness;     
    numerator = ndf * g * f;
    denominator = 4.0 * max(dot(tangentNormal, tangentEyeVec), 0.0) * max(dot(tangentNormal, -tangentLightDir), 0.0) + 0.0001;
    specular = numerator / denominator;  
    nDotL = max(dot(tangentNormal, -tangentLightDir), 0.0);                
    light += (kD * lightColor / PI + specular) * lightColor * nDotL; 
    
    ambient += 0.1;
    fragColor = vec4(color * (light + ambient), 1.0);
    fragColor.rgb = fragColor.rgb / (fragColor.rgb + vec3(1.0));
    fragColor.rgb = pow(fragColor.rgb, vec3(1.0 / 2.2));
};