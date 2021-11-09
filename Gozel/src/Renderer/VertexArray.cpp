/*
 * VertexArray.cpp
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#include "VertexArray.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLVertexArray.h"

std::shared_ptr<VertexArray> VertexArray::create() {
	switch(RendererAPI::getAPI()){
		case RendererAPI::API::None:
			//TODO assert
			return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
	}
	//TODO assert API not defined
	return nullptr;
}
