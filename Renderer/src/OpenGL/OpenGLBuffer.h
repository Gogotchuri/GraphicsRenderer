/*
 * OpenGLBuffer.h
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#ifndef OPENGL_OPENGLBUFFER_H_
#define OPENGL_OPENGLBUFFER_H_

#include "Buffer.h"
#include <glad\glad.h>


//Draw hints
enum DrawHint {
	STREAM_DRAW = GL_STREAM_DRAW,
	STATIC_DRAW = GL_STATIC_DRAW,
	DYNAMIC_DRAW = GL_DYNAMIC_DRAW
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++Vertex Buffer+++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class OpenGLVertexBuffer : public VertexBuffer {
public:
	/**
	 * Creates buffer from given data pointer
	 * @param data pointer to the data
	 * @param unit_size size of units in the passed data (i.e floats, chars, ...)
	 * @param count number of elements in data array/matrix
	 * !after the constuctor call, buffer is bound
	 */
	OpenGLVertexBuffer(const void * data, uint32_t unit_size, unsigned int count, DrawHint draw_hint = STATIC_DRAW);
	/*Deletes buffer*/
	virtual ~OpenGLVertexBuffer();

	/*Returns element count passed to the buffer*/
	virtual unsigned int getCount() const override { return count; }

	virtual void setLayout(const VertexBufferLayout& layout) override { this->layout = layout; }
	virtual VertexBufferLayout& getLayout() override { return layout; }

	/*Binds this buffer to the target*/
	virtual void bind() const override;
	/*Unbinds this buffer from the target*/
	virtual void unbind() const override;

protected:
	uint32_t buff_id;
	unsigned int count;
	VertexBufferLayout layout;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++Index Buffer++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class OpenGLIndexBuffer : public IndexBuffer {
public:
	/**
	 * Creates buffer from given data pointer
	 * @param data pointer to the data
	 * @param unit_size size of units in the passed data (i.e floats, chars, ...)
	 * @param count number of elements in data array/matrix
	 * !after the constuctor call, buffer is bound
	 */
	OpenGLIndexBuffer(const uint32_t * indices, unsigned int count, DrawHint draw_hint = STATIC_DRAW);
	/*Deletes buffer*/
	virtual ~OpenGLIndexBuffer();

	/*Returns element count passed to the buffer*/
	virtual unsigned int getCount() const override { return count; }

	/*Binds this buffer to the target*/
	virtual void bind() const override;
	/*Unbinds this buffer from the target*/
	virtual void unbind() const override;

protected:
	unsigned int buff_id;
	unsigned int count;
};
#endif /* OPENGL_OPENGLBUFFER_H_ */
