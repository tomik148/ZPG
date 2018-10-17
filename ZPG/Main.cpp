//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "App.h"



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



float speed = 0.1f;


int main(void)
{
	App* app = App::GetInstance();
	app->Init();
	app->MainLoop();

	/*
	

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
		shader->SetAsProgram();

		shader->AddMatrix(modelMatrix, "modelMatrix");
		shader->AddMatrix(viewMatrix, "viewMatrix");
		shader->AddMatrix(projectionMatrix, "projectionMatrix");


		/*
		glUniformMatrix4fv(shader->modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(shader->viewMatrixID, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(shader->projectionMatrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		


		obj->Bind();


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
	*/
}

