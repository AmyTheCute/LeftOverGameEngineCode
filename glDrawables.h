#pragma once
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

class glDrawables
{
public:
	glDrawables();
	~glDrawables();

private:
	GLuint VAO = 0;

};

