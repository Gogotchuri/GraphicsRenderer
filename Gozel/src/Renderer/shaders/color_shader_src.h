/*
 * color_shader_src
 *
 *  Created on: 19-Jan-20 11:22:07
 *      Author: User
 */

#ifndef color_shader_src
#define color_shader_src
#include <string>

std::string COLOR_VERTEX_SRC = 
R"(
	#version 330 core

	layout(location = 0) in vec3 aPos;

	uniform mat4 u_view_projection;
	uniform mat4 u_model;

	void main()
	{
		gl_Position = u_view_projection * u_model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	}
)";

std::string COLOR_FRAGMENT_SRC =
R"(
	#version 330 core

	layout(location = 0) out vec4 color;

	uniform vec3 u_color;

	void main()
	{
		color = vec4(u_color.x, u_color.y, u_color.z, 1.0f);
	}
)";

#endif // color_shader_src