#pragma once
#include "SceneConst.h"
#include "../Chara/CharaTexConst.h"

class C_SceneManager
{
public:

	void Update();
	void Draw();

	//セッター
	void SetScene(C_SceneBase* a_pBase);//シーン切り替え
	void SetSceneQueue(E_SceneTypeTag a_tag) { m_sceneQueue = a_tag; }//次のフレームに切り替えする予約
	
	void SetSelectedWeapon(E_WeaponName a_weapon) { m_selectedWeapon = a_weapon; }//選択武器種管理

	//ゲッター
	E_WeaponName GetSelectedWeapon()const { return(m_selectedWeapon); }

private:

	//選択武器種
	E_WeaponName m_selectedWeapon;

	//現在シーンポインター
	C_SceneBase* m_pCurrentScene;

	//予約シーン種
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