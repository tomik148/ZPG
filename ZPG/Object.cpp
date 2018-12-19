#include "Object.h"

Object::Object()
{
}


Object::~Object()
{
}

glm::mat4 Object::getModelMatrix()
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::rotate(modelMatrix, Rotation.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, Rotation.y, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, Rotation.z, glm::vec3(0, 0, 1));
	modelMatrix = glm::translate(modelMatrix, Position);
	modelMatrix = glm::scale(modelMatrix, Scale);
	if (parent != nullptr)
	{
		parent->getModelMatrix(modelMatrix);
	}
	return modelMatrix;
}

glm::mat4 Object::getModelMatrix(glm::mat4 modelMatrix)
{
	modelMatrix = glm::rotate(modelMatrix, Rotation.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, Rotation.y, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, Rotation.z, glm::vec3(0, 0, 1));
	modelMatrix = glm::translate(modelMatrix, Position);
	modelMatrix = glm::scale(modelMatrix, Scale);
	if (parent != nullptr)
	{
		parent->getModelMatrix(modelMatrix);
	}
	return modelMatrix;
}