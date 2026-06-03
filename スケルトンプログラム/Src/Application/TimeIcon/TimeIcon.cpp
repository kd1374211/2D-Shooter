#include "TimeIcon.h"

void C_TimeIcon::SpawnIcon(Math::Vector2 a_pos, E_IconType a_type)
{
	S_TimeIcon data;
	data.m_pos = a_pos + ICONSPAWN * (int)a_type;
	data.m_lifeSpan = ICONLIFE;
	data.m_alpha = 1.0f;
	data.m_type = a_type;
	m_icons.push_back(data);
}

void C_TimeIcon::UpdateIcon()
{
	if (!m_icons.empty())
	{
		for (auto itr = m_icons.begin(); itr != m_icons.end();)
		{
			itr->m_pos += ICONMOVE * (int)itr->m_type;
			itr->m_alpha += ALPHACHANGE;
			itr->m_lifeSpan--;

			if (itr->m_lifeSpan <= 0)
			{
				itr = m_icons.erase(itr);
			}
			else
			{
				itr++;
			}
		}
	}
}

void C_TimeIcon::DrawIcon()
{
	if (!m_icons.empty())
	{
		for (auto &itr : m_icons)
		{
			Math::Rectangle rec = { 0,0,(long)TEXSIZE.x,(long)TEXSIZE.y };
			Math::Color color = { 1,1,1,itr.m_alpha };

			if (itr.m_type == E_IconType::Plus)
			{
				SHADER.m_spriteShader.DrawTex(&(*m_plusIcon), itr.m_pos.x, itr.m_pos.y, &rec, &color);
			}
			else if (itr.m_type == E_IconType::Minus)
			{
				SHADER.m_spriteShader.DrawTex(&(*m_minusIcon), itr.m_pos.x, itr.m_pos.y, &rec, &color);
			}
		}
	}
}

void C_TimeIcon::DeleteAllIcon()
{
	m_icons.clear();
}

void C_TimeIcon::Init()
{
	m_plusIcon = std::make_shared<KdTexture>();
	m_plusIcon->Load("Assets/Texture/Time/PlusIcon.png");
	m_minusIcon = std::make_shared<KdTexture>();
	m_minusIcon->Load("Assets/Texture/Time/MinusIcon.png");
}

void C_TimeIcon::Release()
{
	DeleteAllIcon();
}
