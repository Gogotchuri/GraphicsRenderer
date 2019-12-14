/*
 * OpenGLBuffer.cpp
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#include "OpenGLBuffer.h"

/////////////////////////////////////////////////////////////////////////////
// VertexBuffer /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, uint32_t unit_size, unsigned int count, DrawHint draw_hint)
	: count(count)
{
	glGenBuffers(1, &buff_id);
	glBindBuffer(GL_ARRAY_BUFFER, buff_id);
	glBufferData(GL_ARRAY_BUFFER, unit_size * count, data, draw_hint);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &buff_id);
}

void OpenGLVertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, buff_id);
}

void OpenGLVertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/////////////////////////////////////////////////////////////////////////////
// IndexBuffer //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* indices, unsigned int count, DrawHint draw_hint)
	: count(count)
{
	glGenBuffers(1, &buff_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buff_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, draw_hint);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &buff_id);
}

void OpenGLIndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buff_id);
}

void OpenGLIndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
