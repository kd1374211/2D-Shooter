#pragma once
#include "CharaTexConst.h"

class C_CharaManager
{
public:

	S_BaseCharaTexData* GetBaseTexData(E_CharaName a_name) { return(&m_texData[a_name]); }
	S_PlayerSelectTex* GetSelectTexData(E_WeaponName a_name) { return(&m_selectTexData[a_name]); }

private:

	C_CharaManager() { Init(); };
	~C_CharaManager() { Release(); }

	void Init();
	void LoadBaseTex();
	void SetBaseTexData();
	void LoadPlayerSelectWeaponTex();
	void Release();

	//テクスチャ
	KdTexture m_tex[CHARABASETEXNUM];
	S_BaseCharaTexData m_texData[E_CharaName::Max];
	S_PlayerSelectTex m_selectTexData[E_WeaponName::WeaponMax];

public:

	static C_CharaManager& GetInstance()
	{
		static C_CharaManager instance;
		return instance;
	}

};

#define CHARAMGR C_CharaManager::GetInstance()