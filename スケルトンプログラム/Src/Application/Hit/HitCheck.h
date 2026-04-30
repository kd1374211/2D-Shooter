#pragma once

class C_SceneBase;

class C_HitCheck
{
public:

	void Check();

private:

	C_HitCheck() {}
	~C_HitCheck() {}

	//プレイヤー・敵
	void PlayerEnemyHit();

	//プレイヤー・敵の弾
	void PlayerBulletHit();

	//敵・プレイヤーの弾
	void EnemyBulletHit();

public:

	static C_HitCheck& GetInstance()
	{
		static C_HitCheck instance;
		return instance;
	}

};

#define HITCHECK C_HitCheck::GetInstance()