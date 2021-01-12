#shader vertex

#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 u_view_projection;
uniform mat4 u_model;

void main()
{
	gl_Position = u_view_projection * u_model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}

#shader fragment

#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 u_color;

void main()
{
	color = vec4(u_color.x, u_color.y, u_color.z, 1.0f);
}
