#include "RenderableObject.h"

int RenderableObject::NEXT_ID = 1;
std::map<int, RenderableObject*> RenderableObject::allObjects;

RenderableObject::RenderableObject(const float* points, int size, Shader* shader)
{
	this->shader = shader;
	this->points = points;
	this->size = size;
	id = NEXT_ID++;
	allObjects.insert(std::pair<int,RenderableObject*>(id,this));
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

RenderableObject::RenderableObject(Model* model, Shader* shader)
{
	this->shader = shader;
	this->model = model;
}

void RenderableObject::Bind()
{
	glBindVertexArray(VAO);
}
 
void RenderableObject::Draw()
{
	if (model == nullptr)
	{
		this->shader->SetAsProgram();
		Bind();
		glStencilFunc(GL_ALWAYS, id, 0xFF);
		glDrawArrays(GL_TRIANGLES, 0, size / 12); //FIXME //TODO
	}
	else
	{
		model->Draw(*shader);
	}

}

RenderableObject::~RenderableObject()
{
}

