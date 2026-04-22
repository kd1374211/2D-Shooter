#pragma once
#include "CharaTexConst.h"

class C_CharaTexManager
{
public:

	void LoadData();

	void LoadTexPathData();
	void LoadCharaTexData();

	S_CharaTexData* GetTexData(E_CharaName a_name) { return(&m_texData[a_name]); }

private:

	C_CharaTexManager() {};
	~C_CharaTexManager() { ReleaseTex(); }

	void ReleaseTex();

	std::map<int, KdTexture*> m_texPathData;
	KdTexture m_tex[CHARATEXNUM];
	S_CharaTexData m_texData[E_CharaName::Max];

public:

	static C_CharaTexManager& GetInstance()
	{
		static C_CharaTexManager instance;
		return instance;
	}

};

#define CHARATEXMGR C_CharaTexManager::GetInstance()