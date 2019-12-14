#shader vertex

#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 texCord;

out vec2 outTexCords;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0);
	outTexCords = texCord;
}

#shader fragment

#version 330 core

layout(location = 0) out vec4 color;

in vec2 outTexCords;

uniform sampler2D u_texture;

void main()
{
	vec4 fragColor = texture(u_texture, outTexCords);
	color = fragColor;
}
