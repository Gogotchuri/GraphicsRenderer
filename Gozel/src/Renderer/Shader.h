/*
 * Shader.h
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <memory>
#include <string>
#include "VertexBufferLayout.h"

class Shader {
public:
	virtual ~Shader() = default;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	virtual unsigned int getID() const = 0;
	virtual const std::string& getName() const = 0;

	virtual void setUniform(std::string name, ShaderDataType type, const void * data) const = 0;
	static std::shared_ptr<Shader> create(std::string filepath);
	static std::shared_ptr<Shader> create(std::string name, std::string& vertex_src, std::string& fragment_src);
};

#endif /* SHADER_H_ */
