#include "stdafx.h"
#include "Solver.h"
#include <cmath>
#include <numbers>

namespace
{
constexpr float EQN_EPS = 1e-9f;
}

std::vector<float> Solver::Solve2(const std::vector<float>& coefs)
{
	assert(coefs.size() == 3);
	// x^2 + px + q = 0
	const auto p = coefs[1] / (2.0f * coefs[2]);
	const auto q = coefs[0] / coefs[2];

	const auto D = p * p - q;
	if (isZero(D))
	{
		return { -p };
	}
	else if (D < 0)
	{
		return {};
	}

	const auto sqrtD = sqrt(D);

	return { sqrtD - p, -sqrtD - p };
}

std::vector<float> Solver::Solve3(const std::vector<float>& coefs)
{
	assert(coefs.size() == 4);

	float A = coefs[2] / coefs[3];
	float B = coefs[1] / coefs[3];
	float C = coefs[0] / coefs[3];

	float sq_A = A * A;
	float p = 1.0 / 3 * (-1.0 / 3 * sq_A + B);
	float q = 1.0 / 2 * (2.0 / 27 * A * sq_A - 1.0 / 3 * A * B + C);
    float cb_p = p * p * p;
	
	float D = q * q + cb_p;

	std::vector<float> s;

	if (isZero(D))
	{
		if (isZero(q))
		{
			s.push_back(0);
		}
		else
		{
			float u = std::cbrt(-q);
			s.push_back(2 * u);
			s.push_back(-u);
		}
	}
	else if (D < 0)
	{
		float phi = 1.0 / 3 * std::acos(-q / std::sqrt(-cb_p));
		float t = 2 * std::sqrt(-p);

		s.push_back(t * std::cos(phi));
		s.push_back(-t * std::cos(phi + std::numbers::pi / 3));
		s.push_back(-t * std::cos(phi - std::numbers::pi / 3));
	}
	else 
	{
		float sqrt_D = std::sqrt(D);
		float u = std::cbrt(sqrt_D - q);
		float v = -std::cbrt(sqrt_D + q);

		s.push_back(u + v);
	}

	float sub = 1.0 / 3 * A;

	for (int i = 0; i < (int)s.size(); ++i)
	{
		s[i] -= sub;
	}

	return s;
}

std::vector<float> Solver::Solve4(const std::vector<float>& coefs)
{
	//x^4 + Ax^3 + Bx^2 + Cx + D = 0 
	assert(coefs.size() == 5);

	float A = coefs[3] / coefs[4];
	float B = coefs[2] / coefs[4];
	float C = coefs[1] / coefs[4];
	float D = coefs[0] / coefs[4];


	// преобразовываем так, чтобы убрать Аx^3
	//x^4 + px^2 + qx + r = 0 *
	float sq_A = A * A;
	float p = -3.0f / 8.0f * sq_A + B;
	float q = 1.0f / 8.0f * sq_A * A - 1.0f / 2.0f * A * B + C;
	float r = -3.0f / 256.0f * sq_A * sq_A + 1.0f / 16.0f * sq_A * B - 1.0f / 4.0f * A * C + D;
	std::vector<float> s; 

	if (isZero(r)) 
	{
		// сводится к видy (y^3 + py + q) = 0 
		std::vector<float> coeffs = { q, p, 0, 1 };
		std::vector<float> roots = Solve3(coeffs);

		roots.push_back(0);
		s = roots;
	}
	else
	{
		// решение промежуточного уравнения
		std::vector<float> coeffs = {
			1.0f / 2.0f * r * p - 1.0f / 8.0f * q * q,
			-r,
			-1.0f / 2.0f * p,
			1
		};

		std::vector<float> roots = Solve3(coeffs);

		float z = roots[0];

		float u = z * z - r;
		float v = 2 * z - p;

		if (isZero(u))
		{
			u = 0;
		}
		else if (u > 0)
		{
			u = std::sqrt(u);
		}
		else
		{
			return s;
		}

		if (isZero(v))
		{
			v = 0;
		}
		else if (v > 0)
		{
			v = std::sqrt(v);
		}
		else
		{
			return s;
		}

		coeffs = {
			z - u,
			q < 0 ? -v : v,
			1
		};

		std::vector<float> roots1 = Solve2(coeffs);

		coeffs = {
			z + u,
			q < 0 ? v : -v,
			1
		};

		std::vector<float> roots2 = Solve2(coeffs);

		s.insert(s.end(), roots1.begin(), roots1.end());
		s.insert(s.end(), roots2.begin(), roots2.end());
	}

	//возвращаемся к замене
	float sub = 1.0 / 4 * A;

	for (int i = 0; i < (int)s.size(); ++i)
	{
		s[i] -= sub;
	}

	return s;
}

bool Solver::isZero(float number)
{
	return (number > -EQN_EPS && number < EQN_EPS);
}