#include "WeaponTexManager.h"

void C_WeaponTexManager::LoadTex()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Data/Weapon/WeaponTexData.csv", "r") == 0)
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

				fscanf_s(fp, "%[^,],%f,%f,",	name, STRLENG,
												&data->m_texScale.x, 
												&data->m_texScale.y);

				fscanf_s(fp, "%[^,],%f,%f,%d,%f,",	path_W, STRLENG,
													&data->m_weapon.m_texSize.x,
													&data->m_weapon.m_texSize.y,
													&data->m_weapon.m_animCntMax,
													&data->m_weapon.m_animCntMulti);

				fscanf_s(fp, "%[^,],%f,%f,%d,%f,",	path_B, STRLENG,
													&data->m_bullet.m_texSize.x,
													&data->m_bullet.m_texSize.y,
													&data->m_bullet.m_animCntMax,
													&data->m_bullet.m_animCntMulti);

				data->m_weapon.m_tex.Load(path_W);
				data->m_bullet.m_tex.Load(path_B);
			}
		}

		fclose(fp);
	}
}

void C_WeaponTexManager::ReleaseTex()
{
	for (int i = 0;i < E_WeaponName::WeaponMax;i++)
	{
		m_weaponTexData->m_weapon.m_tex.Release();
		m_weaponTexData->m_bullet.m_tex.Release();
	}
}
