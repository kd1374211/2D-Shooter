#pragma once
#include "SceneConst.h"
#include "SceneManagerConst.h"
#include "../Chara/CharaManagerConst.h"

class C_SceneManager
{
public:

	void Update();
	void Draw();

	//シーン遷移
	void SpawnTransition(E_SceneTypeTag a_nextScene);

	//セッター
	void SetScene(E_SceneTypeTag a_tag);//シーン切り替え
	void SetSceneQueue(E_SceneTypeTag a_tag) { m_sceneQueue = a_tag; }//次のフレームに切り替えする予約
	
	void SetSelectedWeapon(E_WeaponName a_weapon) { m_selectedWeapon = a_weapon; }//選択武器種管理

	//ゲッター
	bool GetIsStop()const { return(m_isStop); }
	E_WeaponName GetSelectedWeapon()const { return(m_selectedWeapon); }
	S_SelectWeaponStat GetSelectedWeaponStat(E_WeaponName a_weapon)const { return(m_weaponStatData[a_weapon]); }
	S_SceneTexData* GetSceneTexData(E_GameTextures a_tex) { return(&m_sceneTex[(int)a_tex]); }
	std::vector<S_TextsData> GetSceneTextsData(E_SceneTypeTag a_scene) { return(m_sceneTexts[(int)a_scene]); }
	KdTexture* GetButtonTex(E_ButtonState a_state) { return(&m_buttonTex[(int)a_state]); }
	S_ButtonPosData* GetButtonData(E_GameButtons a_button) { return(&m_sceneButtons[(int)a_button]); }

private:

	//選択武器種
	E_WeaponName m_selectedWeapon;
	S_SelectWeaponStat m_weaponStatData[E_WeaponName::WeaponMax];

	//現在シーンポインター
	C_SceneBase* m_pCurrentScene;

	//予約シーン種
	E_SceneTypeTag m_sceneQueue;

	//遷移演出
	C_Transition* m_pTransition;

	C_SceneManager() :m_pCurrentScene(nullptr), m_pTransition(nullptr), m_sceneQueue(E_SceneTypeTag::None), m_selectedWeapon(E_WeaponName::AutoCannon), m_isStop(false) { Init(); }
	~C_SceneManager();

	//画像管理
	S_SceneTexData m_sceneTex[(int)E_GameTextures::Max];

	//ボタン
	S_ButtonPosData m_sceneButtons[(int)E_GameButtons::Max];
	KdTexture m_buttonTex[(int)E_ButtonState::Max];

	//フォント管理用
	std::vector<S_TextsData> m_sceneTexts[(int)E_SceneTypeTag::Max];

	//操作可能フラグ
	bool m_isStop;

	void Init();
	void LoadSelectWeaponData();
	void LoadTextsData();
	void LoadButtonData();
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