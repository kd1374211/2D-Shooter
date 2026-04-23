#include "AutoCannon.h"
#include "WeaponTexManager.h"

C_AutoCannon::C_AutoCannon()
{
	m_nameTag = E_WeaponName::AutoCannon;
	m_texData = WPNTEXMGR.GetWeaponTexData(m_nameTag);
}

void C_AutoCannon::Update()
{
}

void C_AutoCannon::Draw()
{

}
