#pragma once

#include <GL/glew.h>
#include <stdio.h>


class Shader
{
public:
	Shader();
	GLuint shaderProgram;

	GLuint vertexShader;
	GLuint fragmentShader;

	GLint modelMatrixID;
	GLint viewMatrixID;
	GLint projectionMatrixID;

	~Shader();
private:
	const char* vertex_shader;
	const char* fragment_shader;
};

