#include "Framework/MathUtility.h"
#include <random>

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

		sf::Color LerpColor(const sf::Color& a, const sf::Color& b, float alpha)
		{
			int lerpR = LerpFloat(a.r, b.r, alpha);
			int lerpG = LerpFloat(a.g, b.g, alpha);
			int lerpB = LerpFloat(a.b, b.b, alpha);
			int lerpA = LerpFloat(a.a, b.a, alpha);

			return sf::Color(lerpR, lerpG, lerpB, lerpA);
		}

		sf::Vector2f LerpVector(const sf::Vector2f& a, const sf::Vector2f& b, float alpha)
		{
			float lerpX = LerpFloat(a.x, b.x, alpha);
			float lerpY = LerpFloat(a.y, b.y, alpha);

			return sf::Vector2f(lerpX, lerpY);
		}

		float LerpFloat(float a, float b, float alpha)
		{
			if (alpha > 1)
				alpha = 1;
			else if (alpha < 0)
				alpha = 0;

			return a + (b - a) * alpha;
		}

		float RandomRange(float min, float max)
		{
			std::random_device rd;
			std::mt19937 generator { rd() };

			std::uniform_real_distribution<float> distribution { min, max };

			return distribution(generator);
		}
		sf::Vector2f RandomNormalizedVector()
		{
			float randomX = RandomRange(-1, 1);
			float randomY = RandomRange(-1, 1);
			sf::Vector2f randVec { randomX, randomY };
			NormalizeVector(randVec);

			return randVec;
		}
	}
}