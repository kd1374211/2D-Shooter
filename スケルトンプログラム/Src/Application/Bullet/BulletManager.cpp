#include "BulletManager.h"
#include "BulletConst.h"
#include "../Const/TextureConst.h"

void C_BulletManager::SpawnBullet(Math::Vector2 a_pos, E_BulletType a_type)
{
	switch (a_type)
	{
	case E_BulletType::B_AutoCannon:
		m_bullets.push_back(new C_AutoCannon_Bullet(a_pos));
		break;
	default:
		break;
	}
}

void C_BulletManager::ClearBullet()
{
	if (m_bullets.empty())return;

	for (const auto& bullet : m_bullets)
	{
		delete bullet;
	}
	m_bullets.clear();
}

void C_BulletManager::Update()
{
	if (!m_bullets.empty())
	{
		for (auto &itr : m_bullets)
		{
			itr->Update();
		}
	}
}

void C_BulletManager::Draw()
{
	if (!m_bullets.empty())
	{
		for (auto& itr : m_bullets)
		{
			itr->Draw();
		}
	}
}

void C_BulletManager::CheckBulletDelete()
{
	if (!m_bullets.empty())
	{
		for (auto itr = m_bullets.begin();itr != m_bullets.end();)
		{
			if ((*itr)->GetIsInScreen())
			{
				itr++;
			}
			else
			{
				delete* itr;
				itr = m_bullets.erase(itr);
			}
		}
	}
}

void C_BulletManager::Init()
{
	LoadData();
}

void C_BulletManager::Release()
{
	for (int i = 0;i < E_BulletType::BulletMax;i++)
	{
		m_bulletBaseTexData[i].m_tex.Release();
	}
}

void C_BulletManager::LoadData()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Data/Bullet/BulletTexData.csv", "r") == 0)
	{
		char dummy[250] = {};

		for (int i = 0;i < E_BulletType::BulletMax;i++)
		{
			char name[STRLENG] = {};
			char texPath[STRLENG] = {};

			if (fgets(dummy, 250, fp) != nullptr)//1行読み
			{
				S_BulletTexData* data = &m_bulletBaseTexData[i];

				fscanf_s(fp, "%[^,],%[^,],%f,%f,%f,%f,%d,%f,",
					name, STRLENG,
					texPath, STRLENG,
					&data->m_texSize.x,
					&data->m_texSize.y,
					&data->m_texScale.x,
					&data->m_texScale.y,
					&data->m_texAnimMax,
					&data->m_texAnimMulti);

				data->m_tex.Load(texPath);
			}
		}

		fclose(fp);
	}
}
