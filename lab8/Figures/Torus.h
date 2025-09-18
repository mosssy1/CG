#pragma once
#include "GeometryObjectWithInitialTransformImpl.h"

class Torus : public CGeometryObjectWithInitialTransformImpl
{
public:
	Torus(float tubeRadius, float mainRadius,
		CVector3d const& center = CVector3d(),
		CMatrix4d const& transform = CMatrix4d());

	bool Hit(CRay const& ray, CIntersection& intersection) const override;

	~Torus() = default;

private:
	float m_tubeRadius;
	float m_mainRadius;
};
