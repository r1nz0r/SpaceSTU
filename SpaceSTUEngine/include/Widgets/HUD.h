#pragma once

#include <SFML/Graphics.hpp>
#include "framework/Object.h"

namespace SSTU
{
	class HUD : public Object
	{
	public:
		virtual void Draw(sf::RenderWindow& windowRef) = 0;
		void NativeInit(const sf::RenderWindow& windowRef);
		bool HasInit() const { return m_bAlreadyInit; }
		virtual bool HandleEvent(const sf::Event& event);
		virtual void Tick(float deltaTime) = 0;
	protected:
		HUD();
		virtual void Init(const sf::RenderWindow& windowRef) = 0;

	private:
		bool m_bAlreadyInit;
	};
}