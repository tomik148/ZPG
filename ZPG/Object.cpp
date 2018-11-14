#include "Object.h"

int Object::NEXT_ID = 1;
std::map<int, Object*> Object::allObjects;

Object::Object(const float* points, int size)
{
	this->points = points;
	this->size = size;
	id = NEXT_ID++;
	allObjects.insert(std::pair<int,Object*>(id,this));
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

	//vertex attribute object(VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes -- position 0
	glEnableVertexAttribArray(1); //enable vertex attributes -- normal   1
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
}

void Object::Bind()
{
	glBindVertexArray(VAO);
}

void Object::Draw()
{
	Bind();
	glStencilFunc(GL_ALWAYS, id, 0xFF);
	glDrawArrays(GL_TRIANGLES, 0, size / 12); //FIXME //TODO
}

glm::mat4 Object::getModelMatrix()
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::rotate(modelMatrix, Rotation.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, Rotation.y, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, Rotation.z, glm::vec3(0, 0, 1));
	modelMatrix = glm::translate(modelMatrix, Position);
	modelMatrix = glm::scale(modelMatrix,Scale);
	return modelMatrix;
}

Object::~Object()
{
}