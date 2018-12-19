#include "Scene.h"



void Scene::Add(Object* obj)
{
	objects.push_back(obj);
	auto u = dynamic_cast<IUpdatable*>(obj);
	if (u != nullptr)
	{
		updatables.push_back(u);
	}
	auto d = dynamic_cast<IDrawable*>(obj);
	if (d != nullptr)
	{
		drawables.push_back(d);
	}
}

void Scene::Update(int deltaTime)
{
	//Update
	for (size_t i = 0; i < updatables.size(); i++)
	{
		updatables.at(i)->preUpdate(deltaTime);
	}
	for (size_t i = 0; i < updatables.size(); i++)
	{
		updatables.at(i)->Update(deltaTime);
	}
	for (size_t i = 0; i < updatables.size(); i++)
	{
		updatables.at(i)->postUpdate(deltaTime);
	}
	//Render

	for (size_t i = 0; i < drawables.size(); i++)
	{
		drawables.at(i)->Draw();
	}
}

Scene::Scene()
{
	
}


Scene::~Scene()
{
}
