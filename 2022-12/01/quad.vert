#version 300 es

in vec4 position;
out vec2 vPosition;

void main() {
    vPosition = position.xy;
    gl_Position = position;
}