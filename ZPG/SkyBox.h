#pragma once

#include "RenderableObject.h"

class SkyBox : public RenderableObject
{
public:
	unsigned int loadCubemap(std::vector<std::string> faces);
	SkyBox(Shader* shader);
	Shader* shader; 
	unsigned int cubemapTexture;
	unsigned int skyboxVAO, skyboxVBO;
	void Draw();

};

