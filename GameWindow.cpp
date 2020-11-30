#include "GameWindow.h"
#include "InputManager.h"


GameWindow::GameWindow(const unsigned int & WIDTH, const unsigned int & HEIGHT)
{
	SCR_WIDTH = WIDTH;
	SCR_HEIGHT = HEIGHT;

	InputManager::registerWindow(this);

	// glfw: initialize and configure
	// ------------------------------
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Proj", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, GameWindow::framebuffer_size_callback);
	glfwSetCursorPosCallback(window, GameWindow::mouse_callback);
	//glfwSetScrollCallback(window, GameWindow::scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Glew: load all OpenGL function pointers
	// ---------------------------------------
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	// -----------------
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
}

void GameWindow::setCamera(Camera *cameraIn)
{
	this->camera = cameraIn;
}

void GameWindow::pollEvents()
{
	glfwSwapBuffers(window);
	glfwPollEvents();

	processInput(window);
}

void GameWindow::update()
{
	// per-frame time logic
	// --------------------
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	if (deltaTime < 6.94)
		Sleep(6.94 - deltaTime);
	lastFrame = currentFrame;
}

bool GameWindow::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void GameWindow::updateFrameSize(int w, int h)
{
	std::cout << "HELLO THERE CUTIE" << std::endl;
}

void GameWindow::onMouseEvent(int xpos, int ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera->ProcessMouseMovement(xoffset, yoffset);
}

// whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void GameWindow::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	//InputManager::onResize(width, height);
}

void GameWindow::mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	InputManager::onMouseEvent(xpos, ypos);
}

//void GameWindow::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
//{
//}

void GameWindow::processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera->ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		camera->ProcessKeyboard(DOWN, deltaTime);
}


GameWindow::~GameWindow()
{
}

