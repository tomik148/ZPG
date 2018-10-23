#pragma once

#include <stdio.h>

//Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float alfa = 90, float beta = 0, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
	Camera(float x, float y, float z, float alfa = 90, float beta = 0, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

	float alfa;
	float beta;

	float speed = 0.1f;

	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;

	glm::mat4 GetViewMatrix();

	void RecalculateFrontRightUp();



	void movment(GLFWwindow* window, int key, int scancode, int action, int mods);

	bool isDraging = false;
	bool first = true;
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	float lastMouseX, lastMouseY;
	void look(GLFWwindow* window, double mouseX, double mouseY);
	~Camera();
};

