#pragma once

//ASSIMP
#include <assimp\scene.h>
#include <glm\vec3.hpp>
#include <glm\vec2.hpp>
#include <GL/glew.h>
#include <vector>
#include <string>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
};

class Model
{
public: 
	Model(const float*, int);
	Model(aiMesh*);
	void setupMesh();
	aiMesh* model;
private:
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
};

