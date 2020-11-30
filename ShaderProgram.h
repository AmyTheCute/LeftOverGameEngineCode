#pragma once
#include <GL/glew.h> // include GLEW and new version of GL on Windows

#include <fstream>
#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ShaderProgram
{
public:
	ShaderProgram(const char * vertex_file, const char * fragment_file);
	ShaderProgram();
	~ShaderProgram();

	void setShaders(const char * vertex_file, const char * fragment_file);

	void use();
	void setUniform(const char* name, const glm::vec4& value);
	void setUniform(const char* name, const float& value1, const float& value2, const float& value3, const float& value4);
	void setUniform(const char* name, const glm::vec3& value);
	void setUniform(const char* name, const float& value1, const float& value2, const float& value3);
	void setUniform(const char* name, const glm::vec2& value);
	void setUniform(const char* name, const float& value1, const float& value2);
	void setUniform(const char* name, const float& value);
	void setUniform(const char* name, const glm::dvec4& value);
	void setUniform(const char* name, const glm::dvec3& value);
	void setUniform(const char* name, const glm::dvec2& value);
	void setUniform(const char* name, const glm::mat4& value);
	void setUniform(const char* name, const glm::mat3& value);
	void setUniform(const char* name, const glm::mat2& value);
	void setUniform(const char* name, const double& value);
	void setUniform(const char* name, const int & value);
	void setUniform(const char* name, const bool& value);

	//GLuint getProgram();

private:
	void CompileShaders();

	std::string vertex_code, fragment_code;
	GLuint shaderProgram;

};

