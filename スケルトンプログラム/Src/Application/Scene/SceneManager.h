#pragma once
#include "SceneConst.h"
#include "../Chara/CharaTexConst.h"

class C_SceneManager
{
public:

	void Update();
	void Draw();

	void SetScene(C_SceneBase* a_pBase);
	void SetSceneQueue(E_SceneTypeTag a_tag) { m_sceneQueue = a_tag; };

	void SetSelectedWeapon(E_WeaponName a_weapon) { m_selectedWeapon = a_weapon; }
	E_WeaponName GetSelectedWeapon() { return(m_selectedWeapon); }

private:

	E_WeaponName m_selectedWeapon;

	C_SceneBase* m_pCurrentScene;
	E_SceneTypeTag m_sceneQueue;

	C_SceneManager() :m_pCurrentScene(nullptr), m_sceneQueue(E_SceneTypeTag::None), m_selectedWeapon(E_WeaponName::AutoCannon) {};
	~C_SceneManager();

public:

	static C_SceneManager& GetInstance()
	{
		static C_SceneManager instance;
		return instance;
	}

};

#define SCENEMGR C_SceneManager::GetInstance()