#pragma once

#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>

class Shader
{
private:/*
	GLenum _shaderType;
	std::string _source;
	GLuint _id;
*/
public:
	unsigned int ID;

//	Shader(std::string source, GLenum shaderType);
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
//	~Shader();

//	GLuint getId() { return _id; }

	void use();

	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, glm::mat4 mat) const;
};
