#include "HitCheck.h"
#include "../Chara/CharaManager.h"
#include "../Bullet/BulletManager.h"
#include "../Chara/Player/Player.h"
#include "../Chara/Enemy/EnemyConst.h"
#include "../Bullet/BulletConst.h"

void C_HitCheck::Check()
{
	PlayerEnemyHit();
	PlayerBulletHit();
	EnemyBulletHit();
}

void C_HitCheck::PlayerEnemyHit()
{
	//プレイヤー用意
	C_Player* player = CHARAMGR.GetPlayer();

	//無敵なら飛ばす
	if (player->GetIsInvincible())return;

	//プレイヤー位置・当たり半径
	Math::Vector2 PlayerPos = player->GetPos();
	float PlayerHitRadius = player->GetHitRadius();

	//敵用意
	std::vector<C_EnemyBase*> enemy = CHARAMGR.GetEnemy();
	for (auto itr : enemy)
	{
		//死んでる敵はスキップ
		if (itr->GetIsDead())continue;

		//敵位置・当たり半径
		Math::Vector2 EnemyPos = itr->GetPos();
		float EnemyHitRadius = itr->GetHitRadius();

		//座標差
		Math::Vector2 Dist = PlayerPos - EnemyPos;

		//距離チェック
		if (sqrt(Dist.x * Dist.x + Dist.y * Dist.y) < PlayerHitRadius + EnemyHitRadius)
		{
			//プレイヤー無敵チェック
			if (!player->GetIsInvincible())
			{
				//プレイヤー被弾
				player->GetHit();

				//処理終了
				return;
			}
		}
	}
}

void C_HitCheck::PlayerBulletHit()
{
	//プレイヤー用意
	C_Player* player = CHARAMGR.GetPlayer();

	//プレイヤー位置・当たり半径
	Math::Vector2 PlayerPos = player->GetPos();
	float PlayerHitRadius = player->GetHitRadius();

	//弾用意
	std::vector<C_BulletBase*> bullet = BULLETMGR.GetBullets();
	for (auto itr : bullet)
	{
		//プレイヤーの弾なら飛ばす
		if (itr->GetBulletTeam() == E_BulletTeam::Player)continue;

		//弾位置・当たり判定
		Math::Vector2 BulletPos = itr->GetPos();
		float BulletHitRadius = itr->GetHitRadius();

		//座標差
		Math::Vector2 Dist = PlayerPos - BulletPos;

		//距離チェック
		if (sqrt(Dist.x * Dist.x + Dist.y * Dist.y) < PlayerHitRadius + BulletHitRadius)
		{
			//プレイヤー無敵チェック
			if (player->GetIsInvincible())
			{
				//弾End
				itr->SetIsEnd(true);
			}
			else
			{
				//プレイヤー被弾
				player->GetHit();

				//弾End
				itr->SetIsEnd(true);
			}
		}
	}
}

void C_HitCheck::EnemyBulletHit()
{
	//敵用意
	std::vector<C_EnemyBase*> enemy = CHARAMGR.GetEnemy();
	for (auto itr_e : enemy)
	{
		//敵位置・当たり半径
		Math::Vector2 EnemyPos = itr_e->GetPos();
		float EnemyHitRadius = itr_e->GetHitRadius();

		//弾用意
		std::vector<C_BulletBase*> bullet = BULLETMGR.GetBullets();
		for (auto itr_b : bullet)
		{
			//敵の弾なら飛ばす
			if (itr_b->GetBulletTeam() == E_BulletTeam::Enemy)continue;

			//弾位置・当たり判定
			Math::Vector2 BulletPos = itr_b->GetPos();
			float BulletHitRadius = itr_b->GetHitRadius();

			//座標差
			Math::Vector2 Dist = EnemyPos - BulletPos;

			//距離チェック
			if (sqrt(Dist.x * Dist.x + Dist.y * Dist.y) < EnemyHitRadius + BulletHitRadius)
			{
				itr_e->GetHit();
				itr_b->SetIsEnd(true);
			}
		}
	}
}
