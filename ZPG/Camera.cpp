#include "Camera.h"


Camera::Camera(glm::vec3 position, float alfa, float beta, glm::vec3 up) : Position(position), alfa(alfa), beta(beta), Up(up)
{
	RecalculateFrontRightUp();
}
Camera::Camera(float x, float y, float z, float alfa, float beta, glm::vec3 up) : Camera::Camera(glm::vec3(x, y, z), alfa, beta, up) {};


glm::mat4 Camera::GetViewMatrix()
{
	RecalculateFrontRightUp();
	return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}

void Camera::RecalculateFrontRightUp()
{
	glm::vec3 front;
	front.x = cos(glm::radians(this->alfa)) * cos(glm::radians(this->beta));
	front.y = sin(glm::radians(this->beta));
	front.z = sin(glm::radians(this->alfa)) * cos(glm::radians(this->beta));
	this->Front = glm::normalize(front);
	this->Right = glm::normalize(glm::cross(this->Front, glm::vec3(0, 1, 0)));
	this->Up = glm::normalize(glm::cross(this->Right, this->Front));
}

void Camera::movment(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (GLFW_KEY_W == key)
	{
		glm::vec3 deltaPos = Front;
		deltaPos *= speed;
		Position += deltaPos;
	}
	if (GLFW_KEY_S == key)
	{
		glm::vec3 deltaPos = -Front;
		deltaPos *= speed;
		Position += deltaPos;
	}
	if (GLFW_KEY_A == key)
	{
		glm::vec3 deltaPos = -Right;
		deltaPos *= speed;
		Position += deltaPos;
	}
	if (GLFW_KEY_D == key)
	{
		glm::vec3 deltaPos = Right;
		deltaPos *= speed;
		Position += deltaPos;

	}
}

void Camera::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	printf("mouse_button_callback %d-%d \n " , button, action);
	if (button == 0 && action == 1)
	{
		isDraging = true;
	}
	if (button == 0 && action == 0)
	{
		isDraging = false;
		first = true;
	}

}

void Camera::look(GLFWwindow * window, double mouseX, double mouseY)
{
	if (isDraging)
	{
		if (first)
		{
			this->lastMouseX = mouseX;
			this->lastMouseY = mouseY;
			first = false;
		}
		float dx = this->lastMouseX - mouseX;
		float dy = this->lastMouseY - mouseY;

		this->alfa -= dx;
		this->beta += dy;

		if (this->beta > 89.0f)
			this->beta = 89.0f;
		if (this->beta < -89.0f)
			this->beta = -89.0f;

		RecalculateFrontRightUp();

		this->lastMouseX = mouseX;
		this->lastMouseY = mouseY;
	}
}

Camera::~Camera()
{
}
