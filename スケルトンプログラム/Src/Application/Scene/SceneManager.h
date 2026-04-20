#pragma once
#include "SceneConst.h"

class C_SceneManager
{
public:

	void Update();
	void Draw();

	void SetScene(C_SceneBase* a_pBase);

private:

	C_SceneBase* m_pCurrentScene;

	C_SceneManager() :m_pCurrentScene(nullptr) {};
	~C_SceneManager();

public:

	static C_SceneManager& GetInstance()
	{
		static C_SceneManager instance;
		return instance;
	}

};

#define SCENEMGR C_SceneManager::GetInstance()