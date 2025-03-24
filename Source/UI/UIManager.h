#pragma once

#include "Singleton.h"

class UIManager : public Singleton<UIManager>
{

public:
	UIManager();
	virtual ~UIManager();

public:
	void Init(GLFWwindow* _window);
	void StartLoop();
	void EndLoop();
	void Destroy();
};