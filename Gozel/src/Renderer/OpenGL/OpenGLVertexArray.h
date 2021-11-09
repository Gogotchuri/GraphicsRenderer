/*
 * OpenGLVertexArray.h
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#ifndef OPENGL_OPENGLVERTEXARRAY_H_
#define OPENGL_OPENGLVERTEXARRAY_H_

#include <glad/glad.h>
#include "VertexArray.h"

class OpenGLVertexArray : public VertexArray{
public:
	OpenGLVertexArray();
	virtual ~OpenGLVertexArray();

	virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vb) override;
	virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& ib) override;

	virtual void bind() const override;
	virtual void unbind() const override;

	virtual std::vector<std::shared_ptr<VertexBuffer> > & getVertexBuffers() override;
	virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const override;
private:
	uint32_t vao_id;
	uint32_t vb_index;
	std::vector<std::shared_ptr<VertexBuffer> > vertex_buffers;
	std::shared_ptr<IndexBuffer> index_buffer;
};

#endif /* OPENGL_OPENGLVERTEXARRAY_H_ */
