#include "Window.h"
#include "RendererAPI.h"
#include "OpenGL/GLWindow.h"

std::shared_ptr<Window> Window::create(unsigned int width, unsigned int height, const char * name){
    switch(RendererAPI::getAPI()){
		case RendererAPI::API::None:
			//TODO assert
			return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<GLWindow>(width, height, name);

        default:
            return std::make_shared<GLWindow>(width, height, name);
	}
	//TODO assert API not defined
	return nullptr;
}