#include "Widgets/ImageWidget.h"
#include "Framework/AssetManager.h"

namespace SSTU
{
	ImageWidget::ImageWidget(const std::string& imagePath)
		: m_texture(AssetManager::Instance().LoadTexture(imagePath))
		, m_sprite(*m_texture.get())
	{

	}

	void ImageWidget::SetImage(const std::shared_ptr<sf::Texture>& texture)
	{
		if (!texture)
			return;
		
		m_texture = texture;
		m_sprite.setTexture(*m_texture.get());
	}

	sf::FloatRect ImageWidget::GetBound() const
	{
		return m_sprite.getGlobalBounds();
	}

	void ImageWidget::OnLocationUpdated(const sf::Vector2f& newLocation)
	{
		m_sprite.setPosition(newLocation);
	}

	void ImageWidget::OnRotationUpdated(float newRotation)
	{
		m_sprite.setRotation(newRotation);
	}

	void ImageWidget::Draw(sf::RenderWindow& window)
	{
		window.draw(m_sprite);
	}
}