#pragma once

enum class E_SceneTypeTag
{
	Title,
	Select,
	Game,
	Max,
	None = -1
};

class C_SceneBase
{
public:

	C_SceneBase() :m_tag(E_SceneTypeTag::Max) {};
	~C_SceneBase() {};

	virtual void Update() = 0;
	virtual void Draw() = 0;
	void SetSceneTag(E_SceneTypeTag a_tag)
	{
		m_tag = a_tag;
	}
	E_SceneTypeTag GetSceneTag()const
	{
		return(m_tag);
	}

private:

	E_SceneTypeTag m_tag;

};