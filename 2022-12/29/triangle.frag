#version 300 es
precision highp float;

in vec2 vPosition;
uniform vec2 dimensions;
out vec4 fragColor;

void main() {
    float aspect = dimensions.x / dimensions.y;
    vec2 pos = vec2(vPosition.x * aspect, vPosition.y);

    vec2 v1 = vec2(-0.5, -0.5);
    vec2 v2 = vec2(0.5, -0.5);
    vec2 v3 = vec2(0.0, 0.5);

    float det = 1.0 / (v2.y - v3.y) * (v1.x - v3.x) + (v3.x - v2.x) * (v1.y - v3.y);
    float b1 = ((v2.y - v3.y) * (pos.x - v3.x) + (v3.x - v2.x) * (pos.y - v3.y)) / det;
    float b2 = ((v3.y - v1.y) * (pos.x - v3.x) + (v1.x - v3.x) * (pos.y - v3.y)) / det;
    float b3 = 1.0 - b1 - b2;

    float edgeStart = -0.1;
    float edgeEnd = -0.08;

    vec4 color = vec4(0.0, 0.0, 0.0, 1.0);
    if (b1 >= 0.0 && b2 >= 0.0 && b3 >= 0.0) {
        float f = min(b1, min(b2, b3));
        color = vec4(vec3(1.0) * smoothstep(edgeStart, edgeEnd, -f), 1.0);
    } else if (b1 <= 0.0 && b2 >= 0.0 && b3 >= 0.0) {
        float f = abs(b1);
        color = vec4(vec3(1.0) * smoothstep(edgeStart, edgeEnd, -f), 1.0);
    } else if (b1 >= 0.0 && b2 <= 0.0 && b3 >= 0.0) {
        float f = abs(b2);
        color = vec4(vec3(1.0) * smoothstep(edgeStart, edgeEnd, -f), 1.0);
    } else if (b1 >= 0.0 && b2 >= 0.0 && b3 <= 0.0) {
        float f = abs(b3);
        color = vec4(vec3(1.0) * smoothstep(edgeStart, edgeEnd, -f), 1.0);
    } else if (b1 <= 0.0 && b2 <= 0.0 && b3 >= 0.0) {
        float f1 = abs(b1);
        float f2 = abs(b2);
        color = vec4(vec3(1.0) * smoothstep(edgeStart,edgeEnd, -f1) * smoothstep(edgeStart,edgeEnd, -f2), 1.0);
    } else if (b1 <= 0.0 && b2 >= 0.0 && b3 <= 0.0) {
        float f1 = abs(b1);
        float f3 = abs(b3);
        color = vec4(vec3(1.0) * smoothstep(edgeStart,edgeEnd, -f1) * smoothstep(edgeStart,edgeEnd, -f3), 1.0);
    } else if (b1 >= 0.0 && b2 <= 0.0 && b3 <= 0.0) {
        float f2 = abs(b2);
        float f3 = abs(b3);
        color = vec4(vec3(1.0) * smoothstep(edgeStart,edgeEnd, -f2) * smoothstep(edgeStart,edgeEnd, -f3), 1.0);
    }

    fragColor = color;
}