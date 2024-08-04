#include "Widgets/Widget.h"

namespace SSTU
{
	Widget::Widget()
		: m_bIsVisible(true)
		, m_transform()
	{}

	void Widget::NativeDraw(sf::RenderWindow& window)
	{
		if (m_bIsVisible)
			Draw(window);
	}

	bool Widget::HandleEvent(const sf::Event& event)
	{
		return false;
	}

	void Widget::SetLocation(const sf::Vector2f newLocation)
	{
		m_transform.setPosition(newLocation);
		OnLocationUpdated(newLocation);
	}

	void Widget::SetRotation(float newRotation)
	{
		m_transform.setRotation(newRotation);
		OnRotationUpdated(newRotation);
	}

	void Widget::SetVisibility(bool state)
	{
		m_bIsVisible = state;
	}
	sf::Vector2f Widget::GetCenterPosition() const
	{
		sf::FloatRect bound = GetBound();
		return sf::Vector2f(bound.left + 0.5f * bound.width, bound.top + 0.5f * bound.height);
	}
}