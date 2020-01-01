#include <OpenGL/GLWindow.h>
#include <assert.h>

GLWindow::GLWindow(unsigned int width, unsigned int height, const char * name) {
    /* Initialize the library */
	assert(glfwInit());

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, name, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		SLOGGER_ERROR("GLFW window initialization failed! \n");
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
		SLOGGER_ERROR("Failed to initialize GLAD \n");
		assert(false);
	}
	//glEnable(GL_DEPTH_TEST);
	/*Opengl version*/
	SLOGGER_INFO((char*)glGetString(GL_VERSION));
	SLOGGER_INFO("\n");
}

bool GLWindow::isOpen() {
    return (bool) !glfwWindowShouldClose(window);
}

void GLWindow::close() {
    glfwSetWindowShouldClose(window, true);
}

void GLWindow::swapBuffers() {
    glfwSwapBuffers(window);
}

void * GLWindow::getBaseWindow() {
	return (void *)window;
}