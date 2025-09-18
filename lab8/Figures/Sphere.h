#pragma once
#include "GeometryObjectWithInitialTransformImpl.h"

class CSphere : public CGeometryObjectWithInitialTransformImpl
{
public:
	CSphere(
		double radius = 1, 
		CVector3d const& center = CVector3d(), 
		CMatrix4d const& transform = CMatrix4d());

	virtual bool Hit(CRay const& ray, CIntersection & intersection)const;
private:
};
