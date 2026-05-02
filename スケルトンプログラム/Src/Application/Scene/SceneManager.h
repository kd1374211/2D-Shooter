#pragma once
#include "SceneConst.h"
#include "SceneManagerConst.h"
#include "../Chara/CharaManagerConst.h"

class C_SceneManager
{
public:

	void Update();
	void Draw();

	//セッター
	void SetScene(E_SceneTypeTag a_tag);//シーン切り替え
	void SetSceneQueue(E_SceneTypeTag a_tag) { m_sceneQueue = a_tag; }//次のフレームに切り替えする予約
	
	void SetSelectedWeapon(E_WeaponName a_weapon) { m_selectedWeapon = a_weapon; }//選択武器種管理

	//ゲッター
	E_WeaponName GetSelectedWeapon()const { return(m_selectedWeapon); }
	S_SelectWeaponStat GetSelectedWeaponStat(E_WeaponName a_weapon)const { return(m_weaponStatData[a_weapon]); }
	S_SceneTexData* GetSceneTexData(E_GameTextures a_tex) { return(&m_sceneTex[(int)a_tex]); }

private:

	//選択武器種
	E_WeaponName m_selectedWeapon;
	S_SelectWeaponStat m_weaponStatData[E_WeaponName::WeaponMax];

	//現在シーンポインター
	C_SceneBase* m_pCurrentScene;

	//予約シーン種
	E_SceneTypeTag m_sceneQueue;

	C_SceneManager() :m_pCurrentScene(nullptr), m_sceneQueue(E_SceneTypeTag::None), m_selectedWeapon(E_WeaponName::AutoCannon) { Init(); }
	~C_SceneManager();

	//画像管理
	S_SceneTexData m_sceneTex[(int)E_GameTextures::Max];

	void Init();
	void LoadData();
	void LoadTex();
	void Release();

public:

	static C_SceneManager& GetInstance()
	{
		static C_SceneManager instance;
		return instance;
	}

};

#define SCENEMGR C_SceneManager::GetInstance()