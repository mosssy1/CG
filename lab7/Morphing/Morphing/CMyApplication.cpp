#include "pch.h"
#include "CMyApplication.h"
#include "ProgramLinker.h"
#include "Scene.h"
#include "ShaderCompiler.h"
#include "ShaderLoader.h"
#include "../../glm/glm/gtx/orthonormalize.hpp"

namespace
{
	constexpr float ANIMATION_PERIOD = 2.0f;
	
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
}

CMyApplication::CMyApplication(const char* title, int width, int height, int argc, char* argv[])
	: CGLApplication(title, argc, argv, width, height)
{
}

void CMyApplication::OnInit()
{
	InitShaders();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GLint phaseLocation = m_program.GetUniformLocation("phase");
}

void CMyApplication::OnIdle()
{
	m_animationController.Tick();

	float delta = m_animationController.GetTimeDelta() * 0.0005f;
	m_phase += delta;
	//Сделать по синусу
	//m_phase = 1;
	m_phase = fmodf(
		float(m_phase + delta * 2 * M_PI / ANIMATION_PERIOD),
		float(2 * M_PI)
	);

	PostRedisplay();
}

void CMyApplication::InitShaders()
{
	if (!GLEW_EXT_geometry_shader4)
	{
		throw std::runtime_error("The OpenGL implementation does not support geometry shaders");
	}

	ShaderLoader loader;
	m_vertexShader = loader.LoadShader(GL_VERTEX_SHADER, L"shaders\\vertex_shader.vsh");

	m_program.Create();
	m_program.AttachShader(m_vertexShader);

	ShaderCompiler compiler;
	compiler.CompileShader(m_vertexShader);
	compiler.CheckStatus();

	ProgramLinker linker;
	linker.LinkProgram(m_program);
	linker.CheckStatus();
}

void CMyApplication::OnDisplay()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(glm::value_ptr(m_cameraMatrix));

	glUseProgram(m_program);
	glUniform1f(m_program.GetUniformLocation("phase"), ((sinf(m_phase) + 1) / 2 ));

	glPushMatrix();
	glScalef(0.3f, 0.3f, 0.3f);
	Scene::Draw();
	glPopMatrix();

	glUseProgram(0);
}

void CMyApplication::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const auto aspectRatio = static_cast<float>(width) / static_cast<float>(height) * 0.7;
	gluOrtho2D(-aspectRatio, aspectRatio, -1.0f, 1.0f);
	const auto proj = glm::perspective(FIELD_OF_VIEW, aspectRatio, Z_NEAR, Z_FAR);
	glLoadMatrixd(&proj[0][0]);
	glMatrixMode(GL_MODELVIEW);
}

void CMyApplication::OnMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		m_leftButtonPressed = (state == GLUT_DOWN);
	}
	m_mousePos = glm::dvec2(x, y);
}

void CMyApplication::OnMotion(int x, int y)
{
	const glm::dvec2 mousePos{ x, y };
	if (m_leftButtonPressed)
	{
		int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
		int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
		auto const windowSize = glm::dvec2(windowWidth, windowHeight);;

		auto const mouseDelta = mousePos - m_mousePos;
		double const xAngle = mouseDelta.y * std::numbers::pi / windowSize.y;
		double const yAngle = mouseDelta.x * std::numbers::pi / windowSize.x;
		RotateCamera(xAngle, yAngle);

	}
	m_mousePos = mousePos;
}

void CMyApplication::RotateCamera(double xAngleRadians, double yAngleRadians)
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