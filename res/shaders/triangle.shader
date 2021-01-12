#shader vertex

#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 myColor;

out vec4 aColor;
uniform float slide;

void main()
{
	gl_Position = vec4(aPos.x + slide, aPos.y, aPos.z, 1.0);
	aColor = vec4(myColor.x, myColor.y, myColor.z, 0);
}

#shader fragment

#version 330 core

layout(location = 0) out vec4 color;

in vec4 aColor;

void main()
{
	color = aColor;
}
