#include "Mesh.h"



Mesh::Mesh(float* vertices, unsigned int numvertices)
{
	m_drawCount = numvertices/8;

	glGenVertexArrays(1, &m_vertexArrayObject);
	glGenBuffers(NUM_BUFFERS, m_vertexBuffers);

	glBindVertexArray(m_vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffers[POSTION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numvertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
	glDeleteBuffers(NUM_BUFFERS, m_vertexBuffers);
}