#pragma once
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::vec3
#include <glm/gtc/matrix_transform.hpp>
#include "IDrawable.h"
#include "Model.h"
#include "Shader.h"

class Object
{
public:
	Object();
	virtual ~Object() = 0;
	Object* parent;

	glm::vec3 Position = glm::vec3(0, 0, 0);
	glm::vec3 Rotation = glm::vec3(0, 0, 0);
	glm::vec3 Scale = glm::vec3(1, 1, 1);

	glm::mat4 getModelMatrix();
	glm::mat4 getModelMatrix(glm::mat4);
};

