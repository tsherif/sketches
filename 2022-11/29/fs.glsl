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

    vec2 v1 = vec2(-0.5, -0.5);
    vec2 v2 = vec2(0.5, -0.5);
    vec2 v3 = vec2(0.0, 0.5);

    float b1 = ((v2.y - v3.y) * (pos.x - v3.x) + (v3.x - v2.x) * (pos.y - v3.y)) / ((v2.y - v3.y) * (v1.x - v3.x) + (v3.x - v2.x) * (v1.y - v3.y));
    float b2 = ((v3.y - v1.y) * (pos.x - v3.x) + (v1.x - v3.x) * (pos.y - v3.y)) / ((v2.y - v3.y) * (v1.x - v3.x) + (v3.x - v2.x) * (v1.y - v3.y));
    float b3 = 1.0 - b1 - b2;

    float edge = min(abs(b1), min(abs(b2), abs(b3)));
    float outside = min(b1, min(b2, b3));

    vec4 color = vec4(vec3(1.0) * step(-0.04, -edge) * step(-0.04, outside), 1.0);

    fragColor = color;
}