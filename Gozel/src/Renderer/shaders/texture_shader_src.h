/*
 * texture_shader_src
 *
 *  Created on: 19-Jan-20 11:22:27
 *      Author: User
 */

#ifndef texture_shader_src
#define texture_shader_src
#include <string>

std::string TEXTURE_VERTEX_SRC =
	R"(
		#version 330 core

		layout(location = 0) in vec3 a_pos;
		layout(location = 1) in vec2 a_texCord;

		out vec2 outTexCords;

		uniform mat4 u_view_projection;
		uniform mat4 u_model;

		void main()
		{
			gl_Position = u_view_projection * u_model * vec4(a_pos, 1.0);
			outTexCords = a_texCord;
		}

	)";

std::string TEXTURE_FRAGMENT_SRC =
	R"(
		#version 330 core

		layout(location = 0) out vec4 color;

		in vec2 outTexCords;

		uniform sampler2D u_texture;

		void main()
		{
			vec4 fragColor = texture(u_texture, outTexCords);
			color = fragColor;
		}

	)";

#endif // texture_shader_src