#pragma once

#include "Widgets/Widget.h"
#include "Widgets/TextWidget.h"
#include "Framework/Delegate.h"

namespace SSTU
{
	class Button : public Widget
	{
	public:
		Button(
			const std::string& textString = "Button",
			const std::string& texturePath = "SpaceShooterRedux/PNG/UI/buttonBlue.png"
		);

		virtual sf::FloatRect GetBound() const override;
		void SetTextString(const std::string& newStr);
		void SetTextSize(uint32_t charSize);
		virtual bool HandleEvent(const sf::Event& event) override;

		Delegate<> onClicked;

	private:
		virtual void Draw(sf::RenderWindow& window) override;
		virtual void OnLocationUpdated(const sf::Vector2f& newLocation) override;
		virtual void OnRotationUpdated(float newRotation) override;
		void CenterText();
		void ButtonUp();
		void ButtonDown();
		void OnMouseHover();

		std::shared_ptr<sf::Texture> m_buttonTexture;
		sf::Sprite m_buttonSprite;

		TextWidget m_buttonText;

		sf::Color m_buttonDefaultColor;
		sf::Color m_buttonDownColor;
		sf::Color m_buttonHoverColor;

		bool m_bIsButtonDown;
	};
}