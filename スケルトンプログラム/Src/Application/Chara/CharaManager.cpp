#include "CharaManager.h"
#include "../Const/TextureConst.h"
#include "Enemy/EnemyConst.h"
#include "Player/Player.h"
#include "../Level/LevelManager.h"
#include "../Time/TimeManager.h"

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

	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_superSeedCool = -500;
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

void C_CharaManager::CheckEnemySpawn()
{
	if (TIMEMGR.GetTimeState() == E_TimeState::Normal || TIMEMGR.GetTimeState() == E_TimeState::Half && TIMEMGR.GetHalfTime())
	{
		//フレーム更新
		m_seedF++;

		//召喚チェック
		for (auto& itr : m_nowSeedData)
		{
			if (m_seedF == itr.m_spawnF)
			{
				SpawnEnemy(itr.m_pos, itr.m_name);
			}
		}
	}

	//フレームが最大ならシード再検索
	if (m_seedF >= FRAMES_ONESEED)
	{
		EnemySeedRand();
		m_seedF = 0;
	}
}

void C_CharaManager::EnemySeedRand()
{
	m_superSeedCool--;
	int randMax = 0;
	std::vector<int> availableSeeds;
	int nowSeed = -1;

	int randomNum = rand() % (abs(m_superSeedCool) + 2);
	for (auto &itr : m_seedData)
	{
		nowSeed++;
		if (m_superSeedCool > 0 || randomNum == 0)
		{
			if (itr.m_minLevel > LEVELMGR.GetLevel() || itr.m_maxLevel < LEVELMGR.GetLevel() || itr.m_isSuperSpawn)continue;
			randMax++;
			availableSeeds.push_back(nowSeed);
		}
		else
		{
			//スーパーシードロール
			if (itr.m_minLevel > LEVELMGR.GetLevel() || itr.m_maxLevel < LEVELMGR.GetLevel() || !itr.m_isSuperSpawn)continue;
			randMax++;
			availableSeeds.push_back(nowSeed);
		}
	}
	if (randMax == 0)return;

	int a = rand() % randMax;
	if (m_seedData[availableSeeds[a]].m_isSuperSpawn)m_superSeedCool = SUPERSEEDMIN;
	m_nowSeedData = m_seedData[availableSeeds[a]].m_enemy;
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

void C_CharaManager::RestartGame()
{
	m_seedF = 0;
	EnemySeedRand();
}

void C_CharaManager::SpawnPlayer(E_WeaponName a_weapon, Math::Vector2 a_pos)
{
	if (!m_player)
	{
		m_player = new C_Player(a_weapon, false);
		m_player->SetPos(a_pos);
	}
}

void C_CharaManager::SpawnBotPlayer(E_WeaponName a_weapon, Math::Vector2 a_pos)
{
	if (!m_player)
	{
		m_player = new C_Player(a_weapon, true);
		m_player->SetPos(a_pos);
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
	case E_CharaName::Bomber:
		m_enemy.push_back(new C_Bomber(a_pos));
		break;
	case E_CharaName::Torpedo:
		m_enemy.push_back(new C_Torpedo(a_pos));
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

void C_CharaManager::DrawSelectShip(Math::Vector2 a_pos, E_WeaponName a_weapon)
{
	S_PlayerSelectWeaponData select = GetSelectWeaponData(a_weapon);

	//武器
	S_TexData weapon = select.m_texDatas[E_SelectWeaponTexType::Select_Weapon];
	Math::Vector2 texSize = weapon.m_texSize;
	Math::Rectangle rec = { 0,0,(long)texSize.x,(long)texSize.y };
	SHADER.m_spriteShader.DrawTex(&(*weapon.m_tex), a_pos.x, a_pos.y, texSize.x * select.m_texScale.x, texSize.y * select.m_texScale.y, &rec);

	//エンジン
	S_TexData engine = select.m_texDatas[E_SelectWeaponTexType::Select_Engine];
	texSize = engine.m_texSize;
	rec = { 0,0,(long)texSize.x,(long)texSize.y };
	SHADER.m_spriteShader.DrawTex(&(*engine.m_tex), a_pos.x, a_pos.y, texSize.x * select.m_texScale.x, texSize.y * select.m_texScale.y, &rec);

	//炎
	S_TexData fire = select.m_texDatas[E_SelectWeaponTexType::Select_Fire];
	texSize = fire.m_texSize;
	rec = { 0,0,(long)texSize.x,(long)texSize.y };
	SHADER.m_spriteShader.DrawTex(&(*fire.m_tex), a_pos.x, a_pos.y, texSize.x * select.m_texScale.x, texSize.y * select.m_texScale.y, &rec);

	//本体
	S_BaseCharaTexData base = GetBaseTexData(E_CharaName::Player);
	S_TexData texData = base.m_texDatas.find(E_CharaBaseTexType::Base)->second;
	texSize = texData.m_texSize;
	rec = { 0,0,(long)texSize.x,(long)texSize.y };
	SHADER.m_spriteShader.DrawTex(&(*texData.m_tex), a_pos.x, a_pos.y, texSize.x * base.m_texScale.x, texSize.y * base.m_texScale.y, &rec);
}

void C_CharaManager::Init()
{
	LoadBaseTex();
	SetBaseTexData();
	LoadPlayerSelectWeaponTex();
	LoadCharaStatData();
	LoadSpawnData();
	m_superSeedCool = SUPERSEEDMIN;
}

void C_CharaManager::LoadBaseTex()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Assets/Data/Chara/CharaTexPathData.csv", "r") == 0)
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

				m_tex[i] = std::make_shared<KdTexture>();
				m_tex[i]->Load(path);
			}
		}

		fclose(fp);
	}
}

