#pragma once
#include "Paraboloid.h"
#include "BaseWindow.h"
#include "pch.h"

class Window : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;

private:
	void OnMouseButton(int button, int action, [[maybe_unused]] int mods) override;

	void OnMouseMove(double x, double y) override;

	void RotateCamera(double xAngleRadians, double yAngleRadians);

	void OnResize(int width, int height) override;

	void OnRunStart() override;

	void Draw(int width, int height) override;

	void SetupCameraMatrix();

	static constexpr float DISTANCE_TO_ORIGIN = 2;
	//static constexpr float ALPHA = 0.7f;

	bool m_leftButtonPressed = false;
	glm::dvec2 m_mousePos = {};
	glm::dmat4x4 m_cameraMatrix = glm::lookAt(
		glm::dvec3{ 0.0, 0.0, DISTANCE_TO_ORIGIN },// Положение глаза наблюдателя
		glm::dvec3{ 0.0, 0.0, 0.0 },// Точка, в которую направлена камера
		glm::dvec3{ 0.0, 1.0, 0.0 });// Вектор, служащий для определения вектора "вверх"
};