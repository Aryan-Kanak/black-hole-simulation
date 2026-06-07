#version 460 core

in vec2 uv;

out vec4 fragmentColor;

uniform sampler2D screenTex;

void main()
{
    fragmentColor = texture(screenTex, uv);
}
