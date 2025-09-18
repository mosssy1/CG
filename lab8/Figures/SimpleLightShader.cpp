#include "stdafx.h"
#include "SimpleLightShader.h"
#include "Vector4.h"
#include "Scene.h"
#include "ShadeContext.h"
#include "Intersection.h"
#include "Ray.h"
#include "ILightSource.h"
#include "VectorMath.h"


CSimpleLightShader::CSimpleLightShader(CSimpleMaterial const& material)
	: m_material(material)
{
}

/*
Запоминаем параметры материала, связанного с шейдером
*/
void CSimpleLightShader::SetMaterial(CSimpleMaterial const& material)
{
	m_material = material;
}

CVector4f CSimpleLightShader::Shade(CShadeContext const& shadeContext) const
{
	/*
	Получаем сцену из контекста закрашивания для того, чтобы вычислить вклад
	каждого из источников света в освещенность обрабатываемой точки
	*/
	CScene const& scene = shadeContext.GetScene();

	// Результирующий цвет
	CVector4f shadedColor;

	const size_t numLights = scene.GetLightsCount();

	// Пробегаемся по всем источникам света в сцене
	for (size_t i = 0; i < numLights; ++i)
	{
		ILightSource const& light = scene.GetLight(i);
		//auto& surfacePoint = shadeContext.GetSurfacePoint();
		//направление на источник света
		CVector3d lightDirection = light.GetDirectionFromPoint(shadeContext.GetSurfacePoint());
		//нормаль к поверхности
		CVector3d const& n = shadeContext.GetSurfaceNormal();

		/*//Определяем, находится ли объект в тени
		CSceneObject const* pSceneObject = NULL;
		CIntersection intersection;
		CRay shadowRay(surfacePoint, lightDirection);
		bool shadowed = scene.GetFirstHit(shadowRay, intersection, &pSceneObject);
		*/

		//интенсивность от источника света в точку
		double lightIntensity = light.GetIntensityInDirection(-lightDirection);
		
		/*
		if (shadowed)
		{
			lightIntensity = 0;
		}
		*/

		// Вычисляем скалярное произведение нормали и орт-вектора направления на источник света
		double nDotL = Max(Dot(n, Normalize(lightDirection)), 0.0);

		auto v = -Normalize(shadeContext.GetRayDirection());
		auto r = (n * 2 * Normalize(lightDirection) * Normalize(n)) / pow(n.GetLength(), 2) * Normalize(n) - Normalize(lightDirection);
		double rDotV = Max(Dot(v, Normalize(r)), 0.0);

		//сделать степень параметром
		CVector4f specularColor = static_cast<float>(lightIntensity * pow(rDotV, 1.0)) * light.GetSpecularIntensity() * m_material.GetSpecularColor();
		CVector4f ambientColor = light.GetAmbientIntensity() * m_material.GetAmbientColor() * 0.3;
		CVector4f diffuseColor = static_cast<float>(nDotL * lightIntensity) * light.GetDiffuseIntensity() * m_material.GetDiffuseColor();

		shadedColor = ambientColor + diffuseColor + specularColor;

	}

	// Возвращаем результирующий цвет точки
	return shadedColor;
}