#pragma once

enum class E_WeaponType
{
	AutoCannon,
	BigSpaceGun,
	Rocket,
	Zapper,
	Max
};

class C_WeaponBase
{
public: 

	C_WeaponBase() :m_type(E_WeaponType::Max) {};
	~C_WeaponBase() {};

	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:

	E_WeaponType m_type;

};