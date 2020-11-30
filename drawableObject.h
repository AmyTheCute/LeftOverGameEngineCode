#pragma once
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

class drawableObject
{
public:
	drawableObject();
	~drawableObject();
	void setVertices(GLfloat* vertices);
private:
	GLuint VBO = 0;
};

