#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "Shader.h"
#include "Object.h"
#include "Camera.h"
#include "Model.h"

#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::vec3
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

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

	void MainLoop();


	GLFWwindow* window;
	void Init();

	glm::vec3 cameraPosition = glm::vec3(10.0f, 10.0f, 10.0f);

	Camera* camera;

	void error_callback(int error, const char* description);
	void window_size_callback(GLFWwindow* window, int width, int height);
	void window_focus_callback(GLFWwindow* window, int focused);
	void window_iconify_callback(GLFWwindow* window, int iconified);

private:
	int width, height;
	float ratio;
	App() { }
};

