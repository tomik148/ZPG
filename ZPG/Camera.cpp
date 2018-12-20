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
	GLbyte color[4];
	GLfloat depth;
	GLuint index;

	double newy = 600 - mouseY;

	glReadPixels(mouseX, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(mouseX, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glReadPixels(mouseX, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	//printf("Clicked on pixel %d, %d, color % 02hhx % 02hhx % 02hhx % 02hhx, depth %f, stencil index %u\n", mouseX, mouseY, color[0], color[1], color[2], color[3], depth, index);

	std::cout << "Clicked on pixel " << mouseX << ", " << newy <<  std::endl;
	std::cout << "Color " << color[0] << ", " << color[1] << ", " << color[2] << ", " << std::endl;
	std::cout << "Depth " << depth <<  std::endl;
	std::cout << "Stencil index " << index <<  std::endl;

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
