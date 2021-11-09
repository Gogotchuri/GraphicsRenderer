/*
 * OpenGLVertexArray.cpp
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#include "OpenGLVertexArray.h"


static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Float1:   return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Int1:     return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
	}

	return 0;
}

OpenGLVertexArray::OpenGLVertexArray()
	:vb_index(0), vao_id(0)
{
	glGenVertexArrays(1, &vao_id);
}

OpenGLVertexArray::~OpenGLVertexArray(){
	glDeleteVertexArrays(1, &vao_id);
}

void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vb) {
	vertex_buffers.push_back(vb);
	/*Bind this vao*/
	this->bind();
	/*Bind vertex/index buffer*/
	vb->bind();

	const auto& elements = vb->getLayout().getElements();
	for (const auto& elem : elements) {
		//Enable attrib array
		glEnableVertexAttribArray(vb_index);
		//pass layout
		glVertexAttribPointer(vb_index, elem.elem_count, ShaderDataTypeToOpenGLBaseType(elem.type), elem.normalized ? GL_TRUE : GL_FALSE, vb->getLayout().getStride(), (const void*)elem.offset);
		//Incrementing for every subsequent vertex attribute
		vb_index++;
	}
}

void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& ib) {
	this->bind();
	ib->bind();
	index_buffer = ib;
}

void OpenGLVertexArray::bind() const {
	glBindVertexArray(vao_id);
}
void OpenGLVertexArray::unbind() const {
	glBindVertexArray(0);
}

std::vector<std::shared_ptr<VertexBuffer> > & OpenGLVertexArray::getVertexBuffers() {
	return vertex_buffers;
}

std::shared_ptr<IndexBuffer> OpenGLVertexArray::getIndexBuffer() const {
	return index_buffer;
}
