#pragma once
#include "../CharaTexConst.h"

class C_EnemyBase;

class C_EnemyManager
{
public:

	void SpawnEnemy(Math::Vector2 a_pos, E_CharaName a_enemy);
	void ClearEnemy();

	void Update();
	void Draw();

private:

	C_EnemyManager() {};
	~C_EnemyManager() {};

	std::vector<C_EnemyBase*> m_enemy;

public:

	static C_EnemyManager& GetInstance()
	{
		static C_EnemyManager instance;
		return instance;
	}

};

#define ENEMYMGR C_EnemyManager::GetInstance()