#include "KeyStateManager.h"

void C_KeyStateManager::UpdateKeyState()
{
	for (int i = 0;i < (int)E_KeyChecks::Max;i++)
	{
		auto itr = m_keyCheckState.find((E_KeyChecks)i);

		//キーコード
		int code = M_KeyTags.find(itr->first)->second;

		//押しチェック
		itr->second.m_bIsPressedPrev = itr->second.m_bIsPressedCurrent;
		if (GetAsyncKeyState(code) & 0x8000)
		{
			itr->second.m_bIsPressedCurrent = true;
		}
		else
		{
			itr->second.m_bIsPressedCurrent = false;
		}
	}
}

E_KeyState C_KeyStateManager::GetKeyState(E_KeyChecks a_key)
{
	auto itr = m_keyCheckState.find(a_key);
	S_KeyCheckState target = m_keyCheckState.find(a_key)->second;

	if (target.m_bIsPressedCurrent)
	{
		if (target.m_bIsPressedPrev)
		{
			return(E_KeyState::Hold);
		}
		else
		{
			return(E_KeyState::Pressed);
		}
	}
	else
	{
		if (target.m_bIsPressedPrev)
		{
			return(E_KeyState::Released);
		}
		else
		{
			return(E_KeyState::None);
		}
	}
}

C_KeyStateManager::C_KeyStateManager()
{
	for (int i = 0;i < (int)E_KeyChecks::Max;i++)
	{
		E_KeyChecks key = E_KeyChecks(i);
		S_KeyCheckState value = { false,false };
		m_keyCheckState.emplace(key, value);
	}
}

C_KeyStateManager::~C_KeyStateManager()
{
	m_keyCheckState.clear();
}
