#pragma once
#include "CharaManagerConst.h"

class C_EnemyBase;
class C_Player;

class C_CharaManager
{
public:

	//基本処理
	void Update();
	void Draw();

	//消去確認
	void CheckEnemyDelete();

	//まとめ処理
	void ClearChara();

	//プレイヤー
	void SpawnPlayer(E_WeaponName a_weapon);
	void SpawnBotPlayer(E_WeaponName a_weapon);
	void DeletePlayer();

	//敵
	void SpawnEnemy(Math::Vector2 a_pos, E_CharaName a_enemy);
	void ClearEnemy();

	//ゲッター
	//画像
	S_BaseCharaTexData GetBaseTexData(E_CharaName a_name) { return(m_texData[a_name]); }
	S_PlayerSelectWeaponData GetSelectWeaponData(E_WeaponName a_name)const { return(m_selectWeaponData[a_name]); }

	//ステータス
	S_CharaStatData GetStatData(E_CharaName a_name)const { return(m_statData[a_name]); }

	//プレイヤー
	C_Player* GetPlayer() { return(m_player); }

	//敵
	std::vector<C_EnemyBase*>& GetEnemy() { return(m_enemy); }

private:

	C_CharaManager() { Init(); };
	~C_CharaManager() { Release(); }

	//コンストラクタ（デストラクタ）で呼ぶ奴ら
	void Init();
	void LoadBaseTex();
	void SetBaseTexData();
	void LoadPlayerSelectWeaponTex();
	void LoadCharaStatData();
	void Release();

	//画像
	KdTexture m_tex[CHARABASETEXNUM];
	S_BaseCharaTexData m_texData[E_CharaName::Max];
	S_CharaStatData m_statData[E_CharaName::Max];
	S_PlayerSelectWeaponData m_selectWeaponData[E_WeaponName::WeaponMax];

	//プレイヤー
	const Math::Vector2 BOTPLAYERPOS = { -580.0f,180.0f };

	C_Player* m_player = nullptr;

	//敵コンテナ
	std::vector<C_EnemyBase*> m_enemy = {};

public:

	static C_CharaManager& GetInstance()
	{
		static C_CharaManager instance;
		return instance;
	}

};

#define CHARAMGR C_CharaManager::GetInstance()