#ifndef SHADER_H
#define SHADER_H

#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <string>

class Shader
{
public:
	unsigned int ID;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void use();

	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, glm::mat4 mat) const;
};

#endif
