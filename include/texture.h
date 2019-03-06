#ifndef TEXTURE_H
#define TEXTURE

#include "glad.h"
#include <string>

class Texture
{
private:
	GLuint _id;

	const char* _source;
	unsigned char* _data;
	int width, height, nrChannels;
	GLint format;
	GLenum prefferedTarget;
	GLenum prefferedChannel;
public:

	Texture(const char* path, GLint format, GLenum target, GLenum channel);

	~Texture();

	Texture(Texture& tex) = delete; //no copying because unique pointer and why would you need to copy a texture
	Texture& operator=(Texture& tex) = delete;

	GLuint getID() const noexcept;

	int getWidth() const noexcept;

	int getHeight() const noexcept;

	int getnrChannels() const noexcept;

	std::string getPath() const noexcept;

	const bool IsLoaded() const noexcept;

	void bind() const;

	void Load(const char* path, GLint format, GLenum target);
};

#endif
