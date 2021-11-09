/*
 * VertexArray.h
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#ifndef VERTEXARRAY_H_
#define VERTEXARRAY_H_

#include "Buffer.h"

class VertexArray
{
public:
	virtual ~VertexArray() = default;

	virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vb) = 0;
	virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& ib) = 0;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	virtual std::vector<std::shared_ptr<VertexBuffer> > & getVertexBuffers() = 0;
	virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const = 0;

	static std::shared_ptr<VertexArray> create();
};

#endif /* VERTEXARRAY_H_ */
