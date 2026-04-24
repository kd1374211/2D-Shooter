#pragma once

class C_BulletBase;

enum class E_BulletTeam
{
	Player,
	Enemy
};

class C_BulletManager
{
public:

	void SpawnBullet(Math::Vector2 a_pos, E_BulletTeam a_team);

private:

	void Init();
	void Release();

	C_BulletManager() { Init(); }
	~C_BulletManager() { Release(); }

	std::vector<C_BulletBase*> m_bullets;

public:

	static C_BulletManager& GetInstance()
	{
		static C_BulletManager instance;
		return instance;
	}

};

#define BULLETMGR C_BulletManager::GetInstance()