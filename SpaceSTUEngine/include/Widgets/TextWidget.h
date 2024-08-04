#pragma once
#include "Framework/Core.h"
#include "Widgets/Widget.h"
#include "SFML/Graphics.hpp"

namespace SSTU
{
	class TextWidget : public Widget
	{
	public:
		TextWidget(
			const std::string& text = "",
			const std::string& fontPath = "SpaceShooterRedux/Bonus/kenvector_future.ttf",
			uint32_t charSize = 10
		);

		void SetString(const std::string& text);
		void SetTextSize(uint32_t newSize);
		virtual sf::FloatRect GetBound() const override;

	private:
		virtual void Draw(sf::RenderWindow& window);
		virtual void OnLocationUpdated(const sf::Vector2f& newLocation);
		virtual void OnRotationUpdated(float newRotation);

		std::shared_ptr<sf::Font> m_font;
		sf::Text m_text;
	};
}