#pragma once
#include "CharaTexConst.h"

class C_CharaTexManager
{
public:

	void LoadTexData();
	void LoadBaseTex();
	void LoadPlayerWeaponTex();
	void LoadPlayerEngineTex();

	S_BaseCharaTexData* GetBaseTexData(E_CharaName a_name) { return(&m_texData[a_name]); }
	S_WeaponTex* GetWeaponTexData(E_WeaponName a_name) { return(&m_weaponTexData[a_name]); }
	S_EngineTex* GetEngineTexData(E_WeaponName a_name) { return(&m_engineTexData[a_name]); }

private:

	C_CharaTexManager() {};
	~C_CharaTexManager() { ReleaseTex(); }

	void ReleaseTex();

	S_BaseCharaTexData m_texData[E_CharaName::Max];
	S_WeaponTex m_weaponTexData[E_WeaponName::WeaponMax];
	S_EngineTex m_engineTexData[E_WeaponName::WeaponMax];

public:

	static C_CharaTexManager& GetInstance()
	{
		static C_CharaTexManager instance;
		return instance;
	}

};

#define CHARATEXMGR C_CharaTexManager::GetInstance()