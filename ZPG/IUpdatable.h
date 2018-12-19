#pragma once
class IUpdatable
{
public:
	virtual void preUpdate(int deltaTime) = 0;
	virtual void Update(int deltaTime) = 0;
	virtual void postUpdate(int deltaTime) = 0;
};
