#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>
#include <memory>

class Texture {
public:
	virtual ~Texture() = default;

	virtual void bind(unsigned int slot = 0) const = 0;
	virtual void unbind() const = 0;

	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;
	static std::shared_ptr<Texture> create(const std::string& path);
};

#endif //TEXTURE_H_