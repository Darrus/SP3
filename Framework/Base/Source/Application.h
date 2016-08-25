
#ifndef APPLICATION_H
#define APPLICATION_H

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "timer.h"
#include "Keyboard.h"

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}

	void Init();
	void Run();
	void Exit();
	static bool IsMousePressed(unsigned short key);
	static bool GetMouseUpdate();
	static void GetMousePos(double& x, double& y);
	static int GetWindowWidth();
	static int GetWindowHeight();

	//Declare variables to store the last and current mouse position
	static double mouse_last_x, mouse_last_y, mouse_current_x, mouse_current_y, mouse_diff_x, mouse_diff_y;
	static double camera_yaw, camera_pitch;
	static double scrollX, scrollY;

	Controller* controller;
	static int m_window_width;
	static int m_window_height;
	int key;
private:
	Application();
	~Application();

	// Declare the window width and height as constant integer
	const static int m_window_deadzone = 1000;
	

	//Declare a window object
	StopWatch m_timer;
};

#endif