#include "InputManager.h"
#include "GameWindow.h"

GameWindow *InputManager::gameWindow;


void InputManager::onMouseEvent(double xpos, double ypos)
{
	gameWindow->onMouseEvent(xpos, ypos);
}