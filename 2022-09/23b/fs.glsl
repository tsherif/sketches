#version 440

#define PI 3.14159265359
#define NUM_LIGHTS 4
#define LIGHT_COLOR vec3(20.0)

uniform vec3 eyePosition;
uniform vec3 lightPositions[NUM_LIGHTS];
uniform float metalness;
uniform float roughness;

in vec3 vPosition;
in vec3 vNormal;

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
    vec3 materialColor = vec3(1.0, 0.0, 0.0);

    vec3 normal = normalize(vNormal);
    vec3 eyeVec = normalize(eyePosition.xyz - vPosition);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    vec3 ambient = vec3(0.0);

    vec3 f0 = vec3(0.04); 
    f0 = mix(f0, materialColor, metalness);

    vec3 light = vec3(0.0);
    for (int i = 0; i < NUM_LIGHTS; ++i) {
        vec3 lightPosition = lightPositions[i];
        vec3 lightVec = normalize(lightPosition - vPosition);
        vec3 halfway = normalize(eyeVec + lightVec);

        float ndf = distributionGGX(normal, halfway, roughness);        
        float g = geometrySmith(normal, eyeVec, lightVec, roughness);      
        vec3 f = fresnelSchlick(max(dot(halfway, eyeVec), 0.0), f0);       
        vec3 kS = f;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metalness;     
        vec3 numerator = ndf * g * f;
        float denominator = 4.0 * max(dot(normal, eyeVec), 0.0) * max(dot(normal, lightVec), 0.0) + 0.0001;
        vec3 specular = numerator / denominator;  
        float nDotL = max(dot(normal, lightVec), 0.0);                
        light += (kD * materialColor / PI + specular) * LIGHT_COLOR * nDotL; 
    }
   
    ambient += 0.01 * materialColor;
    light += ambient;
    
    fragColor = vec4(light + ambient, 1.0);
    fragColor.rgb = fragColor.rgb / (fragColor.rgb + vec3(1.0));
    fragColor.rgb = pow(fragColor.rgb, vec3(1.0 / 2.2));
};