void C_CharaManager::SetBaseTexData()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Assets/Data/Chara/CharaTexData.csv", "r") == 0)
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

					data.m_tex = std::make_shared<KdTexture>();
					data.m_tex = m_tex[pathID];
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

	if (fopen_s(&fp, "Assets/Data/Chara/SelectWeaponData.csv", "r") == 0)
	{
		char dummy[250] = {};

		for (int i = 0;i < E_WeaponName::WeaponMax;i++)
		{
			char name[STRLENG] = {};

			if (fgets(dummy, 250, fp) != nullptr)//1行読み
			{
				fscanf_s(fp, "%[^,],%f,%f,%f,",
					name, STRLENG,
					&m_selectWeaponData[i].m_moveSpeed,
					&m_selectWeaponData[i].m_texScale.x,
					&m_selectWeaponData[i].m_texScale.y
				);
				m_selectWeaponData[i].m_texScale.z = 1.0f;

				for (int j = 0;j < E_SelectWeaponTexType::Select_Max;j++)
				{
					S_TexData* data = &m_selectWeaponData[i].m_texDatas[j];
					int pathID;

					fscanf_s(fp, "%d,%f,%f,%d,%f,",
						&pathID,
						&data->m_texSize.x,
						&data->m_texSize.y,
						&data->m_texAnimMax,
						&data->m_texAnimMulti);

					data->m_tex = std::make_shared<KdTexture>();
					data->m_tex = m_tex[pathID];
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

	if (fopen_s(&fp, "Assets/Data/Chara/CharaStatData.csv", "r") == 0)
	{
		char dummy[250] = {};

		for (int i = 0;i < E_CharaName::Max;i++)
		{
			char name[STRLENG] = {};

			if (fgets(dummy, 250, fp) != nullptr)//1行読み
			{
				fscanf_s(fp, "%[^,],%f,%d,%f,%d,%d,",
					name, STRLENG,
					&m_statData[i].m_hitRadius,
					&m_statData[i].m_health,
					&m_statData[i].m_moveSpeed,
					&m_statData[i].m_timeAddOnKill,
					&m_statData[i].m_scoreOnKill
				);
			}
		}

		fclose(fp);
	}
}

void C_CharaManager::LoadSpawnData()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Assets/Data/Spawn/EnemySpawnSeedData.csv", "r") == 0)
	{
		char dummy[250] = {};

		for (int i = 0;i < SEEDNUM;i++)
		{
			int type;
			S_EnemySeedData seed;

			if (fgets(dummy, 250, fp) != nullptr)//1行読み
			{
				fscanf_s(fp, "%d,%d,%d,%d,",
					&type,
					&seed.m_minLevel,
					&seed.m_maxLevel,
					&seed.m_isSuperSpawn
				);

				while (1)
				{
					S_EnemySpawnData spawn;

					fscanf_s(fp, "%d,", &spawn.m_name);

					if (spawn.m_name == E_CharaName::End)break;

					fscanf_s(fp, "%d,%f,%f,",
						&spawn.m_spawnF,
						&spawn.m_pos.x,
						&spawn.m_pos.y
					);

					seed.m_enemy.push_back(spawn);
				}

				m_seedData.push_back(seed);
			}
		}

		fclose(fp);
	}
}
