/**
 * This file doesn't contain anything important for this library,
 * it's used just for practice and fast implementation testing
*/

#include <iostream>
#include "Renderer.h"
#include "Texture.h"
#include "RendererAPI.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <slogger/slogger.h>

using namespace std;

void closeOnEnter(GLFWwindow * window);
void twoTriangles(GLFWwindow * window);
void Square(GLFWwindow * window);
void helloSquare(GLFWwindow * window);
void bunchOfCubes(GLFWwindow * window);

int main(void)
{
	GLFWwindow* window = Renderer::initWindow(700, 450, "GLFW Window");
	helloSquare(window);
	return 0;
}

void helloSquare(GLFWwindow * window) {

	std::shared_ptr<Shader> shader = Shader::create(
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

	shared_ptr<VertexBuffer> vb = VertexBuffer::create(vertices, sizeof(float), 12);
	VertexBufferLayout layout;
	layout.push(LayoutElement(ShaderDataType::Float3, "Vertex_coords"));
	vb->setLayout(layout);
	shared_ptr<IndexBuffer> ib = IndexBuffer::create(indices, 6);

	shared_ptr<VertexArray> va = VertexArray::create();
	va->addVertexBuffer(vb);
	va->setIndexBuffer(ib);

	va->unbind();

	SLOGGER_INIT_FILE("/home/gogotchuri/Workspace/OpenGL/GraphicsRenderer/log.txt");
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	camera.setFixedTarget(glm::vec3(0.0f, 0.0f, 0.0f));
	float slide = 0;
	float change = 0.01;
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		if(slide > 1){
			SLOGGER_INFO(std::string("Decreasing slide!"));
			change = -0.005;
		}
		if(slide < -1) {
			SLOGGER_ERROR(std::string("Increasing slide!"));
			change = 0.005;
		}
		slide += change;
		// input
		// -----
		closeOnEnter(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		float radius = 3.0f;
        float camX   = sin(glfwGetTime()) * radius;
        float camZ   = cos(glfwGetTime()) * radius;
		camera.setPosition(glm::vec3(camX, 0, camZ));
        glm::mat4 view_proj = camera.getViewProjectionMatrix();
		shader->setUniform("u_view_projection", ShaderDataType::Mat4, glm::value_ptr(view_proj));

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0, 0, 0));

		shader->setUniform("u_model", ShaderDataType::Mat4, glm::value_ptr(model));
		// draw our first triangle
		shader->bind();
		va->bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	SLOGGER_CLOSE();
	glfwTerminate();
}

void texturedSquare(GLFWwindow * window) {
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

	std::shared_ptr<Shader> shader = Shader::create(std::string("res/shaders/TexturedSquare.shader"));

	std::shared_ptr<Texture> tex = Texture::create("res/textures/21122475_1493887597347506_3596902192094063919_o.jpg");
	tex->bind();
	int loc = 0;
	shader->setUniform("u_texture", ShaderDataType::Int1, &loc);

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.1, 0.1, 0.1));


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
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
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

}

void closeOnEnter(GLFWwindow * window) {
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
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