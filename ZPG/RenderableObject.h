#pragma once
#include <GL/glew.h>
#include <stdlib.h>
#include <map>

#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::vec3
#include <glm/gtc/matrix_transform.hpp>
#include "IDrawable.h"
#include "Model.h"
#include "Object.h"
#include "Shader.h"

class RenderableObject : public Object , public IDrawable
{
public:
	RenderableObject(const float*, int, Shader* shader);
	RenderableObject(const Model* model, Shader* shader);

	void Bind();
	void Draw();

	~RenderableObject();
	GLuint VAO = 0;
	GLuint VBO = 0;
	int size;
private:
	static int NEXT_ID;
	int id;
	static std::map<int, RenderableObject*> allObjects;
	const float* points;

	Shader*  shader;
	const Model* model;

};