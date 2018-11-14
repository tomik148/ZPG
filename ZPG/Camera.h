#pragma once

#include <stdio.h>
#include <vector>
#include <functional>
#include <iostream>

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

	inline void AddListenerToOnViewMatrixChanged(std::function<void(glm::mat4)> listener)
	{
		OnViewMatrixChanged.push_back(listener);
	}

	inline void RemoveListenerFromOnViewMatrixChanged(std::function<void(glm::mat4)> listener)
	{
		for (size_t i = 0; i < OnViewMatrixChanged.size(); i++)
		{
			if (&OnViewMatrixChanged.at(i) == &listener)
			{
				OnViewMatrixChanged.erase(OnViewMatrixChanged.begin() + i);
			}
		}
	}

	void movment(GLFWwindow* window, int key, int scancode, int action, int mods);

	bool isDraging = false;
	bool first = true;
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	float lastMouseX, lastMouseY;
	void look(GLFWwindow* window, double mouseX, double mouseY);
	~Camera();
private:

	inline void InvokeOnViewMatrixChanged(glm::mat4 viewMatrix)
	{
		for (size_t i = 0; i < OnViewMatrixChanged.size(); i++)
		{
			if (OnViewMatrixChanged.at(i))
			{
				OnViewMatrixChanged.at(i)(viewMatrix);
			}

		}
	}
	std::vector<std::function<void(glm::mat4)>> OnViewMatrixChanged;

};

