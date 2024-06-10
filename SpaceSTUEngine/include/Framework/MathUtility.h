#pragma once
#include "SFML/System.hpp"
namespace SSTU
{
	namespace Math
	{
		const float PI = 3.1415f;
		const float STRAIGHT_ANGLE = 180.0f;

		float DegreesToRadians(float angle);
		float RadiansToDegrees(float radians);
		sf::Vector2f RotationToVector(float rotation);
	}
}