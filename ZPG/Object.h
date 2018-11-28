#pragma once
#include <GL/glew.h>
#include <stdlib.h>
#include <map>

#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::vec3
#include <glm/gtc/matrix_transform.hpp>
#include "IDrawable.h"
#include "Model.h"
#include "Shader.h"

class Object : IDrawable
{
public:
	Object(const float*, int);
	Object(const Model* model, const Shader* shader);

	void Bind();
	void Draw();

	glm::vec3 Position = glm::vec3(0, 0, 0);
	glm::vec3 Rotation = glm::vec3(0, 0, 0);
	glm::vec3 Scale = glm::vec3(1,1,1);
	
	glm::mat4 getModelMatrix();

	~Object();
	GLuint VAO = 0;
	GLuint VBO = 0;
	int size;
private:
	static int NEXT_ID;
	int id;
	static std::map<int, Object*> allObjects;
	const float* points;

	const Shader*  shader;
	const Model* model;

};