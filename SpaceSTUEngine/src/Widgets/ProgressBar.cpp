#include "Widgets/ProgressBar.h"
#include "Framework/AssetManager.h"

namespace SSTU
{	
	ProgressBar::ProgressBar(
		const sf::Vector2f& size,
		float initialPercentage,
		const sf::Color& foregroundColor,
		const sf::Color& backgroundColor
	)	: m_text("")
		, m_barFront(size)
		, m_barBack(size)
		, m_percent(initialPercentage)
		, m_foregroundColor(foregroundColor)
		, m_backgroundColor(backgroundColor)
	{
		m_barFront.setFillColor(m_foregroundColor);
		m_barBack.setFillColor(m_backgroundColor);
		m_text.SetTextSize(20);
	}

	void ProgressBar::UpdateValue(float value, float maxValue)
	{
		if (maxValue == 0)
			return;

		m_percent = value / maxValue;
		std::string valueStr = std::to_string((int)value) + "/" + std::to_string((int)maxValue);
		m_text.SetString(valueStr);
		sf::Vector2f barSize = m_barBack.getSize();
		m_barFront.setSize(sf::Vector2f(barSize.x * m_percent, barSize.y));
		CenterText();
	}

	sf::FloatRect ProgressBar::GetBound() const
	{
		return m_barBack.getGlobalBounds();
	}

	void ProgressBar::SetForegroundColor(const sf::Color& color)
	{
		m_barFront.setFillColor(color);
	}

	void ProgressBar::SetBackgroundColor(const sf::Color & color)
	{
		m_barBack.setFillColor(color);
	}

	void ProgressBar::Draw(sf::RenderWindow& window)
	{
		window.draw(m_barBack);
		window.draw(m_barFront);
		m_text.NativeDraw(window);
	}

	void ProgressBar::OnLocationUpdated(const sf::Vector2f& newLocation)
	{
		m_text.SetLocation(newLocation);
		m_barFront.setPosition(newLocation);
		m_barBack.setPosition(newLocation);
		CenterText();
	}

	void ProgressBar::OnRotationUpdated(float newRotation)
	{
		m_text.SetRotation(newRotation);
		m_barFront.setRotation(newRotation);
		m_barBack.setRotation(newRotation);
	}

	void ProgressBar::CenterText()
	{
		sf::Vector2f widgetCenter = GetCenterPosition();
		sf::FloatRect textBound = m_text.GetBound();
		m_text.SetLocation(widgetCenter - sf::Vector2f(textBound.width * 0.5, textBound.height));
	}
}