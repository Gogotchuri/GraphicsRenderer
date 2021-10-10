/*
 * OpenGLRendererAPI.cpp
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#include "OpenGLRendererAPI.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

OpenGLRendererAPI::~OpenGLRendererAPI(){
	glfwTerminate();
}
void OpenGLRendererAPI::init(){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
}
void OpenGLRendererAPI::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height){
	glViewport(x, y, width,height);
}
void OpenGLRendererAPI::setClearColor(float r, float g, float b, float a){
	glClearColor(r,g,b,a);
}
void OpenGLRendererAPI::clear(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::drawVA(const std::shared_ptr<VertexArray>& vertexArray){
	vertexArray->bind();
	glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
}
