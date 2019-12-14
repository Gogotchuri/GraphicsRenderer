#include "Renderer.h"

void Renderer::clearColor(float red, float green, float blue, float alpha) {
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

GLFWwindow * Renderer::initWindow(unsigned int width, unsigned int height, const std::string& title)
{
	GLFWwindow* window;

	/* Initialize the library */
	assert(glfwInit());

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		printf("GLFW window initilization failed! \n");
		assert(false);
	}


	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/*Viewports for scaling and callback*/
	//glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD \n");
		assert(false);
	}
	//glEnable(GL_DEPTH_TEST);
	/*Opengl version*/
	printf((char*)glGetString(GL_VERSION));
	printf("\n");

	return window;
}

void Renderer::draw(const std::shared_ptr<VertexArray>& vao, const std::shared_ptr<IndexBuffer>& ibo, const std::shared_ptr<Shader>& shader)
{
	//Draw Triangle
	//Enable compiled shaders
	shader->bind();

	//Bind vertex array (configuration of vertex buffer)
	vao->bind();
	ibo->bind();
	//Draw bound array
	glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::draw(const std::shared_ptr<VertexArray>& vao, const std::shared_ptr<Shader>& shader, unsigned int from, unsigned int to) {
	//Draw Triangle
	//Enable compiled shaders
	shader->bind();

	//Bind vertex array (configuration of vertex buffer)
	vao->bind();
	//Draw bound array
	glDrawArrays(GL_TRIANGLES, from, to);
}
