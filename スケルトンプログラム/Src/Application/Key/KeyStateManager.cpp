#include "KeyStateManager.h"

void C_KeyStateManager::UpdateKeyState()
{
	for (auto itr : m_keyCheckState)
	{
		//キーコード
		int code = M_KeyTags.find(itr.first)->second;

		//押しチェック
		itr.second.m_bIsPressedPrev = itr.second.m_bIsPressedCurrent;
		itr.second.m_bIsPressedCurrent = (GetAsyncKeyState(code) & 0x8000);
	}
}

E_KeyState C_KeyStateManager::GetKeyState(E_KeyChecks a_key)
{
	return(E_KeyState::Pressed);
}

C_KeyStateManager::C_KeyStateManager()
{
	for (int i = 0;i < (int)E_KeyChecks::Max;i++)
	{
		E_KeyChecks key = E_KeyChecks(i);
		m_keyCheckState.emplace(key, false, false);
	}
}

C_KeyStateManager::~C_KeyStateManager()
{
	m_keyCheckState.clear();
}
