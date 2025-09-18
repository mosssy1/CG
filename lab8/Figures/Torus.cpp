#include "stdafx.h"
#include "Torus.h"
#include "Ray.h"
#include "Intersection.h"
#include "Solver.h"
#include <numbers>

namespace
{
constexpr float EPSILON = 0.0001f;
}

Torus::Torus(float tubeRadius, float mainRadius, CVector3d const& center, CMatrix4d const& transform)
	: CGeometryObjectWithInitialTransformImpl(transform)
	, m_tubeRadius(tubeRadius)
	, m_mainRadius(mainRadius)
{
	CMatrix4d initialTransform;
	initialTransform.Translate(center.x, center.y, center.z);

	SetInitialTransform(initialTransform);
}

bool Torus::Hit(CRay const& ray, CIntersection& intersection) const
{
	//обратное преобразование луча
	CRay invRay = Transform(ray, GetInverseTransform());
	const auto rayOrigin = invRay.GetStart();
	const auto rayDirection = invRay.GetDirection();

	// (x^2 + y^2 + z^2 + R^2 - r^2)^2 - 4R^2(x^2 + y^2) = 0
	// A*t^4 + B*t^3 + C*t^2 + D*t + E = 0
	
	// A = firstCoef = x^2 + y^2+ z^2
	// B = secondCoef = x0^2 + y0^2 + z0^2 -r^2 -R^2
	// C = thirdCoef = x0*x + y0*y + z0*z
	// D = fourthCoef = 4R^2
	const float firstCoef = std::powf(rayDirection.x, 2) + std::powf(rayDirection.y, 2) + std::powf(rayDirection.z, 2);
	const float secondCoef = std::powf(rayOrigin.x, 2) + std::powf(rayOrigin.y, 2) + std::powf(rayOrigin.z, 2) - std::powf(m_mainRadius, 2) - std::powf(m_tubeRadius, 2);
	const float thirdCoef = rayOrigin.x * rayDirection.x + rayOrigin.y * rayDirection.y + rayOrigin.z * rayDirection.z;
	const float fourthCoef = 4.0 * std::powf(m_mainRadius, 2);

	//B^2 - D*(r^2 -y0^2)
	// 4CB + 2Dy*y0 
	// 2Ab + 4C^2 + D * y^2
	// 4Ac
	// A^2
	const std::vector<float> coeffs = {
		secondCoef * secondCoef - fourthCoef * (std::powf(m_tubeRadius, 2) - std::powf(rayOrigin.y, 2)),
		4.0f * thirdCoef * secondCoef + 2.0f * fourthCoef * static_cast<float>(rayOrigin.y) * static_cast<float>(rayDirection.y),
		2.0f * firstCoef * secondCoef + 4.0f * std::powf(thirdCoef, 2) + fourthCoef * std::powf(rayDirection.y, 2),
		4.0f * firstCoef * thirdCoef,
		std::powf(firstCoef, 2)
	};
	
	//решаем
	const auto solution = Solver::Solve4(coeffs);
	
	//наличие пересечения
	if (solution.empty())
	{
		return false;
	}

	//ближайшее пересесечние
	auto min = FLT_MAX;
	for (auto number : solution)
	{
		if (number > EPSILON && number < min)
		{
			min = number;
		}
	}
	//нормаль через частную производную посчитать, подставить точку пересечения
	//точки пересечения
	auto hitPoint = ray.GetPointAtTime(min); 
	auto hitPointInObjectSpace = invRay.GetPointAtTime(min);
	auto hitNormalInObjectSpace = hitPointInObjectSpace;
	auto hitNormal = GetNormalMatrix() * hitNormalInObjectSpace;

	CHitInfo hit(
		min, *this,
		hitPoint, hitPointInObjectSpace,
		hitNormal, hitNormalInObjectSpace);

	intersection.AddHit(hit);
	return true;
}
