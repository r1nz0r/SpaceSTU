#include "Widgets/Button.h"
#include "Framework/AssetManager.h"

namespace SSTU
{
	Button::Button(const std::string& textString, const std::string& texturePath)
		: m_buttonTexture(AssetManager::Instance().LoadTexture(texturePath))
		, m_buttonSprite(*(m_buttonTexture.get()))
		, m_buttonText(textString, "SpaceShooterRedux/Bonus/kenvector_future.ttf", 30)
		, m_buttonDefaultColor(128, 128, 128, 255)
		, m_buttonDownColor(64, 64, 64, 255)
		, m_buttonHoverColor(190, 190, 190, 255)
		, m_bIsButtonDown(false)
	{
		m_buttonSprite.setColor(m_buttonDefaultColor);
		CenterText();
	}

	sf::FloatRect Button::GetBound() const
	{
		return m_buttonSprite.getGlobalBounds();
	}

	void Button::SetTextString(const std::string& newStr)
	{
		m_buttonText.SetString(newStr);
		CenterText();
	}

	void Button::SetTextSize(uint32_t charSize)
	{
		m_buttonText.SetTextSize(charSize);
		CenterText();
	}

	bool Button::HandleEvent(const sf::Event& event)
	{
		if (!IsVisible())
			return false;

		bool handled = false;

		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (m_buttonSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)
					&& m_bIsButtonDown)
				{
					onClicked.Notify();
					handled = true;
				}
			}

			ButtonUp();
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (m_buttonSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				ButtonDown();
				handled = true;
			}
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (m_buttonSprite.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
				{
					OnMouseHover();
				}
				else
				{
					ButtonUp();
				}
				handled = true;
			}
		}

		return handled || Widget::HandleEvent(event);
	}

	void Button::Draw(sf::RenderWindow& window)
	{
		window.draw(m_buttonSprite);
		m_buttonText.NativeDraw(window);
	}

	void Button::OnLocationUpdated(const sf::Vector2f& newLocation)
	{
		m_buttonSprite.setPosition(newLocation);
		CenterText();
	}
	
	void Button::OnRotationUpdated(float newRotation)
	{
		m_buttonSprite.setRotation(newRotation);
		m_buttonText.SetRotation(newRotation);
	}


	void Button::CenterText()
	{
		sf::Vector2f widgetCenter = GetCenterPosition();
		sf::FloatRect textBound = m_buttonText.GetBound();
		m_buttonText.SetLocation(widgetCenter - sf::Vector2f(textBound.width * 0.5, textBound.height));
	}

	void Button::ButtonUp()
	{
		m_bIsButtonDown = false;
		m_buttonSprite.setColor(m_buttonDefaultColor);
	}

	void Button::ButtonDown()
	{
		m_bIsButtonDown = true;
		m_buttonSprite.setColor(m_buttonDownColor);
	}

	void Button::OnMouseHover()
	{
		m_buttonSprite.setColor(m_buttonHoverColor);
	}
}