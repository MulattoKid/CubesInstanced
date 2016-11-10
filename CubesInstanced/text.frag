#version 450

in vec2 texCoord;

uniform sampler2D sampler;
uniform vec3 textColor;

out vec4 color;

void main()
{
	vec4 sampledColor = vec4(1.0f, 1.0f, 1.0f, texture(sampler, texCoord).r);
	color = vec4(textColor, 1.0f) * sampledColor;
}