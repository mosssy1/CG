#pragma once
#include "IShader.h"
#include "SimpleMaterial.h"

/*
Простой шейдер, выполняющий расчет диффузной составляющей отраженного света
*/
class CSimpleLightShader :
	public IShader
{
public:
	CSimpleLightShader(CSimpleMaterial const& material = CSimpleMaterial());

	/*
	В качестве параметра шейдера выступает класс CSimpleMaterial, хранящий в простейшем случае
	диффузный цвет материала поверхности объекта
	*/
	void SetMaterial(CSimpleMaterial const& material);

	/*
	Вычисление цвета с объекта
	*/
	virtual CVector4f Shade(CShadeContext const & shadeContext)const;
private:
	CSimpleMaterial m_material;
};
