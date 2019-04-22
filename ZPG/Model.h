#pragma once

//ASSIMP
#include <assimp\scene.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <GL\glew.h>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <soil.h>

#include <string>
#include <vector>

#include "Mesh.h"



class Model
{
public: 

	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;

	Model(std::string const &path);
	void Draw(Shader shader);
private:


	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	void loadModel(std::string const &path);
	void processNode(aiNode* node, const aiScene* scene, std::string baseDir);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene, std::string baseDir);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, std::string baseDir);
};

