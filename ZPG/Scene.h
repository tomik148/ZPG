#pragma once

#include <vector>
#include <type_traits>
	
#include "Object.h"
#include "IUpdatable.h"
#include "IDrawable.h"

class Scene
{
public:
	void Add(Object* obj);
	void Update(int deltaTime);
	Scene();
	~Scene();
private:
	

	std::vector<Object*> objects;
	std::vector<IUpdatable*> updatables;
	std::vector<IDrawable*> drawables;
};

