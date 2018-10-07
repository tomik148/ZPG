#pragma once

#include <GL/glew.h>
#include <stdio.h>


class Shader
{
public:
	Shader();
	GLuint shaderProgram;
	GLint modelMatrixID;
	GLuint vertexShader;
	GLuint fragmentShader;

	~Shader();
private:
	const char* vertex_shader;
	const char* fragment_shader;
};

