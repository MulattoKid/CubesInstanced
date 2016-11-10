#version 450

in layout(location=0) vec3 position;
in layout(location=1) vec3 color;
in layout(location=2) vec3 offset;

uniform mat4 mvp;

out vec3 fragColor;

void main()
{
	fragColor = color;
	gl_Position = mvp *  vec4(position.x + offset.x, position.y + offset.y, position.z + offset.z, 1.0f);
}