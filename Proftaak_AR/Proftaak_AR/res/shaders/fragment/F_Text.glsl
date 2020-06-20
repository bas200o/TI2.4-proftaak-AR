#version 330 core

layout(location = 0) out vec4 FragColor;

in vec2 UVCoord;

uniform vec3 textColor;
uniform sampler2D fontAtlas;

const float characterWidth = 0.5;
const float edgeTransitionWidth = 0.1;

void main()
{
    float distance = 1.0 - texture(fontAtlas, UVCoord).a;
    float alpha = 1.0 - smoothstep(characterWidth, characterWidth + edgeTransitionWidth, distance);

    FragColor = vec4(textColor, alpha);
}