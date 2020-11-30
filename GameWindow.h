#pragma once

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

#include <Windows.h>

#include <iostream>
class InputManager;
class GameWindow {
public:
	GameWindow(const unsigned int & WIDTH, const unsigned int & HEIGHT);
	void processInput(GLFWwindow *window);

	void setCamera(Camera *cameraIn);
	void pollEvents();
	void update();
	bool shouldClose();
	friend InputManager;
	~GameWindow();
protected:
private:
	void updateFrameSize(int w, int h);
	void onMouseEvent(int xpos, int ypos);
	void static framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void static mouse_callback(GLFWwindow* window, double xpos, double ypos);
	//void static scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	// settings
	unsigned int SCR_WIDTH = 1920;
	unsigned int SCR_HEIGHT = 1080;

	// camera
	Camera *camera;
	GLFWwindow* window;

	float currentFrame;
	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;

	// timing
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
};

