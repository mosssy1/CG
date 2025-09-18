// 01_raytrace_baseView.h : interface of the CMy01_raytrace_baseView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "IGeometryObject_fwd.h"
#include "RenderContext.h"
#include "Renderer.h"
#include "Scene.h"
#include "SimpleLightShader.h"

class CFrameBuffer;

class CSimpleDiffuseShader;
class CSphere;
class CCheckerShader;
class CSimpleMaterial;
class IShader;
class CTriangleMeshData;
struct Vertex;
struct Face;

class CRaytraceView : public CWindowImpl<CRaytraceView>
{
	enum
	{
		FRAMEBUFFER_UPDATE_TIMER = 1
	};

public:
	CRaytraceView();
	~CRaytraceView();
	DECLARE_WND_CLASS(NULL)

	void SetStatusBar(HWND statusBar);

	BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_MSG_MAP(CRaytraceView)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	END_MSG_MAP()

private:
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	void AddSomePlane();
	void AddSomeSpheres();
	void AddSomeLight();
	void AddSomeTetrahedron();
	void AddCube(float size = 1.0f);
	void AddTorusPyromid();

	void DrawFrameBuffer(CDC& dc, int x, int y);
	bool UpdateFrameBuffer();

	// Методы создания и добавления шейдеров в коллекцию m_shaders
	//CSimpleLightShader& CreateSimpleLightShader(CSimpleMaterial const& material);
	CSimpleLightShader& CreateSimpleLightShader(CSimpleMaterial const& material);
	CCheckerShader& CreateCheckerShader(CMatrix4d const& textureTransform);

	// Методы, создающие и добавляющие объекты к сцене
	CSceneObject& AddSphere(IShader const& shader, double radius = 1, CVector3d const& center = CVector3d(), CMatrix4d const& transform = CMatrix4d());
	CSceneObject& AddTorus(IShader const& shader, double bigRadius = 2, double smallRadius = 1, CVector3d const& center = CVector3d(), CMatrix4d const& transform = CMatrix4d());
	CSceneObject& AddPlane(IShader const& shader, double a, double b, double c, double d, CMatrix4d const& transform = CMatrix4d());
	CSceneObject& AddSceneObject(IGeometryObject const& object, IShader const& shader);
	CSceneObject& AddTriangleMesh(IShader const& shader, CTriangleMeshData const* pMeshData, CMatrix4d const& transform = CMatrix4d());
	CTriangleMeshData* CreateTriangleMeshData(std::vector<Vertex> const& vertices, std::vector<Face> const& faces);

private:
	CStatusBarCtrl m_statusBar;
	CRenderContext m_context;
	CRenderer m_renderer;
	CScene m_scene;
	CMatrix4d m_modelViewMatrix;


	std::unique_ptr<CFrameBuffer> m_pFrameBuffer;

	std::vector<std::unique_ptr<CTriangleMeshData>> m_triangleMeshDataObjects;
	std::vector<std::unique_ptr<IGeometryObject>> m_geometryObjects;
	std::vector<std::unique_ptr<IShader>> m_shaders;
};
