#pragma once
#include "Widgets/Widget.h"
#include "Widgets/TextWidget.h"

namespace SSTU
{	
	class ProgressBar : public Widget
	{
	public:
		ProgressBar(
			const sf::Vector2f& size = sf::Vector2f(200.f, 30.f),
			float initialPercentage = 0.75f,
			const sf::Color& foregroundColor = sf::Color(128,255,128,255),
			const sf::Color& backgroundColor = sf::Color(128,128,128,255)
		);
		void UpdateValue(float value, float maxValue);
		virtual sf::FloatRect GetBound() const override;
		void SetForegroundColor(const sf::Color& color);
		void SetBackgroundColor(const sf::Color& color);

	private:
		virtual void Draw(sf::RenderWindow& window) override;
		virtual void OnLocationUpdated(const sf::Vector2f& newLocation) override;
		virtual void OnRotationUpdated(float newRotation) override;
		void CenterText();

		TextWidget m_text;
		
		sf::RectangleShape m_barFront;
		sf::RectangleShape m_barBack;

		float m_percent;

		sf::Color m_foregroundColor;
		sf::Color m_backgroundColor;
	};
}