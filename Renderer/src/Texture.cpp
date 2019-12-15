#include "Texture.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLTexture.h"

std::shared_ptr<Texture> Texture::create(const std::string& filepath) {
	switch (RendererAPI::getAPI()) {
	case RendererAPI::API::None:
		//TODO assert
		return nullptr;
	case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture>(filepath);
	}
	//TODO assert API not defined
	return nullptr;
}