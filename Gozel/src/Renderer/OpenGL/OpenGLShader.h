/*
 * OpenGLShader.h
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#ifndef OPENGL_OPENGLSHADER_H_
#define OPENGL_OPENGLSHADER_H_

#include "Shader.h"
#include <glad/glad.h>

class OpenGLShader : public Shader {
public:
	OpenGLShader(std::string& name, std::string& vertex_src, std::string& fragment_src);
	OpenGLShader(std::string& filepath);
	virtual ~OpenGLShader(){};
	virtual void bind() const override;
	virtual void unbind() const override;
	virtual void setUniform(std::string name, ShaderDataType type, const void * data) const override;
	virtual uint32_t getID() const { return gl_program_id; };
	virtual const std::string& getName() const { return name; };

private:
	struct ShaderSrc{
		std::string vertex_src;
		std::string fragment_src;
	};
	enum ShaderType{VERTEX = GL_VERTEX_SHADER, FRAGMENT = GL_FRAGMENT_SHADER, NONE = 0};
	ShaderSrc parseShaders(std::string filepath);
	int compileShader(ShaderType type, const std::string & source);
	void createProgram(std::string& vertex_src, std::string& fragment_src);
private:
	int gl_program_id;
	std::string name;
};

#endif /* OPENGL_OPENGLSHADER_H_ */
