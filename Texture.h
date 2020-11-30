#pragma once

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <iostream>

#include "stb_image.h"

class Texture
{
public:
	Texture(const char* location, const unsigned int & num);
	Texture();
	~Texture();
	void bind();
private:
	unsigned int texture, textureNum;
};

