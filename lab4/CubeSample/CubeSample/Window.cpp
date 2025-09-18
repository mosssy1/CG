#include "pch.h"
#include "Window.h"
#include "DirectLight.h"

namespace
{
	// ���� ������ �� ���������
	constexpr double FIELD_OF_VIEW = 60 * M_PI / 180.0;

	constexpr double Z_NEAR = 0.1;
	constexpr double Z_FAR = 10;

	// ������������� ������� 4*4 (��� ������ ���� �������� �������)
	glm::dmat4x4 Orthonormalize(const glm::dmat4x4& m)
	{
		// ��������� ���������� 3*3 �� ������� m � ������������� �
		const auto normalizedMatrix = glm::orthonormalize(glm::dmat3x3{ m });
		// �������� 3 ������� �������� �������
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


Window::Window(int w, int h, const char* title)
	: BaseWindow(w, h, title)
{
	m_dodecahedron.SetSideColor(0, ColorToVector(0xF8B117, ALPHA));
	m_dodecahedron.SetSideColor(1, ColorToVector(0xFD3866, ALPHA));
	m_dodecahedron.SetSideColor(2, ColorToVector(0xFF3545, ALPHA));
	m_dodecahedron.SetSideColor(3, ColorToVector(0xFF8901, ALPHA));
	m_dodecahedron.SetSideColor(4, ColorToVector(0xF4D717, ALPHA));
	m_dodecahedron.SetSideColor(5, ColorToVector(0x00BA71, ALPHA));
	m_dodecahedron.SetSideColor(6, ColorToVector(0x00C2DE, ALPHA));
	m_dodecahedron.SetSideColor(7, ColorToVector(0x5F2879, ALPHA));
	m_dodecahedron.SetSideColor(8, ColorToVector(0xFDB3A8, ALPHA));
	m_dodecahedron.SetSideColor(9, ColorToVector(0xFD3866, ALPHA));
	m_dodecahedron.SetSideColor(10, ColorToVector(0x8EB5B2, ALPHA));
	m_dodecahedron.SetSideColor(11, ColorToVector(0xDA5335, ALPHA));
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
	// ��������� �� 1 � 2 ������ ������� ������ ����������� ���� ��������,
	// ����������� � ��������� ����� X � Y.
	// ������ ������, ��� ����� ���� ��������� ������� �� �������� ������� ������, �� ��� ���
	// ������� ������ �����������������, ���������� ��������������� � ���������� 3*3
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

	// ��������� ����������� ������ ���������� ������� ����
	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	const auto proj = glm::perspective(FIELD_OF_VIEW, aspect, Z_NEAR, Z_FAR);
	glLoadMatrixd(&proj[0][0]);
	glMatrixMode(GL_MODELVIEW);
}

void Window::OnRunStart()
{
	// �������� ��������� �������� ����� �0
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// �������� ����� ���������� ������
	glEnable(GL_CULL_FACE);
	// ��������������� ����� ��������� ������� ������
	glCullFace(GL_BACK);
	// ������� ��������� ��������� �������, ���� ��� �� ���������
	// ����� ������ �������������� ������ ������� �������
	glFrontFace(GL_CCW);

	// �������� ���� ������� ��� �������� ��������� ����� � ������������, � ������ � ����� �������
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	//����� ���������� ������
	glEnable(GL_BLEND);
	//��� ������ �������������� ��������
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

	// ����������� �� �������� ����� (��������� � �������� �����������)
	DirectLight light{ { 0.0f, 0.0f, 1.0f } };
	light.SetDiffuseIntensity({ 0.8f, 0.8f, 0.8f, 1.0f });
	light.SetAmbientIntensity({ 0.2f, 0.2f, 0.2f, 1.0f });
	light.SetSpecularIntensity({ 0.5f, 0.5f, 0.5f, 1.0f });
	light.Apply(GL_LIGHT0);
}


void Window::Draw(int width, int height)
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetupCameraMatrix();

	m_dodecahedron.DrawSolidParts();

	glDepthMask(GL_FALSE);
	m_dodecahedron.DrawTransparentParts();
	glDepthMask(GL_TRUE);
}

void Window::SetupCameraMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(&m_cameraMatrix[0][0]);
}