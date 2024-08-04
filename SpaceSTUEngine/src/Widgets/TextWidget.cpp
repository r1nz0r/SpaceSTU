#include "Widgets/TextWidget.h"
#include "Framework/AssetManager.h"
namespace SSTU
{
	TextWidget::TextWidget(const std::string& text, const std::string& fontPath, uint32_t charSize)
		: Widget()
		, m_font(AssetManager::Instance().LoadFont(fontPath))
		, m_text(text, *m_font.get(), charSize)
	{

	}

	void TextWidget::SetString(const std::string& text)
	{
		m_text.setString(text);
	}

	void TextWidget::SetTextSize(uint32_t newSize)
	{
		m_text.setCharacterSize(newSize);
	}

	sf::FloatRect TextWidget::GetBound() const
	{
		return m_text.getGlobalBounds();
	}

	void TextWidget::Draw(sf::RenderWindow& window)
	{
		window.draw(m_text);
	}

	void TextWidget::OnLocationUpdated(const sf::Vector2f & newLocation)
	{
		m_text.setPosition(newLocation);
	}

	void TextWidget::OnRotationUpdated(float newRotation)
	{
		m_text.setRotation(newRotation);
	}
}