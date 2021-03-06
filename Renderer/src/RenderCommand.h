/*
 * RenderCommand.h
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#ifndef RENDERCOMMAND_H_
#define RENDERCOMMAND_H_

#include <memory>
#include "RendererAPI.h"

class RenderCommand {
public:
	static void init() {
		renderer_API->init();
	}

	static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		renderer_API->setViewport(x, y, width, height);
	}

	static void setClearColor(float r, float g, float b, float a) {
		renderer_API->setClearColor(r, g, b, a);
	}

	static void clear() {
		renderer_API->clear();
	}

	//TODO change name to mention elements/indexes
	static void drawVA(const std::shared_ptr<VertexArray>& vertexArray){
		renderer_API->drawVA(vertexArray);
	}

private:
	static std::shared_ptr<RendererAPI> renderer_API;
};

#endif /* RENDERCOMMAND_H_ */
