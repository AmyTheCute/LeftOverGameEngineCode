#include "ShaderProgram.h"



ShaderProgram::ShaderProgram(const char* vertex_file, const char* fragment_file)
{
	std::ifstream vertex, fragment;
	std::string tempString;

	vertex.open(vertex_file);
	fragment.open(fragment_file);

	if (vertex.is_open()) {
		while (std::getline(vertex, tempString)) {
			vertex_code.append(tempString);
			vertex_code.append("\n");
		}
	}
	vertex.close();

	if (fragment.is_open()) {
		while (std::getline(fragment, tempString)) {
			fragment_code.append(tempString);
			fragment_code.append("\n");
		}
	}
	fragment.close();

	CompileShaders();
}

ShaderProgram::ShaderProgram()
{

}


ShaderProgram::~ShaderProgram()
{
	glUseProgram(0);
	glDeleteProgram(shaderProgram);
}

void ShaderProgram::setShaders(const char * vertex_file, const char * fragment_file)
{
	std::ifstream vertex, fragment;
	std::string tempString;

	vertex.open(vertex_file);
	fragment.open(fragment_file);

	if (vertex.is_open()) {
		while (std::getline(vertex, tempString)) {
			vertex_code.append(tempString);
			vertex_code.append("\n");
		}
	}
	vertex.close();

	if (fragment.is_open()) {
		while (std::getline(fragment, tempString)) {
			fragment_code.append(tempString);
			fragment_code.append("\n");
		}
	}
	fragment.close();

	CompileShaders();
}

void ShaderProgram::CompileShaders()
{

	int sucsess;
	char infoLog[512];


	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragment_source = fragment_code.c_str();
	glShaderSource(fragment, 1, &fragment_source, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &sucsess);

	if (!sucsess) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	const char* vertex_source = vertex_code.c_str();
	glShaderSource(vertex, 1, &vertex_source, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &sucsess);

	if (!sucsess) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertex);
	glAttachShader(shaderProgram, fragment);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &sucsess);

	if (!sucsess) {
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKNING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void ShaderProgram::use()
{
	glUseProgram(shaderProgram);
}

void ShaderProgram::setUniform(const char* name, const glm::vec4& value)
{
	int uniformLocation = glGetUniformLocation(shaderProgram, name);
	glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);

}

void ShaderProgram::setUniform(const char * name, const float & value1, const float & value2, const float & value3, const float & value4)
{
	int uniformLocation = glGetUniformLocation(shaderProgram, name);
	glUniform4f(uniformLocation, value1, value2, value3, value4);
}

void ShaderProgram::setUniform(const char* name, const glm::vec3& value)
{
	int uniformLocation = glGetUniformLocation(shaderProgram, name);
	glUniform3f(uniformLocation, value.x, value.y, value.z);

}

void ShaderProgram::setUniform(const char * name, const float & value1, const float & value2, const float & value3)
{
	int uniformLocation = glGetUniformLocation(shaderProgram, name);
	glUniform3f(uniformLocation, value1, value2, value3);
}

void ShaderProgram::setUniform(const char* name, const glm::vec2& value)
{
	int uniformLocation = glGetUniformLocation(shaderProgram, name);
	glUniform2f(uniformLocation, value.x, value.y);
}

void ShaderProgram::setUniform(const char * name, const float & value1, const float & value2)
{
	int uniformLocation = glGetUniformLocation(shaderProgram, name);
	glUniform2f(uniformLocation, value1, value2);
}

void ShaderProgram::setUniform(const char* name, const float& value)
{
	int uniformLocation = glGetUniformLocation(shaderProgram, name);
	glUniform1f(uniformLocation, value);
}

void ShaderProgram::setUniform(const char* name, const glm::dvec4& value)
{
	int uniformLocation = glGetUniformLocation(shaderProgram, name);
	glUniform4d(uniformLocation, value.x, value.y, value.z, value.w);
}

void ShaderProgram::setUniform(const char* name, const glm::dvec3& value)
{
	int uniformLocation = glGetUniformLocation(shaderProgram, name);
	glUniform3d(uniformLocation, value.x, value.y, value.z);
}
void ShaderProgram::setUniform(const char* name, const glm::dvec2& value) {
	int uniformLocation = glGetUniformLocation(shaderProgram, name);
	glUniform2d(uniformLocation, value.x, value.y);
}

void ShaderProgram::setUniform(const char* name, const double& value)
{
	int uniformLocation = glGetUniformLocation(shaderProgram, name);
	glUniform1d(uniformLocation, value);
}

void ShaderProgram::setUniform(const char* name, const bool & value)
{
	int uniformLocation = glGetUniformLocation(shaderProgram, name);
	glUniform1i(uniformLocation, value);
}

void ShaderProgram::setUniform(const char* name, const int& value)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name), value);
}

void ShaderProgram::setUniform(const char* name, const glm::mat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, glm::value_ptr(value));
}
void ShaderProgram::setUniform(const char* name, const glm::mat3& value)
{
	glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, glm::value_ptr(value));
}
void ShaderProgram::setUniform(const char* name, const glm::mat2& value)
{
	glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, glm::value_ptr(value));
}