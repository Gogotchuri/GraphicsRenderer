/*
 * RendererAPI.cpp
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#include "RendererAPI.h"
#include "OpenGL/OpenGLRendererAPI.h"

RendererAPI::API RendererAPI::current_API = RendererAPI::API::OpenGL;

std::shared_ptr<RendererAPI> RendererAPI::create() {
	switch(RendererAPI::getAPI()){
		case RendererAPI::API::None:
			//TODO assert
			return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLRendererAPI>();
	}
	//TODO assert API not defined
	return nullptr;
};
