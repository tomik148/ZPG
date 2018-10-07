#pragma once
#include <stdlib.h>
#include <stdio.h>

//Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  

class App
{
public:
	static App* GetInstance()
	{
		static App Instance;
		return &Instance;
	}
	~App();

	GLFWwindow* window;
	void Init();

	volatile double cursorePositionX = 0;
	volatile double cursorePositionY = 0;

	static void error_callback(int error, const char* description) { fputs(description, stderr); }
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
	}

	static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

	static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

	static void window_size_callback(GLFWwindow* window, int width, int height) {
		printf("resize %d, %d \n", width, height);
		glViewport(0, 0, width, height);
	}

	static void cursor_callback(GLFWwindow *window, double x, double y) { App* a = App::GetInstance();  a->cursorePositionX = x; a->cursorePositionY = y; /*printf("cursor_callback \n");*/ }

	static void button_callback(GLFWwindow* window, int button, int action, int mode) {
		if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
	}

private:
	int width, height;
	float ratio;
	App() { Init(); }
};

