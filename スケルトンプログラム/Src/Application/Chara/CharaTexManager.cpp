#include "CharaTexManager.h"

void C_CharaTexManager::LoadData()
{
	LoadTexPathData();
	LoadCharaTexData();
}

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
				char path[STRLENG] = {};
				int yomi;

				fscanf_s(fp, "%d,%s", &yomi, path, STRLENG);
				m_tex[i].Load(path);

				m_texPathData.emplace(yomi, &m_tex[i]);
			}
		}

		fclose(fp);
	}
}

void C_CharaTexManager::LoadCharaTexData()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Data/CharaTexData.csv", "r") == 0)
	{
		char dummy[250] = {};

		for (int i = 0;i < E_CharaName::Max;i++)
		{
			char name[STRLENG] = {};

			if (fgets(dummy, 250, fp) != nullptr)//1行読み
			{
				fscanf_s(fp, "%[^,],%f,%f,%f,%f,",
					name, STRLENG,
					&m_texData[i].m_texScale.x,
					&m_texData[i].m_texScale.y,
					&m_texData[i].m_hitSize.x,
					&m_texData[i].m_hitSize.y
				);

				while (1)
				{
					int type;
					fscanf_s(fp, "%d,", &type);
					if (type == E_TexType::TexEnd)break;

					E_TexType key = (E_TexType)type;
					S_TexData value = {};

					int ID;
					fscanf_s(fp, "%d,%d,%f,%f,%f,", &ID, &value.m_texAnimMax, &value.m_texAnimMulti, &value.m_texSize.x, &value.m_texSize.y);
					value.m_pTex = &m_tex[ID];
					value.m_animCnt = 0;

					m_texData[i].m_tex.emplace(key, value);
				}
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
