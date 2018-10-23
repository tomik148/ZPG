#pragma once
#include <GL/glew.h>
#include <stdlib.h>

#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::vec3
#include <glm/gtc/matrix_transform.hpp>

class RenderObject
{
public:
	RenderObject(const float*, int);

	void Bind();
	void Render();

	glm::vec3 Position = glm::vec3(0, 0, 0);
	glm::vec3 Rotation = glm::vec3(0, 0, 0);
	glm::vec3 Scale = glm::vec3(1,1,1);
	
	glm::mat4 getModelMatrix();

	~RenderObject();
	GLuint VAO = 0;
	GLuint VBO = 0;
	int size;
private:
	const float* points;
};