#version 450

in layout(location=0) vec4 position;

out vec2 texCoord;

void main()
{
	texCoord = position.zw;
	gl_Position = vec4(position.xy, 0.0f, 1.0f);
}