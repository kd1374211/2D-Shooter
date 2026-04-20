#pragma once

//操作キーメモ 矢印 エンター スペース
enum class E_KeyChecks
{
	Up,
	Left,
	Down,
	Right,
	Enter,
	Space,
	Max
};

const std::map<E_KeyChecks, int> M_KeyTags
{
	{E_KeyChecks::Up,VK_UP},
	{E_KeyChecks::Left,VK_LEFT},
	{E_KeyChecks::Down,VK_DOWN},
	{E_KeyChecks::Right,VK_RIGHT},
	{E_KeyChecks::Enter,VK_RETURN},
	{E_KeyChecks::Space,VK_SPACE},
};

enum class E_KeyState
{
	Pressed,
	Hold,
	Released,
	None
};

struct S_KeyCheckState
{
	bool m_bIsPressedCurrent;
	bool m_bIsPressedPrev;
};

class C_KeyStateManager
{
public:

	void UpdateKeyState();
	E_KeyState GetKeyState(E_KeyChecks a_key);

private:

	std::map<E_KeyChecks, S_KeyCheckState> m_keyCheckState;

	C_KeyStateManager();
	~C_KeyStateManager();

public:

	static C_KeyStateManager& GetInstance()
	{
		static C_KeyStateManager instance;
		return instance;
	}

};

#define KEYMGR C_KeyStateManager::GetInstance()