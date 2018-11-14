#pragma once
class Model
{
public: 
	template<typename... Ts>
	Model(const float*, int);
private:
	const float* points;
	int size;
};

