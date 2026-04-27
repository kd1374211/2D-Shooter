#pragma once
#include "CharaTexConst.h"

class C_CharaTexManager
{
public:

	void LoadTexData();
	void LoadBaseTex();
	void SetBaseTexData();
	void LoadPlayerSelectWeaponTex();
	
	S_BaseCharaTexData* GetBaseTexData(E_CharaName a_name) { return(&m_texData[a_name]); }
	S_PlayerSelectTex* GetSelectTexData(E_WeaponName a_name) { return(&m_selectTexData[a_name]); }
	

private:

	C_CharaTexManager() {};
	~C_CharaTexManager() { ReleaseTex(); }

	void ReleaseTex();

	KdTexture m_tex[CHARABASETEXNUM];
	S_BaseCharaTexData m_texData[E_CharaName::Max];
	S_PlayerSelectTex m_selectTexData[E_WeaponName::WeaponMax];

public:

	static C_CharaTexManager& GetInstance()
	{
		static C_CharaTexManager instance;
		return instance;
	}

};

#define CHARATEXMGR C_CharaTexManager::GetInstance()