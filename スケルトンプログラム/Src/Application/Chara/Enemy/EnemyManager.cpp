#include "EnemyManager.h"
#include "EnemyConst.h"

void C_EnemyManager::SpawnEnemy(Math::Vector2 a_pos, E_CharaName a_enemy)
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

void C_EnemyManager::ClearEnemy()
{
	if (m_enemy.empty())return;

	for (const auto& enemy : m_enemy)
	{
		delete enemy;
	}
	m_enemy.clear();
}

void C_EnemyManager::Update()
{
	if (!m_enemy.empty())
	{
		for (auto& itr : m_enemy)
		{
			itr->Update();
		}
	}

	CheckIsEnd();
}

void C_EnemyManager::Draw()
{
	if (!m_enemy.empty())
	{
		for (auto& itr : m_enemy)
		{
			itr->Draw();
		}
	}
}

void C_EnemyManager::CheckIsEnd()
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
