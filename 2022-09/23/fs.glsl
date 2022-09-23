#version 440

#define NUM_LIGHTS 4
#define LIGHT_COLOR vec3(0.3)
uniform vec3 eyePosition;
uniform vec3 lightPositions[NUM_LIGHTS];

in vec3 vPosition;
in vec3 vNormal;

out vec4 fragColor;

void main() {
    vec3 color = vec3(1.0, 0.0, 0.0);

    vec3 normal = normalize(vNormal);
    vec3 eyeVec = normalize(eyePosition.xyz - vPosition);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    vec3 ambient = vec3(0.0);

    for (int i = 0; i < NUM_LIGHTS; ++i) {
        vec3 lightPosition = lightPositions[i];
        vec3 lightVec = normalize(lightPosition - vPosition);
        vec3 halfway = normalize(eyeVec + lightVec);

        diffuse += LIGHT_COLOR * max(dot(lightVec, normal), 0.0);
        specular += LIGHT_COLOR * pow(max(dot(halfway, normal), 0.0), 100.0);
    }
   
    ambient += 0.01;
    
    fragColor = vec4(color * (diffuse + specular + ambient), 1.0);
};