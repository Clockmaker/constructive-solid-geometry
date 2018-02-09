#version 150
in vec4 position;
in vec4 colorBuf;
out vec4 line_color;

uniform mat4 camera;

void main(void) {
    gl_Position = camera * position;
    line_color = colorBuf;
}