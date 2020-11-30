#pragma once

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <glm/glm.hpp>
#include <iostream>



class Mesh
{
public:
	Mesh(float* vertices, unsigned int numvertices);

	void Draw();

	~Mesh();
protected:
private:
	Mesh(const Mesh& other);
	void operator=(const Mesh& other);

	enum
	{
		POSTION_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

