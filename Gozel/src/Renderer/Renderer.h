#pragma once

#include "VertexArray.h"
#include "Shader.h"
#include "Buffer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assert.h>
class Renderer
{
public:
	static GLFWwindow* initWindow(unsigned int width, unsigned int height, const std::string& title);
	static void draw(const std::shared_ptr<VertexArray>& vao, const std::shared_ptr<IndexBuffer>& ibo, const std::shared_ptr<Shader>& shader);
	static void draw(const std::shared_ptr<VertexArray>& vao, const std::shared_ptr<Shader>& shader, unsigned int from, unsigned int to);
	static void clearColor(float red, float green, float blue, float alpha = 1.0f);
	static void clear();

private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height){ glViewport(0, 0, width, height); }
};