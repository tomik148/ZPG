//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "App.h"
#include "Shader.h"
#include "RenderObject.h"


float points[] = {
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f
};

glm::mat4 modelMatrix = glm::mat4(1.0f);
glm::mat4 viewMatrix = glm::mat4(1.0f);
glm::mat4 projectionMatrix = glm::mat4(1.0f);

glm::vec3 cameraPosition = glm::vec3(10.0f, 10.0f, 10.0f);

float speed = 0.1f;

static void movment(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (GLFW_KEY_W == key)
	{
		glm::vec3 deltaPos = -cameraPosition;
		deltaPos /= deltaPos.length();
		deltaPos *= speed;
		cameraPosition += deltaPos;
	}
	if (GLFW_KEY_S == key)
	{
		glm::vec3 deltaPos = cameraPosition;
		deltaPos /= deltaPos.length();
		deltaPos *= speed;
		cameraPosition += deltaPos;
	}
	if (GLFW_KEY_A == key)
	{
		glm::vec3 deltaPos = cameraPosition;
		deltaPos = glm::cross(deltaPos, glm::vec3(0, 1, 0));

		deltaPos /= deltaPos.length();
		deltaPos *= speed;
		cameraPosition += deltaPos;
	}
	if (GLFW_KEY_D == key)
	{
		glm::vec3 deltaPos = cameraPosition;
		deltaPos = glm::cross(glm::vec3(0, 1, 0), deltaPos);

		deltaPos /= deltaPos.length();
		deltaPos *= speed;
		cameraPosition += deltaPos;
	}
}

int main(void)
{
	App* app = App::GetInstance();

	Shader* shader = new Shader();
	
	RenderObject* obj = new RenderObject(points, sizeof(points));

	glfwSetKeyCallback(app->window, movment);

	while (!glfwWindowShouldClose(app->window))
	{
		
		//modelMatrix = glm::translate(modelMatrix, -glm::vec3(0.5f, -0.5f, 0.0f));
		//modelMatrix = glm::rotate(modelMatrix, 0.1f, glm::vec3(0.0f, 0.0f, 1.0f));
		//modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f, -0.5f, 0.0f));

		viewMatrix = glm::lookAt(cameraPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		projectionMatrix = glm::perspective(glm::radians(45.0f), app->ratio, 0.01f, 1000.0f);

		//modelMatrix = glm::rotate(modelMatrix, 0.01f, glm::vec3(0.0f, 0.0f, 1.0f));

		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader->shaderProgram);

		glUniformMatrix4fv(shader->modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(shader->viewMatrixID, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(shader->projectionMatrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		
		glBindVertexArray(obj->VAO);


		// draw triangles
		glDrawArrays(GL_TRIANGLES, 0, obj->size); //mode,first,count
										  // update other events like input handling
		glfwPollEvents();

		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(app->window);
	}
	glfwDestroyWindow(app->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

