/*
 * Renderer2D.cpp
 *
 *  Created on: Dec 12, 2019
 *      Author: gogotchuri
 */

#include "Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::shared_ptr<VertexArray> Renderer2D::va = nullptr;
std::shared_ptr<Shader> Renderer2D::shader = nullptr;

void Renderer2D::init(){
    shader = Shader::create(
		std::string("/home/gogotchuri/Workspace/OpenGL/GraphicsRenderer/Renderer/res/shaders/HelloTriangleAgain.glsl"));

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	uint32_t indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	std::shared_ptr<VertexBuffer> vb = VertexBuffer::create(vertices, sizeof(float), 12);
	VertexBufferLayout layout;
	layout.push(LayoutElement(ShaderDataType::Float3, "Vertex_coords"));
	vb->setLayout(layout);
	std::shared_ptr<IndexBuffer> ib = IndexBuffer::create(indices, 6);

	va = VertexArray::create();
	va->addVertexBuffer(vb);
	va->setIndexBuffer(ib);

	va->unbind();

	RenderCommand::init();
}

void Renderer2D::startScene(const OrthographicCamera& camera){
	shader->bind();
	glm::mat4 view_proj = camera.getViewProjectionMatrix();
	shader->setUniform("u_view_projection", ShaderDataType::Mat4, glm::value_ptr(view_proj));
}

void Renderer2D::startScene(const Camera& camera){
	shader->bind();
	glm::mat4 view_proj = camera.getViewProjectionMatrix();
	shader->setUniform("u_view_projection", ShaderDataType::Mat4, glm::value_ptr(view_proj));
}

void Renderer2D::endScene(){}

//Rectangle drawing
void Renderer2D::drawRect(const glm::vec3& position, const glm::vec2& size){
	glm::vec3 color = glm::vec3(0.5f, 0.0f, 0.2f);
	drawRect(position, size, color);
}

void Renderer2D::drawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color){
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
	shader->setUniform("u_model", ShaderDataType::Mat4, glm::value_ptr(model));
	shader->setUniform("u_color", ShaderDataType::Float3, glm::value_ptr(color));
	RenderCommand::drawVA(va);
}

void Renderer2D::drawRect(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture> texture){

}

void Renderer2D::drawRect(const glm::vec2& position, const glm::vec2& size){
	drawRect(glm::vec3(position.x, position.y, 0.0f), size);
}

void Renderer2D::drawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color){
	drawRect(glm::vec3(position.x, position.y, 0.0f), size, color);
}

void Renderer2D::drawRect(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture> texture){

}

