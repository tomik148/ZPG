#pragma once
#include <GL/glew.h>
#include <stdlib.h>

class RenderObject
{
public:
	RenderObject(float*, int);

	void Bind();

	~RenderObject();
	GLuint VAO = 0;
	GLuint VBO = 0;
	int size;
private:
	float* points;
};