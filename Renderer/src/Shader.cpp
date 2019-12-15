/*
 * Shader.cpp
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#include "Shader.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLShader.h"

std::shared_ptr<Shader> Shader::create(std::string filepath){
	switch(RendererAPI::getAPI()){
		case RendererAPI::API::None:
			//TODO assert
			return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath);
	}
	//TODO assert API not defined
	return nullptr;
}

std::shared_ptr<Shader> Shader::create(std::string name, std::string& vertex_src, std::string& fragment_src){
	switch(RendererAPI::getAPI()){
		case RendererAPI::API::None:
			//TODO assert
			return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertex_src, fragment_src);
	}
	//TODO assert API not defined
	return nullptr;
}

