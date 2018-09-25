#pragma once
class App
{
public:
	static App& GetInstance()
	{
		static App s;
		return s;
	}
private:
	App() {}
};

