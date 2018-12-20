#include "App.h"

#include "sphere.h"


App::~App()
{
}
void App::MainLoop()
{
	Shader* shader = new Shader("../ZPG/vertex.vert", "../ZPG/fragment.frag");
	Shader* shader2 = new Shader("../ZPG/cubeUnLit.vert", "../ZPG/cubeUnLit.frag");
	Scene* scene = new Scene();

	RenderableObject* obj1 = new RenderableObject(sphere, sizeofSphere, shader);
	obj1->Position = glm::vec3(2,0,0);	
	scene->Add(obj1);

	RenderableObject* obj2 = new RenderableObject(sphere, sizeofSphere, shader);
	obj2->Position = glm::vec3(-2,0,0);	
	scene->Add(obj2);

	RenderableObject* obj3 = new RenderableObject(sphere, sizeofSphere, shader);
	obj3->Position = glm::vec3(0,0,2);	
	scene->Add(obj3);

	RenderableObject* obj4 = new RenderableObject(sphere, sizeofSphere, shader);
	obj4->Position = glm::vec3(0,0,-2);
	scene->Add(obj4);

	camera = new Camera(0, 10, 0, 0, -89);

	//Model* m = new  Model<glm::vec3, glm::vec3> (sphere, sizeofSphere);

	//glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	//const aiScene* s = aiImportFile(, aiProcessPreset_TargetRealtime_Fast );

	//aiMesh* mesh = NULL;
	//if (s->HasMeshes())
	//{
	//	for (size_t i = 0; i < s->mNumMeshes; i++)
	//	{
	//		mesh = s->mMeshes[i];
	//		mesh->HasPositions();
	//	}
	//}

	//GLuint textureID = SOIL_load_OGL_texture("../Models/test.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	//if (s->HasMaterials())
	//{
	//	for (size_t i = 0; i < s->mNumMaterials; i++)
	//	{
	//		aiMaterial* material = s->mMaterials[i];
	//		for (size_t j = 0; j < material->mNumProperties; j++)
	//		{
	//			aiString  a;
	//			aiTexture t;
	//			material->Get(AI_MATKEY_NAME,a);
	//			std::cout << a.C_Str() << std::endl;

	//		}
	//		


	//	}
	//}

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	auto obj = new RenderableObject(new Model("../Models/test.obj"), shader);
	scene->Add(obj);

	//glm::mat4 modelMatrix = glm::mat4(1);
	auto sky = new SkyBox(shader2);

	//glfwSetKeyCallback(window, movment);
	projectionMatrix = glm::perspective(glm::radians(45.0f), ratio, 0.01f, 1000.0f);

	while (!glfwWindowShouldClose(window))
	{

		//modelMatrix = glm::translate(modelMatrix, -glm::vec3(0.5f, -0.5f, 0.0f));
		//modelMatrix = glm::rotate(modelMatrix, 0.1f, glm::vec3(0.0f, 0.0f, 1.0f));
		//modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f, -0.5f, 0.0f));

		viewMatrix = camera->GetViewMatrix();//glm::lookAt(cameraPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		

		//modelMatrix = glm::rotate(modelMatrix, 0.01f, glm::vec3(0.0f, 0.0f, 1.0f));

		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		//shader->SetAsProgram();

		
		shader->Add(viewMatrix, "viewMatrix");
		shader->Add(projectionMatrix, "projectionMatrix");		
		shader->Add(camera->Position, "cameraPosition");

		//shader2->Add(glm::translate(modelMatrix, camera->Position), "Model");
		shader2->Add(viewMatrix, "viewMatrix");
		shader2->Add(projectionMatrix, "projectionMatrix");
		
		
		
		//sky->Draw();
		scene->Update(1);

		/*
		glUniformMatrix4fv(shader->modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(shader->viewMatrixID, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(shader->projectionMatrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		*/

		//shader->Add(obj1->getModelMatrix(), "modelMatrix");
		//obj1->Draw();
		//shader->Add(obj2->getModelMatrix(), "modelMatrix");
		//obj2->Draw();
		//shader->Add(obj3->getModelMatrix(), "modelMatrix");
		//obj3->Draw();
		//shader->Add(obj4->getModelMatrix(), "modelMatrix");
		//obj4->Draw();

		// draw triangles
		//glDrawArrays(GL_TRIANGLES, 0, 2880); //mode,first,count
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

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void { App::GetInstance()->camera->movment(window, key, scancode, action, mods); });
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos) -> void { App::GetInstance()->camera->look(window, mouseXPos, mouseYPos); });
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) -> void { App::GetInstance()->camera->mouse_button_callback(window, button, action, mods); });
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

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}
