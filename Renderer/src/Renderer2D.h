/*
 * Renderer2D.h
 *
 *  Created on: Dec 12, 2019
 *      Author: Gogotchuri
 */

#ifndef RENDERER2D_H_
#define RENDERER2D_H_
#include <glm/glm.hpp>
#include <memory>

#include "RenderCommand.h"

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Buffer.h"
#include "Camera.h"
#include "Texture.h"
class Renderer2D {
public:
    static void init();
    static void startScene(const OrthographicCamera& camera);
    static void startScene(const Camera& camera);
    static void endScene();
    //Rectangle drawing
    static void drawRect(const glm::vec3& position, const glm::vec2& size);
    static void drawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color);
    static void drawRect(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture> texture);

    static void drawRect(const glm::vec2& position, const glm::vec2& size);
    static void drawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color);
    static void drawRect(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture> texture);
private:

    static std::shared_ptr<VertexArray> va;
    static std::shared_ptr<Shader> color_shader, texture_shader;
};

#endif /* RENDERER2D_H_ */
