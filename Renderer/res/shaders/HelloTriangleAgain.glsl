#shader vertex

#version 330 core

layout(location = 0) in vec3 aPos;

uniform float slide;

void main()
{
	gl_Position = vec4(aPos.x + slide, aPos.y, aPos.z, 1.0);
}

#shader fragment

#version 330 core

layout(location = 0) out vec4 color;

void main()
{
	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
