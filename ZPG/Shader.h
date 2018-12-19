#pragma once

#include <GL/glew.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::mat4
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

class Shader
{
public:
	Shader(std::string, std::string);

	void SetAsProgram();

	GLint Add(glm::mat4 matrix, const char * nameInShader);
	GLint Add(glm::vec3 vector, const char * nameInShader);
	GLint Add(float f, const char * nameInShader);
	GLint Add(int i, const char * nameInShader);

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

