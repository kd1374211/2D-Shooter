#include "CharaManager.h"
#include "../Const/TextureConst.h"
#include "Enemy/EnemyConst.h"
#include "Player/Player.h"

void C_CharaManager::Update()
{
	if (m_player)m_player->Update();

	if (!m_enemy.empty())
	{
		for (auto& itr : m_enemy)
		{
			itr->Update();
		}
	}
}

void C_CharaManager::Draw()
{
	if (!m_enemy.empty())
	{
		for (auto& itr : m_enemy)
		{
			itr->Draw();
		}
	}

	if (m_player)m_player->Draw();
}

void C_CharaManager::CheckEnemyDelete()
{
	if (!m_enemy.empty())
	{
		for (auto itr = m_enemy.begin();itr != m_enemy.end();)
		{
			if (!(*itr)->GetIsEnd())
			{
				itr++;
			}
			else
			{
				delete* itr;
				itr = m_enemy.erase(itr);
			}
		}
	}
}

void C_CharaManager::ClearChara()
{
	DeletePlayer();
	ClearEnemy();
}

void C_CharaManager::SpawnPlayer(E_WeaponName a_weapon)
{
	if (!m_player)
	{
		m_player = new C_Player(a_weapon);
	}
}

void C_CharaManager::DeletePlayer()
{
	if (m_player)
	{
		delete m_player;
		m_player = nullptr;
	}
}

void C_CharaManager::SpawnEnemy(Math::Vector2 a_pos, E_CharaName a_enemy)
{
	switch (a_enemy)
	{
	case E_CharaName::Fighter:
		m_enemy.push_back(new C_Fighter(a_pos));
		break;
	default:
		break;
	}
}

void C_CharaManager::ClearEnemy()
{
	if (m_enemy.empty())return;

	for (const auto& enemy : m_enemy)
	{
		delete enemy;
	}
	m_enemy.clear();
}

void C_CharaManager::Init()
{
	LoadBaseTex();
	SetBaseTexData();
	LoadPlayerSelectWeaponTex();
	LoadCharaStatData();
}

void C_CharaManager::LoadBaseTex()
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

				fscanf_s(fp, "%d,%[^,],", &ID,
					path, STRLENG);

				m_tex[i].Load(path);
			}
		}

		fclose(fp);
	}
}

void C_CharaManager::SetBaseTexData()
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
				fscanf_s(fp, "%[^,],%f,%f,",
					name, STRLENG,
					&m_texData[i].m_texScale.x,
					&m_texData[i].m_texScale.y
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

					m_texData[i].m_texDatas.emplace(texType, data);
				}
			}
		}

		fclose(fp);
	}
}

void C_CharaManager::LoadPlayerSelectWeaponTex()
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
				m_selectTexData[i].m_texScale.z = 1.0f;

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

void C_CharaManager::LoadCharaStatData()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Data/Chara/CharaStatData.csv", "r") == 0)
	{
		char dummy[250] = {};

		for (int i = 0;i < E_CharaName::Max;i++)
		{
			char name[STRLENG] = {};

			if (fgets(dummy, 250, fp) != nullptr)//1行読み
			{
				fscanf_s(fp, "%[^,],%f,%d,",
					name, STRLENG,
					&m_statData[i].m_hitRadius,
					&m_statData[i].m_health
				);
			}
		}

		fclose(fp);
	}
}

void C_CharaManager::Release()
{
	for (int i = 0;i < CHARABASETEXNUM;i++)
	{
		m_tex[i].Release();
	}
}
