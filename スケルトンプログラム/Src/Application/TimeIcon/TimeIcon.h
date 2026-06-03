#pragma once

enum class E_IconType
{
	Plus = 1,
	Minus = -1
};

class C_TimeIcon
{
public:

	C_TimeIcon() { Init(); }
	~C_TimeIcon() { Release(); }

	void SpawnIcon(Math::Vector2 a_pos, E_IconType a_type);
	void UpdateIcon();
	void DrawIcon();
	void DeleteAllIcon();

private:

	void Init();
	void Release();

	std::shared_ptr<KdTexture> m_plusIcon;
	std::shared_ptr<KdTexture> m_minusIcon;

	struct S_TimeIcon
	{
		E_IconType m_type;
		Math::Vector2 m_pos;
		float m_alpha;
		int m_lifeSpan;
	};
	std::vector<S_TimeIcon> m_icons;

	static const int ICONLIFE = 25;
	const float ALPHACHANGE = -0.04f;
	const Math::Vector2 TEXSIZE = { 67,36 };
	const Math::Vector2 ICONMOVE = { -0.1f,0.4f };
	const Math::Vector2 ICONSPAWN = { 0,30.0f };

public:

	static C_TimeIcon& GetInstance()
	{
		static C_TimeIcon instance;
		return instance;
	}

};

#define TIMEICON C_TimeIcon::GetInstance()