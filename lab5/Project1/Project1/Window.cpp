#include "pch.h"
#include "Window.h"
#include "Cottage.h"
#include "DirectLight.h"

namespace
{
	// Угол обзора по вертикали
	constexpr double FIELD_OF_VIEW = 60 * M_PI / 180.0;

	constexpr double Z_NEAR = 0.1;
	constexpr double Z_FAR = 15;

	// Ортонормируем матрицу 4*4 (это должна быть аффинная матрица)
	glm::dmat4x4 Orthonormalize(const glm::dmat4x4& m)
	{
		// Извлекаем подматрицу 3*3 из матрицы m и ортонормируем её
		const auto normalizedMatrix = glm::orthonormalize(glm::dmat3x3{ m });
		// Заменяем 3 столбца исходной матрицы
		return {
			glm::dvec4{ normalizedMatrix[0], 0.0 },
			glm::dvec4{ normalizedMatrix[1], 0.0 },
			glm::dvec4{ normalizedMatrix[2], 0.0 },
			m[3]
		};
	}

} // namespace

glm::vec4 ColorToVector(int color, float alpha)
{
	auto const red = static_cast<float>((color >> 16) & 0xff) / 255.0f;
	auto const green = static_cast<float>((color >> 8) & 0xff) / 255.0f;
	auto const blue = static_cast<float>(color & 0xff) / 255.0f;

	return { red, green, blue, alpha };
}


Window::Window(int w, int h, char const* title)
	: BaseWindow(w, h, title)
{
}


void Window::OnMouseButton(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		m_leftButtonPressed = (action & GLFW_PRESS) != 0;
	}
}

void Window::OnMouseMove(double x, double y)
{
	const glm::dvec2 mousePos{ x, y };
	if (m_leftButtonPressed)
	{
		const auto windowSize = GetFramebufferSize();

		auto const mouseDelta = mousePos - m_mousePos;
		const double xAngle = mouseDelta.y * M_PI / windowSize.y;
		const double yAngle = mouseDelta.x * M_PI / windowSize.x;
		RotateCamera(xAngle, yAngle);
	}
	m_mousePos = mousePos;
}

void Window::RotateCamera(double xAngleRadians, double yAngleRadians)
{
	// Извлекаем из 1 и 2 строки матрицы камеры направления осей вращения,
	// совпадающих с экранными осями X и Y.
	// Строго говоря, для этого надо извлекать столбцы их обратной матрицы камеры, но так как
	// матрица камеры ортонормированная, достаточно транспонировать её подматрицу 3*3
	const glm::dvec3 xAxis{
		m_cameraMatrix[0][0], m_cameraMatrix[1][0], m_cameraMatrix[2][0]
	};
	const glm::dvec3 yAxis{
		m_cameraMatrix[0][1], m_cameraMatrix[1][1], m_cameraMatrix[2][1]
	};
	m_cameraMatrix = glm::rotate(m_cameraMatrix, xAngleRadians, xAxis);
	m_cameraMatrix = glm::rotate(m_cameraMatrix, yAngleRadians, yAxis);

	m_cameraMatrix = Orthonormalize(m_cameraMatrix);
}

void Window::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	// Вычисляем соотношение сторон клиентской области окна
	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	const auto proj = glm::perspective(FIELD_OF_VIEW, aspect, Z_NEAR, Z_FAR);
	glLoadMatrixd(&proj[0][0]);
	glMatrixMode(GL_MODELVIEW);
}

void Window::SetupFog()
{
	// Включаем либо выключаем туман
	if (m_isFogEnabled)
	{
		//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		const float density = 0.2f;
		glEnable(GL_FOG);
		// Задаем режим тумана
		glFogi(GL_FOG_MODE, GL_EXP);
		// Задаем цвет тумана
		float fogColor[4] = { 0.8 , 0.8, 0.8, 1 };
		glFogfv(GL_FOG_COLOR, fogColor);
		// и его плотность
		glFogf(GL_FOG_DENSITY, density);
	}
	else
	{
		glDisable(GL_FOG);
	}
}

void Window::OnKeyboard(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F && action == 1)
	{
		m_isFogEnabled = !m_isFogEnabled;
	}
}

void Window::OnRunStart()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Включаем режим отбраковки граней
	glEnable(GL_CULL_FACE);
	// Отбраковываться будут нелицевые стороны граней
	glCullFace(GL_BACK);
	// Сторона примитива считается лицевой, если при ее рисовании
	// обход верших осуществляется против часовой стрелки
	glFrontFace(GL_CCW);

	// Включаем тест глубины для удаления невидимых линий и поверхностей
	glEnable(GL_DEPTH_TEST);


	// Направление на источник света (совпадает с позицией наблюдателя)
	DirectLight light{ { 0.0f, 0.0f, 1.0f } };
	light.SetDiffuseIntensity({ 0.8f, 0.8f, 0.8f, 1.0f });
	light.SetAmbientIntensity({ 0.2f, 0.2f, 0.2f, 1.0f });
	light.SetSpecularIntensity({ 0.5f, 0.5f, 0.5f, 1.0f });
	light.Apply(GL_LIGHT0);
}


void Window::Draw(int width, int height)
{
	glClearColor(0.4, 0.4, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetupCameraMatrix();
	SetupFog();
	m_scene.Draw();

}

void Window::SetupCameraMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(&m_cameraMatrix[0][0]);
}