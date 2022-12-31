#version 300 es
precision highp float;

in vec2 vPosition;
uniform vec2 dimensions;
out vec4 fragColor;

void main() {
    float aspect = dimensions.x / dimensions.y;
    vec2 pos = vec2(vPosition.x * aspect, vPosition.y) * vec2(0.5, 0.8);
    float r2 = dot(pos, pos);

    vec4 color = vec4(vec3(1.0) * smoothstep(-0.055, -0.045, -abs(r2 - 0.16)), 1.0);

    fragColor = color;
}