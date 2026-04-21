#pragma once

class C_CharaTexManager
{
public:

	void LoadTexPathData();

private:

	C_CharaTexManager() {};
	~C_CharaTexManager() { ReleaseTex(); }

	void ReleaseTex();

	static const int CHARATEXNUM = 5;

	std::map<int, KdTexture*> m_texData;
	KdTexture m_tex[CHARATEXNUM];

public:

	static C_CharaTexManager& GetInstance()
	{
		static C_CharaTexManager instance;
		return instance;
	}

};

#define CHARATEXMGR C_CharaTexManager::GetInstance()