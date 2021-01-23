#include "JaxRenderer.h"

namespace Jax
{
	JaxRenderer* JaxRenderer::sm_pRenderer = NULL;

	JaxRenderer::JaxRenderer()
	{
		m_pChildWindowInfo = NULL;
		m_ClearColor.Set(1.0f, 1.0f, 1.0f, 1.0f);
		m_fClearDepth = 1.0f;
		m_uiClearStencil = 0;

		m_iNumChildWindow = 0;
		m_iCurWindowID = -1;
		m_bIsRendering = false;
	}

}
