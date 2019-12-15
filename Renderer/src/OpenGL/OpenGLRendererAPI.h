/*
 * OpenGLRendererAPI.h
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#ifndef OPENGL_OPENGLRENDERERAPI_H_
#define OPENGL_OPENGLRENDERERAPI_H_


#include "RendererAPI.h"
#include <glad/glad.h>

class OpenGLRendererAPI : public RendererAPI {
public:
	virtual ~OpenGLRendererAPI();
	virtual void init() override;
	virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
	virtual void setClearColor(float r, float g, float b, float a) override;
	virtual void clear() override;

	virtual void drawVA(const std::shared_ptr<VertexArray>& vertexArray) override;
};

#endif /* OPENGL_OPENGLRENDERERAPI_H_ */
