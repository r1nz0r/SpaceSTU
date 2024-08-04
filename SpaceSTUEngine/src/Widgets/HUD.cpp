#include "widgets/HUD.h"

namespace SSTU
{
	void HUD::NativeInit(const sf::RenderWindow& windowRef)
	{
		if (!m_bAlreadyInit)
		{
			m_bAlreadyInit = true;
			Init(windowRef);
		}
	}

	bool HUD::HandleEvent(const sf::Event& event)
	{
		return false;
	}

	HUD::HUD()
		: m_bAlreadyInit { false }
	{}
}