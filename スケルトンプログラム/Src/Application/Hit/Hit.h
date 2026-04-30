#pragma once

class C_SceneBase;

class C_Hit
{
public:

	C_Hit() {}
	~C_Hit(){}

	void HitCheck();

private:

	//プレイヤー・敵
	void PlayerEnemyHit();

	//プレイヤー・敵の弾
	void PlayerBulletHit();

	//敵・プレイヤーの弾
	void EnemyBulletHit();

};