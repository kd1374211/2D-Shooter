#include "Hit.h"
#include "../Chara/CharaManager.h"
#include "../Bullet/BulletManager.h"
#include "../Chara/Player/Player.h"
#include "../Chara/Enemy/EnemyConst.h"

void C_Hit::HitCheck()
{
	PlayerEnemyHit();
	PlayerBulletHit();
	EnemyBulletHit();
}

void C_Hit::PlayerEnemyHit()
{
	C_Player* player = CHARAMGR.GetPlayer();
	Math::Vector2 PlayerPos = player->GetPos();
	Math::Vector2 PlayerHitRadius = player->GetHitRadius();

	std::vector<C_EnemyBase*> enemy = CHARAMGR.GetEnemy();
	for (auto itr : enemy)
	{
		if (itr->GetIsDead())continue;
	}
}

void C_Hit::PlayerBulletHit()
{
}

void C_Hit::EnemyBulletHit()
{
}
