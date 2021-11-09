/*
 * Buffer.cpp
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#include "Buffer.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLBuffer.h"

std::shared_ptr<VertexBuffer> VertexBuffer::create(const void * data, uint32_t unit_size, unsigned int count) {
	switch(RendererAPI::getAPI()){
		case RendererAPI::API::None:
			//TODO assert
			return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(data, unit_size, count);
	}
	//TODO assert API not defined
	return nullptr;
};

std::shared_ptr<IndexBuffer> IndexBuffer::create(const uint32_t * data, unsigned int count) {
	switch(RendererAPI::getAPI()){
		case RendererAPI::API::None:
			//TODO assert
			return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(data, count);
	}
	//TODO assert API not defined
	return nullptr;
};
