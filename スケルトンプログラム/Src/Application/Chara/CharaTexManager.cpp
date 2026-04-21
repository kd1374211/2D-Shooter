#include "CharaTexManager.h"

void C_CharaTexManager::LoadTexPathData()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Data/CharaTexPathData.csv", "r") == 0)
	{
		char dummy[100] = {};

		for (int i = 0; i < CHARATEXNUM; i++)
		{
			if (fgets(dummy, 100, fp) != nullptr)//1行読み
			{
				const int PATHLENG = 70;
				char path[PATHLENG] = {};
				int yomi;

				fscanf_s(fp, "%d,%s", &yomi, path, PATHLENG);
				m_tex[i].Load(path);

				m_texData.emplace(yomi, &m_tex[i]);
			}
		}

		fclose(fp);
	}
}

void C_CharaTexManager::ReleaseTex()
{
	for (int i = 0; i < CHARATEXNUM; i++)
	{
		m_tex[i].Release();
	}
}
