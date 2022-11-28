#version 300 es
precision highp float;

#define PI      3.141592653589793
#define TAU     (2.0 * PI)
#define SQRT2   1.41421

in vec2 vPosition;
uniform vec2 dimensions;
out vec4 fragColor;

void main() {
    float aspect = dimensions.x / dimensions.y;
    vec2 pos = vec2(vPosition.x * aspect, vPosition.y);

    vec4 color = vec4(vec3(1.0) * smoothstep(-0.055, -0.045, -abs(pos.x - pos.y)) * smoothstep(-1.505, -1.495, -abs(pos.x + pos.y)), 1.0);

    fragColor = color;
}