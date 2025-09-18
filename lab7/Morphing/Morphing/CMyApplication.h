#pragma once
#include "CGLapplication.h"
#include "Shader.h"
#include "AnimationController.h"

class CMyApplication : public CGLApplication
{
public:
	CMyApplication(const char* title, int width, int height, int argc, char* argv[]);
	~CMyApplication() = default;

protected:
	virtual void OnDisplay();
	virtual void OnInit();
	virtual void OnIdle();
	virtual void OnReshape(int width, int height);
	virtual void OnMouse(int button, int state, int x, int y) override;
	virtual void OnMotion(int x, int y) override;
private:
	void InitShaders();
	void RotateCamera(double xAngleRadians, double yAngleRadians);

private:
	CProgram m_program;
	CShader m_vertexShader;
	CAnimationController m_animationController;

	static constexpr double DISTANCE_TO_ORIGIN = 2.0;
	bool m_leftButtonPressed = false;
	glm::dvec2 m_mousePos = {};
	glm::dmat4x4 m_cameraMatrix = glm::lookAt(
		glm::dvec3{ 0.0, 0.0, DISTANCE_TO_ORIGIN },// Положение глаза наблюдателя
		glm::dvec3{ 0.0, 0.0, 0.0 },// Точка, в которую направлена камера
		glm::dvec3{ 0.0, 1.0, 0.0 });// Вектор, служащий для определения вектора "вверх"

	float m_phase = 0;
};