#pragma once

//ASSIMP
#include <assimp\scene.h>


class Model
{
public: 
	Model(const float*, int);
	Model(aiMesh*);
	aiMesh* model;
private:
	const float* points;
	int size;
};

