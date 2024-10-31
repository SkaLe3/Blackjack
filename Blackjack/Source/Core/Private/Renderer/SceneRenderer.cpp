#include "Renderer/SceneRenderer.h"

namespace Core
{

	SharedPtr<SceneRenderer> SceneRenderer::Create()
	{
		SharedPtr<SceneRenderer> result = MakeShared<SceneRenderer>();
		result->Init();
		return result;
	}

	SceneRenderer::~SceneRenderer()
	{
		Shutdown();
	}

	void SceneRenderer::Init()
	{

	}

}