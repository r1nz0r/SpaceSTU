#include "Framework/MathUtility.h"

namespace SSTU
{
	namespace Math
	{
		float DegreesToRadians(float degrees)
		{			
			return degrees * PI / STRAIGHT_ANGLE;
		}

		float RadiansToDegrees(float radians)
		{
			return radians * STRAIGHT_ANGLE / PI;
		}

		sf::Vector2f RotationToVector(float rotation)
		{
			float radians = DegreesToRadians(rotation);
			return sf::Vector2f{std::cos(radians), std::sinf(radians)};
		}

		bool IsNearlyEqual(const double numOne, const double numTwo)
		{
			return (std::fabs(numOne - numTwo) <= FLOAT_TOLERANCE);
		}

		bool IsZero(const double number)
		{
			return IsNearlyEqual(number, 0);
		}
	}
}