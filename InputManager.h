#pragma once
class GameWindow;

class InputManager
{
public:
	//void static onResize(int w, int h);
	void static onMouseEvent(double xpos, double ypos);
	void static registerWindow(GameWindow *window) { gameWindow = window; }

private:
	static GameWindow *gameWindow;
};

