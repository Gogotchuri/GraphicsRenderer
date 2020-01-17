/*
 * VertexBufferLayou.h
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#ifndef VERTEXBUFFERLAYOUT_H_
#define VERTEXBUFFERLAYOUT_H_

#include <vector>
#include <string>

enum class ShaderDataType{
	None = 0, Float1, Float2, Float3, Float4, Int1, Int2, Int3, Int4, Mat2, Mat3, Mat4
};

static uint32_t getShaderDataTypeSize(ShaderDataType type){
	switch(type){
		case ShaderDataType::Float1:   return sizeof(float);
		case ShaderDataType::Float2:   return sizeof(float) * 2;
		case ShaderDataType::Float3:   return sizeof(float) * 3;
		case ShaderDataType::Float4:   return sizeof(float) * 4;
		case ShaderDataType::Int1:     return sizeof(int);
		case ShaderDataType::Int2:     return sizeof(int) * 2;
		case ShaderDataType::Int3:     return sizeof(int) * 3;
		case ShaderDataType::Int4:     return sizeof(int) * 4;
		case ShaderDataType::Mat2:     return sizeof(float) * 4 * 4;
		case ShaderDataType::Mat3:     return sizeof(float) * 3 * 3;
		case ShaderDataType::Mat4:     return sizeof(float) * 4 * 4;
		//TODO
		//Others should be added
	}

	//TODO create assertion
	return 0;
}

static uint32_t getShaderDataTypeCount(ShaderDataType type){
	switch(type){
		case ShaderDataType::Float1:   return 1;
		case ShaderDataType::Float2:   return 2;
		case ShaderDataType::Float3:   return 3;
		case ShaderDataType::Float4:   return 4;
		case ShaderDataType::Int1:     return 1;
		case ShaderDataType::Int2:     return 2;
		case ShaderDataType::Int3:     return 3;
		case ShaderDataType::Int4:     return 4;
		case ShaderDataType::Mat2:     return 4 * 4;
		case ShaderDataType::Mat3:     return 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4;
		//TODO
		//Others should be added
	}

	//TODO create assertion
	return 0;
}

struct LayoutElement {

	ShaderDataType type;
	std::string name;
	uint32_t elem_count;
	bool normalized;
	uint32_t size;
	uint32_t offset;

	LayoutElement(ShaderDataType type, std::string name, bool normalized = false)
		: type(type), name(name), elem_count(getShaderDataTypeCount(type)),
			normalized(normalized), size(getShaderDataTypeSize(type)), offset(0) {}
};


class VertexBufferLayout
{
public:
	VertexBufferLayout() : stride(0) {}

	void push(LayoutElement elem) {
		elem.offset = stride;
		elements.push_back(elem);
		stride += elem.size;
	}

	inline const std::vector<LayoutElement>& getElements() const { return elements; }

	inline unsigned int getStride() const { return stride; }
private:
	uint32_t stride;
	std::vector<LayoutElement> elements;
};

#endif /* VERTEXBUFFERLAYOUT_H_ */
