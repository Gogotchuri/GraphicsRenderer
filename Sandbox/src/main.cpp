/**
 * This file doesn't contain anything important for this library,
 * it's used just for practice and fast implementation testing
*/

#include <iostream>
#include "Texture.h"
#include "RenderCommand.h"
#include "Camera.h"
#include <time.h>
#include "Window.h"
#include "Renderer2D.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <slogger/slogger.h>

using namespace std;

void newInterface(std::shared_ptr<Window> window);

int main(void)
{
	srand(time(nullptr));
	std::shared_ptr<Window> window = Window::create(800, 600, "New Window");
	window->setVSync(true);
	newInterface(window);
	return 0;
}

void newInterface(std::shared_ptr<Window> window) {
	//std::shared_ptr<Texture> giraffe_tex = Texture::create("res/textures/Giraffe.jpg");
	std::shared_ptr<Texture> Mario = Texture::create("res/textures/Mario.png");
	Renderer2D::init();
	Camera camera = Camera();
//	camera.setFixedTarget(glm::vec3(0, 0, 0));
	float x = 0;
	float y = 0;
	while (window->isOpen()) {
		// closeOnEnter(window);
		// if (glfwGetKey((GLFWwindow*)(window->getBaseWindow()), GLFW_KEY_LEFT) == GLFW_PRESS) x += 0.1;
		// if (glfwGetKey((GLFWwindow*)(window->getBaseWindow()), GLFW_KEY_RIGHT) == GLFW_PRESS) x -= 0.1;
		// if (glfwGetKey((GLFWwindow*)(window->getBaseWindow()), GLFW_KEY_UP) == GLFW_PRESS) y -= 0.1;
		// if (glfwGetKey((GLFWwindow*)(window->getBaseWindow()), GLFW_KEY_DOWN) == GLFW_PRESS) y += 0.1;
		camera.setPosition(glm::vec3(x, y, 3.0f));
		RenderCommand::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		RenderCommand::clear();
		Renderer2D::startScene(camera);
		Renderer2D::drawRect(glm::vec2(-0.5, 0), glm::vec2(1.0f, 1.0f), Mario, glm::vec3(0.0f, 0.0f, 1.0f), -90.0f);
		Renderer2D::drawRect(glm::vec2(0.5, 0), glm::vec2(1.0f, 1.0f), Mario);
		Renderer2D::endScene();
		window->onUpdate();
		// glfwPollEvents();
	}
	// glfwTerminate();
}