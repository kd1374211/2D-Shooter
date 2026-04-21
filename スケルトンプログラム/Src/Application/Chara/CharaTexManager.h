#pragma once

class C_CharaTexManager
{
public:

	void LoadTexPathData();
	void LoadTex();

	void ReleaseTex();

private:

	C_CharaTexManager() {};
	~C_CharaTexManager() {};

public:

	static C_CharaTexManager& GetInstance()
	{
		static C_CharaTexManager instance;
		return instance;
	}

};

#define CHARATEXMGR C_CharaTexManager::GetInstance()