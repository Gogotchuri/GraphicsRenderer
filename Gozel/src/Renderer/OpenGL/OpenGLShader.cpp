/*
 * OpenGLShader.cpp
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#include "OpenGLShader.h"
#include <assert.h>
#include <string.h>
#include <iostream>

OpenGLShader::OpenGLShader(std::string& name, std::string& vertex_src, std::string& fragment_src)
	:name(name), gl_program_id(0)
{
	createProgram(vertex_src, fragment_src);
}

OpenGLShader::OpenGLShader(std::string& filepath)
	:name(filepath), gl_program_id(0)
{
	ShaderSrc src = parseShaders(filepath);
	createProgram(src.vertex_src, src.fragment_src);
}

void OpenGLShader::setUniform(std::string name, ShaderDataType type, const void * data) const {
	const int uniform_loc = glGetUniformLocation(getID(), name.c_str());
	switch(type){
		case ShaderDataType::Float1:
			glUniform1fv(uniform_loc, 1, (float *) data);
			break;
		case ShaderDataType::Float2:
			glUniform2fv(uniform_loc, 1, (float *) data);
			break;
		case ShaderDataType::Float3:
			glUniform3fv(uniform_loc, 1, (float *) data);
			break;
		case ShaderDataType::Float4:
			glUniform4fv(uniform_loc, 1, (float *) data);
			break;
		case ShaderDataType::Int1:
			glUniform1iv(uniform_loc, 1, (int *) data);
			break;
		case ShaderDataType::Int2:
			glUniform2iv(uniform_loc, 1, (int *) data);
			break;
		case ShaderDataType::Int3:
			glUniform3iv(uniform_loc, 1, (int *) data);
			break;
		case ShaderDataType::Int4:
			glUniform4iv(uniform_loc, 1, (int *) data);
			break;
		case ShaderDataType::Mat2:
			glUniformMatrix2fv(uniform_loc, 1, GL_FALSE, (float *) data);
			break;
		case ShaderDataType::Mat3:
			glUniformMatrix3fv(uniform_loc, 1, GL_FALSE, (float *) data);
			break;
		case ShaderDataType::Mat4:
			glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, (float *) data);
			break;
		//TODO
		//Others should be added
		default: assert(false);
	}
}

void OpenGLShader::bind() const {
	glUseProgram(gl_program_id);
}

void OpenGLShader::unbind() const {
	glUseProgram(0);
}

//+++++++++++++++++++Privates+++++++++++++++++++++++++++++++++++++++++++++
OpenGLShader::ShaderSrc OpenGLShader::parseShaders(std::string filepath){
	ShaderSrc src;
	src.vertex_src = src.fragment_src = "";
	FILE * source = fopen(filepath.c_str(), "r");
	assert(source != NULL);
	char line_buffer[512];
	ShaderType type = ShaderType::NONE;

	while (fgets(line_buffer, 256, source)) {
		if (!strcmp(line_buffer, "#shader vertex\n")) {
			type = ShaderType::VERTEX;
			continue;
		}

		if (!strcmp(line_buffer, "#shader fragment\n")) {
			type = ShaderType::FRAGMENT;
			continue;
		}

		if (type == ShaderType::VERTEX)
			src.vertex_src += std::string(line_buffer);

		else if (type == ShaderType::FRAGMENT)
			src.fragment_src += std::string(line_buffer);
	}

	fclose(source);
	return src;
}

int OpenGLShader::compileShader(ShaderType type, const std::string & source) {
	int id = glCreateShader(type);
	const char * src = source.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	int status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		char message[512];
		glGetShaderInfoLog(id, 512, NULL, message);
		printf("failed to compile %s \n log: \n %s", (type == GL_VERTEX_SHADER) ? "Vertex shader!" : "Fragment shader!", message);
		glDeleteShader(id);
		assert(false);
		return 0;
	}
	return id;
}

void OpenGLShader::createProgram(std::string& vertex_src, std::string& fragment_src) {
	gl_program_id = glCreateProgram();

	int vertext_shader = compileShader(ShaderType::VERTEX, vertex_src);
	int fragment_shader = compileShader(ShaderType::FRAGMENT, fragment_src);

	glAttachShader(gl_program_id, vertext_shader);
	glAttachShader(gl_program_id, fragment_shader);
	glLinkProgram(gl_program_id);
	//glValidateProgram(gl_program_id);

	int status;
	glGetProgramiv(gl_program_id, GL_LINK_STATUS, &status);

	if (status == GL_FALSE) {
		char message[512];
		glGetProgramInfoLog(gl_program_id, 512, NULL, message);
		printf("failed to create a program. log: \n %s", message);
		glDeleteProgram(gl_program_id);
		assert(false);
		return;
	}

	glDeleteShader(vertext_shader);
	glDeleteShader(fragment_shader);
}
