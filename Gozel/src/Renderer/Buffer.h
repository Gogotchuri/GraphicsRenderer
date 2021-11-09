/*
 * Buffer.h
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <vector>
#include <memory>
#include "VertexBufferLayout.h"

/*VertexBuffer Interface*/
class VertexBuffer {
public:
	/*Deletes buffer*/
	virtual ~VertexBuffer() = default;

	virtual void setLayout(const VertexBufferLayout& layout) = 0;
	virtual VertexBufferLayout& getLayout() = 0;

	/*Returns element count passed to the buffer*/
	virtual unsigned int getCount() const = 0;

	/*Binds this buffer to the target*/
	virtual void bind() const = 0;
	/*Unbinds this buffer from the target*/
	virtual void unbind() const = 0;

	static std::shared_ptr<VertexBuffer> create(const void * data, uint32_t unit_size, unsigned int count);
};

/*General buffer class*/
class IndexBuffer {
public:
	/*Deletes buffer*/
	virtual ~IndexBuffer() = default;

	/*Returns element count passed to the buffer*/
	virtual unsigned int getCount() const = 0;

	/*Binds this buffer to the target*/
	virtual void bind() const = 0;
	/*Unbinds this buffer from the target*/
	virtual void unbind() const = 0;

	static std::shared_ptr<IndexBuffer> create(const uint32_t * data, unsigned int count);

};


#endif /* BUFFER_H_ */
