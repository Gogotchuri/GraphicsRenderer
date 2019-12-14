#ifndef OPENGL_OPENGLTEXTURE_H_
#define OPENGL_OPENGLTEXTURE_H_

#include "Texture.h"

class OpenGLTexture : public Texture
{
public:
	OpenGLTexture(const std::string& filepath);
	virtual ~OpenGLTexture();
	virtual void bind(unsigned int slot = 0) const;
	virtual void unbind() const;

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }
private:
	unsigned int gl_texture_id;
	std::string filepath;
	int width, height, bpp;
};

#endif //OPENGL_OPENGLTEXTURE_H_
