/**
 * This file doesn't contain anything important for this library,
 * it's used just for practice and fast implementation testing
*/

#include <iostream>
#include "Renderer.h"
#include "Texture.h"
#include "RendererAPI.h"
#include "RenderCommand.h"
#include "Camera.h"
#include "Window.h"
#include "Renderer2D.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <slogger/slogger.h>

using namespace std;

void texturedSquare(std::shared_ptr<Window> window);
void closeOnEnter(GLFWwindow * window);
void closeOnEnter(std::shared_ptr<Window> window);
void twoTriangles(GLFWwindow * window);
void Square(GLFWwindow * window);
void helloSquare(std::shared_ptr<Window> window);
void bunchOfCubes(GLFWwindow * window);

int main(void)
{
	srand(time(nullptr));
	std::shared_ptr<Window> window = Window::create(800, 600, "New Window");
	// texturedSquare(window);
	helloSquare(window);
	return 0;
}

void helloSquare(std::shared_ptr<Window> window) {
	std::shared_ptr<Texture> giraffe_tex = Texture::create("/home/gogotchuri/Workspace/OpenGL/GraphicsRenderer/Renderer/res/textures/Giraffe.jpg");
	Renderer2D::init();
	OrthographicCamera camera(0.0f, 700.0f, 0.0f, 450.0f);
	// render loop
	// -----------
	while (window->isOpen())
	{
		// input
		// -----
		closeOnEnter(window);
		// render
		// ------
		RenderCommand::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		RenderCommand::clear();
		Renderer2D::startScene(camera);
		// for(int x = 10; x < 700; x += 10)
		// 	for(int y = 10; y < 450; y += 10)
		// 		Renderer2D::drawRect(glm::vec2(x, y), glm::vec2(9, 9), giraffe_tex);
		Renderer2D::drawRect(glm::vec2(20, 20), glm::vec2(15, 15), giraffe_tex);
		Renderer2D::endScene();
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		window->swapBuffers();
		glfwPollEvents();
	}
	glfwTerminate();
}

void texturedSquare(std::shared_ptr<Window> window) {
	//Triangle vertices to draw
	float vertices[] =
	{
		-0.5f,  0.5f, 0,    0,    1.0f,
		0.5f,  0.5f, 0,    1.0f, 1.0f,
		0.5f, -0.5f, 0,    1.0f, 0,
		-0.5f, -0.5f, 0,    0,    0
	};

	uint32_t indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	std::shared_ptr<VertexBuffer> vb = VertexBuffer::create(vertices, sizeof(float), 20);
	VertexBufferLayout vbl;
	vbl.push(LayoutElement(ShaderDataType::Float3, "vertex_coordiates"));
	vbl.push(LayoutElement(ShaderDataType::Float2, "texture_sampling" ));
	vb->setLayout(vbl);

	std::shared_ptr<IndexBuffer> ib = IndexBuffer::create(indices, 6);

	std::shared_ptr<VertexArray> va = VertexArray::create();

	va->addVertexBuffer(vb);
	va->setIndexBuffer(ib);

	std::shared_ptr<Shader> shader = Shader::create(std::string("/home/gogotchuri/Workspace/OpenGL/GraphicsRenderer/Renderer/res/shaders/TexturedSquare.shader"));

	std::shared_ptr<Texture> tex = Texture::create("/home/gogotchuri/Workspace/OpenGL/GraphicsRenderer/Renderer/res/textures/Giraffe.jpg");
	tex->bind();
	int loc = 0;
	shader->setUniform("u_texture", ShaderDataType::Int1, &loc);

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.1, 0.1, 0.1));


	/* Loop until the user closes the window */
	while (window->isOpen())
	{
		closeOnEnter(window);
		/*Clear screen*/
		Renderer::clearColor(1.0f, 0.3f, 0.3f, 1.0f);
		//Draw Triangle
		Renderer::draw(va, ib, shader);
		shader->setUniform("transform", ShaderDataType::Mat4, glm::value_ptr(trans));
		if (trans[0][0] < 2)
			trans = glm::scale(trans, glm::vec3(1.02, 1.02, 1.02));
		else
			trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
		/* Swap front and back buffers */
		window->swapBuffers();

		/* Poll for and process events */
		glfwPollEvents();
	}

}

void closeOnEnter(GLFWwindow * window) {
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void closeOnEnter(std::shared_ptr<Window> window) {
	if (glfwGetKey((GLFWwindow*)window->getBaseWindow(), GLFW_KEY_ENTER) == GLFW_PRESS)
		window->close();
}

void bunchOfCubes(GLFWwindow * window) {
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -5.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -7.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	std::shared_ptr<VertexArray> va = VertexArray::create();
	std::shared_ptr<VertexBuffer> vb = VertexBuffer::create(vertices, sizeof(float), 30*6);
	VertexBufferLayout layout;
	layout.push(LayoutElement(ShaderDataType::Float3, "position_coords"));
	layout.push(LayoutElement(ShaderDataType::Float2, "texture_sampling"));
	vb->setLayout(layout);

	std::shared_ptr<Shader> shader = Shader::create("/home/gogotchuri/Workspace/OpenGL/GraphicsRenderer/Renderer/res/shaders/MvpPractice.shader");
	std::shared_ptr<Texture> giraffe_textue = Texture::create("/home/gogotchuri/Workspace/OpenGL/GraphicsRenderer/Renderer/res/textures/Giraffe.jpg");
	giraffe_textue->bind();
	int loc = 0;
	shader->setUniform("u_texture", ShaderDataType::Int1, &loc);

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.1, 0.1, 0.1));

	glm::mat4 identity = glm::mat4(1.0f);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		closeOnEnter(window);
		/*Clear screen*/
		Renderer::clearColor(1.0f, 0.3f, 0.3f, 1.0f);
		//Draw Triangle
		shader->setUniform("proj", ShaderDataType::Mat4, glm::value_ptr(identity));
		shader->setUniform("view", ShaderDataType::Mat4, glm::value_ptr(identity));
		shader->setUniform("model", ShaderDataType::Mat4, glm::value_ptr(identity));

		shader->bind();
		va->bind();

		glDrawArrays(GL_TRIANGLES, 0, 36);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
}