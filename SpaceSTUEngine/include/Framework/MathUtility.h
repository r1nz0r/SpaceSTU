#pragma once
#include "SFML/System.hpp"
namespace SSTU
{
	namespace Math
	{
		constexpr float PI = 3.1415f;
		constexpr float STRAIGHT_ANGLE = 180.0f;
		constexpr double FLOAT_TOLERANCE = 1e-10;

		float DegreesToRadians(float angle);
		float RadiansToDegrees(float radians);
		sf::Vector2f RotationToVector(float rotation);
		bool IsNearlyEqual(const double numOne, const double numTwo);
		bool IsZero(const double number);

		template<typename T>
		float GetVectorLength(const sf::Vector2<T>& vector)
		{
			return std::sqrt(vector.x * vector.x + vector.y * vector.y);
		}

		template<typename T>
		sf::Vector2<T>& ScaleVector(sf::Vector2<T>& vector, float factor)
		{
			vector.x *= factor;
			vector.y *= factor;
			return vector;
		}

		template<typename T>
		sf::Vector2<T>& NormalizeVector(sf::Vector2<T>& vector)
		{
			float vectorLength = GetVectorLength(vector);
			if (IsZero(vectorLength)) return vector;

			ScaleVector(vector, 1.0f / vectorLength);
			return vector;
		}
	}
}