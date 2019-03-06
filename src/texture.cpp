#include "../include/texture.h"

#include "stb_image.h"
#include <iostream>

Texture::Texture(const char* path, GLint format, GLenum target, GLenum channel)
{
	glGenTextures(1, &_id);
	glActiveTexture(channel);
	glBindTexture(target, _id);
	_source = path;
	prefferedTarget = target;
	prefferedChannel = channel;
	this->format = format;
	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Load(path, format, target);
	glBindTexture(prefferedTarget, 0);
}

Texture::~Texture()
{
	stbi_image_free(_data);
}

GLuint Texture::getID() const noexcept
{
	return _id;
}

int Texture::getWidth() const noexcept
{
	return width;
}

int Texture::getHeight() const noexcept
{
	return height;
}

int Texture::getnrChannels() const noexcept
{
	return nrChannels;
}

std::string Texture::getPath() const noexcept //to read the information
{
	return _source;
}

const bool Texture::IsLoaded() const noexcept
{
	return _data != nullptr;
}

void Texture::bind() const
{
	glBindTexture(prefferedTarget, _id);
}

void Texture::Load(const char* path, GLint format, GLenum target)
{
	_data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (_data)
	{
		glTexImage2D(target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, _data);
		glGenerateMipmap(target);
	}
	else
	{
		std::cout << "ERROR LOADING IMAGE\n";
	}
}
