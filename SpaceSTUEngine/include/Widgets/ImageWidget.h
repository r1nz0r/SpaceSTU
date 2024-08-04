#pragma once
#include "Widgets/Widget.h"
#include "SFML/Graphics.hpp"

namespace SSTU
{
	class ImageWidget : public Widget
	{
	public:
		ImageWidget(const std::string& imagePath);
		void SetImage(const std::shared_ptr<sf::Texture>& texture);
		virtual sf::FloatRect GetBound() const override;

	private:
		virtual void OnLocationUpdated(const sf::Vector2f& newLocation) override;
		virtual void OnRotationUpdated(float newRotation) override;
		virtual void Draw(sf::RenderWindow& window) override;

		std::shared_ptr<sf::Texture> m_texture;
		sf::Sprite m_sprite;
	};
}