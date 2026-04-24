#include "CharaTexManager.h"

void C_CharaTexManager::LoadTexData()
{
	LoadBaseTex();
	LoadPlayerWeaponTex();
	LoadPlayerEngineTex();
}

void C_CharaTexManager::LoadBaseTex()
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

				for (int j = 0;j < E_CharaBaseTexType::TexTypeMax;j++)
				{
					char texPath[STRLENG] = {};
					S_TexData* data = &m_texData[i].m_texDatas[j];

					fscanf_s(fp, "%[^,],%d,%f,%f,%f,", texPath, STRLENG,
						&data->m_texAnimMax,
						&data->m_texAnimMulti,
						&data->m_texSize.x,
						&data->m_texSize.y);

					data->m_tex.Load(texPath);
				}
			}
		}

		fclose(fp);
	}
}

void C_CharaTexManager::LoadPlayerWeaponTex()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Data/Chara/PlayerWeaponTexData.csv", "r") == 0)
	{
		char dummy[300] = {};

		for (int i = 0; i < E_WeaponName::WeaponMax; i++)
		{
			if (fgets(dummy, 300, fp) != nullptr)//1行読み
			{
				char name[STRLENG] = {};
				char path_W[STRLENG] = {};
				char path_B[STRLENG] = {};
				S_WeaponTex* data = &m_weaponTexData[i];

				fscanf_s(fp, "%[^,],%f,%f,", name, STRLENG,
					&data->m_texScale.x,
					&data->m_texScale.y);

				fscanf_s(fp, "%[^,],%f,%f,%d,%f,", path_W, STRLENG,
					&data->m_weapon.m_texSize.x,
					&data->m_weapon.m_texSize.y,
					&data->m_weapon.m_texAnimMax,
					&data->m_weapon.m_texAnimMulti);

				fscanf_s(fp, "%[^,],%f,%f,%d,%f,", path_B, STRLENG,
					&data->m_bullet.m_texSize.x,
					&data->m_bullet.m_texSize.y,
					&data->m_bullet.m_texAnimMax,
					&data->m_bullet.m_texAnimMulti);

				data->m_weapon.m_tex.Load(path_W);
				data->m_bullet.m_tex.Load(path_B);
			}
		}

		fclose(fp);
	}
}

void C_CharaTexManager::LoadPlayerEngineTex()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Data/Chara/PlayerEngineTexData.csv", "r") == 0)
	{
		char dummy[300] = {};

		for (int i = 0; i < E_WeaponName::WeaponMax; i++)
		{
			if (fgets(dummy, 300, fp) != nullptr)//1行読み
			{
				char name[STRLENG] = {};
				char path_E[STRLENG] = {};
				char path_F[STRLENG] = {};
				S_EngineTex* data = &m_engineTexData[i];

				fscanf_s(fp, "%[^,],%f,%f,", name, STRLENG,
					&data->m_texScale.x,
					&data->m_texScale.y);

				fscanf_s(fp, "%[^,],%f,%f,%d,%f,", path_E, STRLENG,
					&data->m_engine.m_texSize.x,
					&data->m_engine.m_texSize.y,
					&data->m_engine.m_texAnimMax,
					&data->m_engine.m_texAnimMulti);

				fscanf_s(fp, "%[^,],%f,%f,%d,%f,", path_F, STRLENG,
					&data->m_fire.m_texSize.x,
					&data->m_fire.m_texSize.y,
					&data->m_fire.m_texAnimMax,
					&data->m_fire.m_texAnimMulti);

				data->m_engine.m_tex.Load(path_E);
				data->m_fire.m_tex.Load(path_F);
			}
		}

		fclose(fp);
	}
}

void C_CharaTexManager::ReleaseTex()
{
	//本体
	for (int i = 0;i < E_CharaName::Max;i++)
	{
		for (int j = 0;j < E_CharaBaseTexType::TexTypeMax;j++)
		{
			m_texData[i].m_texDatas[j].m_tex.Release();
		}
	}

	//武器
	for (int i = 0;i < E_WeaponName::WeaponMax;i++)
	{
		m_weaponTexData->m_weapon.m_tex.Release();
		m_weaponTexData->m_bullet.m_tex.Release();
	}

	//エンジン
	for (int i = 0;i < E_WeaponName::WeaponMax;i++)
	{
		m_engineTexData->m_engine.m_tex.Release();
		m_engineTexData->m_fire.m_tex.Release();
	}
}
