#include "drawableObject.h"



drawableObject::drawableObject()
{
	glGenBuffers(1, &VBO);
}


drawableObject::~drawableObject()
{
}

void drawableObject::setVertices(GLfloat* vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices, GL_STATIC_DRAW);


}
