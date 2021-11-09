#include "OpenGLTexture.h"
#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <assert.h>
#include <slogger/slogger.h>

OpenGLTexture::OpenGLTexture(const std::string& filepath)
	:gl_texture_id(0), filepath(filepath), height(0), width(0), bpp(0)
{
	unsigned char * local_buffer;
	stbi_set_flip_vertically_on_load(1);
	local_buffer = stbi_load(filepath.c_str(), &width, &height, &bpp, 4);
	if (!local_buffer) {
		SLOGGER_ERROR("Texture isn't on the filepath: " + filepath);
		assert(false);
	}
	std::cout <<  width << height << std::endl;
	glGenTextures(1, &gl_texture_id);
	bind();
	//TODO Exception handling
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer);
	unbind();

	if (local_buffer)
		stbi_image_free(local_buffer);
}

OpenGLTexture::~OpenGLTexture()
{
	glDeleteTextures(1, &gl_texture_id);
}

void OpenGLTexture::bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, gl_texture_id);
}

void OpenGLTexture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
