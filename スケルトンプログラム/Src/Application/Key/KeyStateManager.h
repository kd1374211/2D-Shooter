#pragma once

//操作キーメモ 矢印 エンター スペース

//使うキーをここに追加
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

//名前とVK対応
const std::map<E_KeyChecks, int> M_KeyTags
{
	{E_KeyChecks::Up,VK_UP},
	{E_KeyChecks::Left,VK_LEFT},
	{E_KeyChecks::Down,VK_DOWN},
	{E_KeyChecks::Right,VK_RIGHT},
	{E_KeyChecks::Enter,VK_RETURN},
	{E_KeyChecks::Space,VK_SPACE},
};

//キー状況
enum class E_KeyState
{
	Pressed,
	Hold,
	Released,
	None
};

//1つまえ/このフレームでキーが押されているか
struct S_KeyCheckState
{
	bool m_bIsPressedCurrent;
	bool m_bIsPressedPrev;
};

class C_KeyStateManager
{
public:

	void UpdateKeyState();

	//ゲッター
	E_KeyState GetKeyState(E_KeyChecks a_key);//キー状況
	bool GetIsPressed(E_KeyChecks a_key);//このフレームで押されたか

private:

	//キーとキー管理
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