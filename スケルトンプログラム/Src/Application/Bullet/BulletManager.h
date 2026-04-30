#pragma once
#include "BulletTexConst.h"

class C_BulletBase;

class C_BulletManager
{
public:

	//弾召喚・削除
	void SpawnBullet(Math::Vector2 a_pos, float a_speed, float a_shotAngle, E_BulletType a_type);
	void ClearBullet();

	void Update();
	void Draw();

	//画面外チェック
	void CheckBulletDelete();

	//ゲッター
	S_BulletTexData* GetTexData(E_BulletType a_bullet) { return(&m_bulletBaseTexData[a_bullet]); }
	std::vector<C_BulletBase*> &GetBullets() { return(m_bullets); }

private:

	void Init();
	void Release();

	void LoadData();

	C_BulletManager() { Init(); }
	~C_BulletManager() { Release(); }

	//弾コンテナ
	std::vector<C_BulletBase*> m_bullets;

	//画像
	S_BulletTexData m_bulletBaseTexData[E_BulletType::BulletMax];

public:

	static C_BulletManager& GetInstance()
	{
		static C_BulletManager instance;
		return instance;
	}

};

#define BULLETMGR C_BulletManager::GetInstance()