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
		if (itr->CheckIsDead())continue;

		if (itr->GetCharaType() == E_CharaName::Torpedo)
		{
			for (int i = 0;i < 5;i++)
			{
				//敵位置・当たり半径
				Math::Vector2 EnemyPos = itr->GetPos();
				float EnemyHitRadius = itr->GetHitRadius();

				//ズラす
				EnemyPos.y += (TORPEDOHITDIST * (i - 2));

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
		else
		{
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

		//終わっていても飛ばす
		if (itr->GetIsEnd())continue;

		//弾位置・当たり判定
		Math::Vector2 BulletPos = itr->GetPos();
		float BulletHitRadius = itr->GetHitRadius();
		float Angle = itr->GetAngle();

		for (auto itr_hit : itr->GetHitCheckPos())
		{
			Math::Vector2 AnglePosX = { cosf(DirectX::XMConvertToRadians(Angle - 90)), sinf(DirectX::XMConvertToRadians(Angle - 90)) };
			Math::Vector2 AnglePosY = { cosf(DirectX::XMConvertToRadians(Angle)), sinf(DirectX::XMConvertToRadians(Angle)) };
			Math::Vector2 X = AnglePosX * itr_hit.x;
			Math::Vector2 Y = AnglePosY * itr_hit.y;

			Math::Vector2 CheckPos = BulletPos + X + Y;

			//座標差
			Math::Vector2 Dist = PlayerPos - CheckPos;

			//距離チェック
			if (sqrt(Dist.x * Dist.x + Dist.y * Dist.y) < PlayerHitRadius + BulletHitRadius)
			{
				//プレイヤー無敵チェック
				if (player->GetIsInvincible())
				{
					//弾Hit
					itr->OnHit();
				}
				else
				{
					//プレイヤー被弾
					player->GetHit();

					//弾Hit
					itr->OnHit();
				}

				break;
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
		//死んでいたら飛ばす
		if (itr_e->CheckIsDead())continue;

		if (itr_e->GetCharaType() == E_CharaName::Torpedo)
		{
			bool m_isHit = false;
			for (int i = 0;i < 5;i++)
			{
				if (m_isHit)break;

				//敵位置・当たり半径
				Math::Vector2 EnemyPos = itr_e->GetPos();
				float EnemyHitRadius = itr_e->GetHitRadius();

				//ズラす
				EnemyPos.y += (TORPEDOHITDIST * (i - 2));

				//弾用意
				std::vector<C_BulletBase*> bullet = BULLETMGR.GetBullets();
				for (auto itr_b : bullet)
				{
					//敵の弾なら飛ばす
					if (itr_b->GetBulletTeam() == E_BulletTeam::Enemy)continue;

					//終わっていても飛ばす
					if (itr_b->GetIsEnd())continue;

					//弾位置・当たり判定
					Math::Vector2 BulletPos = itr_b->GetPos();
					float BulletHitRadius = itr_b->GetHitRadius();
					float Angle = itr_b->GetAngle();

					for (auto itr_hit : itr_b->GetHitCheckPos())
					{
						Math::Vector2 AnglePosX = { cosf(DirectX::XMConvertToRadians(Angle - 90)), sinf(DirectX::XMConvertToRadians(Angle - 90)) };
						Math::Vector2 AnglePosY = { cosf(DirectX::XMConvertToRadians(Angle)), sinf(DirectX::XMConvertToRadians(Angle)) };
						Math::Vector2 X = AnglePosX * itr_hit.x;
						Math::Vector2 Y = AnglePosY * itr_hit.y;

						Math::Vector2 CheckPos = BulletPos + X + Y;

						//座標差
						Math::Vector2 Dist = EnemyPos - CheckPos;

						//距離チェック
						if (sqrt(Dist.x * Dist.x + Dist.y * Dist.y) < EnemyHitRadius + BulletHitRadius)
						{
							itr_e->GetHit(itr_b->GetDamage());
							itr_b->OnHit();
							m_isHit = true;

							break;
						}
					}
				}
			}
		}
		else
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

				//終わっていても飛ばす
				if (itr_b->GetIsEnd())continue;

				//弾位置・当たり判定
				Math::Vector2 BulletPos = itr_b->GetPos();
				float BulletHitRadius = itr_b->GetHitRadius();
				float Angle = itr_b->GetAngle();

				for (auto itr_hit : itr_b->GetHitCheckPos())
				{
					Math::Vector2 AnglePosX = { cosf(DirectX::XMConvertToRadians(Angle - 90)), sinf(DirectX::XMConvertToRadians(Angle - 90)) };
					Math::Vector2 AnglePosY = { cosf(DirectX::XMConvertToRadians(Angle)), sinf(DirectX::XMConvertToRadians(Angle)) };
					Math::Vector2 X = AnglePosX * itr_hit.x;
					Math::Vector2 Y = AnglePosY * itr_hit.y;

					Math::Vector2 CheckPos = BulletPos + X + Y;

					//座標差
					Math::Vector2 Dist = EnemyPos - CheckPos;

					//距離チェック
					if (sqrt(Dist.x * Dist.x + Dist.y * Dist.y) < EnemyHitRadius + BulletHitRadius)
					{
						itr_e->GetHit(itr_b->GetDamage());
						itr_b->OnHit();

						break;
					}
				}
			}
		}
	}
}
