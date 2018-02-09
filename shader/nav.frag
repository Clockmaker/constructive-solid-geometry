#version 330 core
//layout(binding=0)//version 420
in vec2 tex_uv;


out vec4 color;
uniform sampler2D texs;

void main(void) {
    color = texture(texs, tex_uv);
}