#include "App.h"


App::~App()
{
}

void App::MainLoop()
{
	float points[] = {
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f
	};

	Shader* shader = new Shader();
	RenderObject* obj = new RenderObject(points, sizeof(points));

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	

	//glfwSetKeyCallback(window, movment);

	while (!glfwWindowShouldClose(window))
	{

		//modelMatrix = glm::translate(modelMatrix, -glm::vec3(0.5f, -0.5f, 0.0f));
		//modelMatrix = glm::rotate(modelMatrix, 0.1f, glm::vec3(0.0f, 0.0f, 1.0f));
		//modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f, -0.5f, 0.0f));

		viewMatrix = glm::lookAt(cameraPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		projectionMatrix = glm::perspective(glm::radians(45.0f), ratio, 0.01f, 1000.0f);

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
		*/


		obj->Bind();


		// draw triangles
		glDrawArrays(GL_TRIANGLES, 0, obj->size); //mode,first,count
										  // update other events like input handling
		glfwPollEvents();

		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void App::error_callback(int error, const char* description) { fputs(description, stderr); }


void App::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void App::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void App::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void App::movment(GLFWwindow* window, int key, int scancode, int action, int mods)
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




void App::cursor_callback(GLFWwindow *window, double x, double y) { App* a = App::GetInstance();  a->cursorePositionX = x; a->cursorePositionY = y; printf("cursor_callback %f , %f \n", x, y); }

void App::mouse_button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

void App::Init()
{
	glfwSetErrorCallback([](int error, const char* description) -> void { App::GetInstance()->error_callback(error, description); });

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}
	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void { App::GetInstance()->movment(window, key, scancode, action, mods); });
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos) -> void { App::GetInstance()->cursor_callback(window, mouseXPos, mouseYPos); });
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) -> void { App::GetInstance()->mouse_button_callback(window, button, action, mods); });
	glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused) -> void { App::GetInstance()->window_focus_callback(window, focused); });
	glfwSetWindowIconifyCallback(window, [](GLFWwindow* window, int iconified) -> void { App::GetInstance()->window_iconify_callback(window, iconified); });
	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) -> void { App::GetInstance()->window_size_callback(window, width, height); });


	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();
	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);

	if (!glfwInit())
		exit(EXIT_FAILURE);


}
