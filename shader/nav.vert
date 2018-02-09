#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 vert_uv;
out vec2 tex_uv;

uniform mat4 model;
uniform mat4 projection;

void main(void) {
    gl_Position =  projection * model * vec4(position, 1.0);
    tex_uv = vert_uv;
}