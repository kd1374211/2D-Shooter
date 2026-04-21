#include "CharaTexManager.h"

void C_CharaTexManager::LoadTexPathData()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Data/CharaTexPathData.csv", "r") == 0)
	{


		fclose(fp);
	}
}

void C_CharaTexManager::LoadTex()
{
}

void C_CharaTexManager::ReleaseTex()
{
}
