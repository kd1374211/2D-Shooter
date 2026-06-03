#pragma once

//画像数
static const int CHARABASETEXNUM = 19;

//キャラ名
enum E_CharaName
{
	Player,
	Fighter,
	Bomber,
	Torpedo,
	Max,
	End = 999
};

//画像種まとめ
enum E_CharaBaseTexType
{
	Base,
	Attack,
	EngineEffect,
	OnHit,
	TexTypeMax,
	TexEnd = 999
};

//選択武器で変わる画像
enum E_SelectWeaponTexType
{
	Select_Weapon,
	Select_Engine,
	Select_Fire,
	Select_Max
};

//↓のsecond部分
struct S_TexData
{
	std::shared_ptr<KdTexture> m_tex;
	int m_animCnt;
	int m_texAnimMax;
	float m_texAnimMulti;
	Math::Vector2 m_texSize;
};

//本体画像
struct S_BaseCharaTexData
{
	std::map<int, S_TexData> m_texDatas;
	Math::Vector3 m_texScale;
};

//選択武器
enum E_WeaponName
{
	AutoCannon,
	BigSpaceGun,
	WeaponMax
};

//選択武器の画像
struct S_PlayerSelectWeaponData
{
	S_TexData m_texDatas[E_SelectWeaponTexType::Select_Max];
	Math::Vector3 m_texScale;
	float m_moveSpeed;
};

struct S_CharaStatData
{
	float m_hitRadius;
	int m_health;
	float m_moveSpeed;
	int m_timeAddOnKill;
	int m_scoreOnKill;
};

//シード数
static const int SEEDNUM = 28;

//敵出現情報
struct S_EnemySpawnData
{
	int m_spawnF;
	E_CharaName m_name;
	Math::Vector2 m_pos;
};

//シード情報
struct S_EnemySeedData
{
	int m_minLevel;
	int m_maxLevel;
	bool m_isSuperSpawn;
	std::vector<S_EnemySpawnData> m_enemy;
};