#include "../include/shader.h"

/*
Shader::Shader(std::string source, GLenum shaderType) : _id(0)
{
	if(!(shaderType == GL_VERTEX_SHADER || shaderType == GL_GEOMETRY_SHADER || shaderType == GL_FRAGMENT_SHADER))
	{
		std::cout << "Invalid shader type\n";
		throw std::exception();
	}

	//load shader
	std::ifstream fp(source);
	if(fp.is_open())
	{
		std::stringstream buf;
		buf << fp.rdbuf();

		if((_id = glCreateShader(shaderType) != 0)
		{
			_source = buf.str();
			const char* sourceChar = _source.c_str();
			glShaderSource(_id, 1, &sourceChar, nullptr);
		} else
		{
			std::cout << "GL could not create new shader\n";
			throw std::exception();
		}
	} else
	{
		std::cout << "GLSL source is not found!\n";
		throw std::exception();
	}
	//compile shader
	glCompileShader(_id);
	GLint status = 0;
	glGetShaderiv(_id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* infoLog = (GLchar)malloc(sizeof(GLchar) * (infoLogLength + 1);
		glGetShaderInfoLog(_id, infoLogLength, nullptr, infoLog);
		std::cout << "Shader could not compile: " << infoLog << "\n";
		throw std::exception();

		free(infoLog);
	}
}

Shader::~Shader()
{
	glDeleteShader(_id);
}*/

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::ifstream vShaderFile, fShaderFile;

	vShaderFile.open(vertexPath);
	fShaderFile.open(fragmentPath);

	//put shaders into strings :::::: ADD IN SAFETY
	std::string vertexCode((std::istreambuf_iterator<char>(vShaderFile)),
		(std::istreambuf_iterator<char>())); vertexCode += "\n";
	vShaderFile.close();
	std::string fragmentCode((std::istreambuf_iterator<char>(fShaderFile)),
		(std::istreambuf_iterator<char>())); fragmentCode += "\n";
	fShaderFile.close();

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	//compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	//vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION::FAILED\n" << infoLog << std::endl;
	}

	//fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED\n" << infoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, glm::mat4 mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}
