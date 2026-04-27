#include "CharaTexManager.h"

void C_CharaTexManager::LoadTexData()
{
	LoadBaseTex();
	SetBaseTexData();
	LoadPlayerSelectWeaponTex();
}

void C_CharaTexManager::LoadBaseTex()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Data/Chara/CharaTexPathData.csv", "r") == 0)
	{
		char dummy[250] = {};

		for (int i = 0;i < CHARABASETEXNUM;i++)
		{
			if (fgets(dummy, 250, fp) != nullptr)//1行読み
			{
				int ID;
				char path[STRLENG] = {};

				fscanf_s(fp, "%d,%[^,],",	&ID,
											path, STRLENG);

				m_tex[i].Load(path);
			}
		}

		fclose(fp);
	}
}

void C_CharaTexManager::SetBaseTexData()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Data/Chara/CharaTexData.csv", "r") == 0)
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
					int texType, pathID;

					if (fscanf_s(fp, "%d,", &texType));

					if (texType == E_CharaBaseTexType::TexEnd)break;

					S_TexData data;

					fscanf_s(fp, "%d,%d,%f,%f,%f,",
						&pathID,
						&data.m_texAnimMax,
						&data.m_texAnimMulti,
						&data.m_texSize.x,
						&data.m_texSize.y);

					data.m_tex = &m_tex[pathID];
					data.m_animCnt = 0;

					m_texData[i].m_texDatas.emplace(texType,data);
				}
			}
		}

		fclose(fp);
	}
}

void C_CharaTexManager::LoadPlayerSelectWeaponTex()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Data/Chara/SelectWeaponTexData.csv", "r") == 0)
	{
		char dummy[250] = {};

		for (int i = 0;i < E_WeaponName::WeaponMax;i++)
		{
			char name[STRLENG] = {};

			if (fgets(dummy, 250, fp) != nullptr)//1行読み
			{
				fscanf_s(fp, "%[^,],%f,%f,",
					name, STRLENG,
					&m_selectTexData[i].m_texScale.x,
					&m_selectTexData[i].m_texScale.y
					);

				for (int j = 0;j < E_SelectWeaponTexType::Select_Max;j++)
				{
					S_TexData* data = &m_selectTexData[i].m_texDatas[j];
					int pathID;

					fscanf_s(fp, "%d,%f,%f,%d,%f,",
								&pathID,
								&data->m_texSize.x,
								&data->m_texSize.y,
								&data->m_texAnimMax,
								&data->m_texAnimMulti);

					data->m_tex = &m_tex[pathID];
					data->m_animCnt = 0;
				}
			}
		}

		fclose(fp);
	}
}

void C_CharaTexManager::ReleaseTex()
{
	for (int i = 0;i < CHARABASETEXNUM;i++)
	{
		m_tex[i].Release();
	}
}
