#pragma once
#include "Framework/Object.h"
#include "SFML/Graphics.hpp"

namespace SSTU
{
	class Widget : public Object
	{
	public:
		void NativeDraw(sf::RenderWindow& window);
		virtual bool HandleEvent(const sf::Event& event);
		void SetLocation(const sf::Vector2f newLocation);
		void SetRotation(float newRotation);
		sf::Vector2f GetLocation() const { return m_transform.getPosition(); }
		float GetRotation() const { return m_transform.getRotation(); }

		void SetVisibility(bool state);
		bool IsVisible() const { return m_bIsVisible; }
		virtual sf::FloatRect GetBound() const = 0;
		sf::Vector2f GetCenterPosition() const;

	protected:
		Widget();
	private:
		virtual void Draw(sf::RenderWindow& window) = 0;
		virtual void OnLocationUpdated(const sf::Vector2f& newLocation) = 0;
		virtual void OnRotationUpdated(float newRotation) = 0;

		sf::Transformable m_transform;
		bool m_bIsVisible;
	};
}