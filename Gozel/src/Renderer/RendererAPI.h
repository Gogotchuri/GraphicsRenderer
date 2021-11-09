/*
 * RendererAPI.h
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#ifndef RENDERERAPI_H_
#define RENDERERAPI_H_

#include <memory>
#include "VertexArray.h"

class RendererAPI {
public:
	enum API
	{
		None = 0, OpenGL
	};
	virtual ~RendererAPI() = default;
	virtual void init() = 0;
	virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
	virtual void setClearColor(float r, float g, float b, float a) = 0;
	virtual void clear() = 0;

	virtual void drawVA(const std::shared_ptr<VertexArray>& vertexArray) = 0;
	inline static API getAPI() { return current_API; };
	static std::shared_ptr<RendererAPI> create();
private:
	static API current_API;
};

#endif /* RENDERERAPI_H_ */
