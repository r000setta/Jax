#include "JaxInput.h"

namespace Jax
{
	JaxInput* JaxInput::sm_pInput = NULL;
	JaxInput::JaxInput():m_lX(0),m_lY(0),m_lZ(0)
	{
		JaxMemset(m_Keys, 0, sizeof(m_Keys));
		JaxMemset(m_KeysOld, 0, sizeof(m_Keys));
		JaxMemset(m_bPressed, 0, sizeof(m_bPressed));
		JaxMemset(m_bReleased, 0, sizeof(m_bReleased));

		m_Range.left = -1;
		m_Range.right = -1;
		m_Range.back = -1;
		m_Range.bottom = -1;
		m_Range.front = -1;
		m_Range.right = -1;
		m_pMsgProc = NULL;
		sm_pInput = this;
	}

	JaxInput::~JaxInput()
	{
	}

	void JaxInput::Update()
	{
		KeyBoardUpdate();
		MouseUpdate();
		if (m_pMsgProc)
		{
			for (size_t i = 0; i < BK_MAX; ++i)
			{
				if (IsKeyBoardPressed(i))
				{
					(*m_pMsgProc)(IT_KEYBOARD, IE_DOWN, i, m_lX, m_lY, m_lZ);
				}
				if (IsKeyBoardReleased(i))
				{
					(*m_pMsgProc)(IT_KEYBOARD, IE_UP, i, m_lX, m_lY, m_lZ);
				}
			}
		}

		for (size_t i = 0; i < MK_MAX; ++i)
		{
			if (IsMousePressed(i))
			{
				(*m_pMsgProc)(IT_MOUSE, IE_DOWN, i, m_lX, m_lY, m_lZ);
			}
			if (IsMouseReleased(i))
			{
				(*m_pMsgProc)(IT_MOUSE, IE_UP, i, m_lX, m_lY, m_lZ);
			}
		}
		if (m_Delta.x != 0 || m_Delta.y != 0)
		{
			(*m_pMsgProc)(IT_MOUSE, IE_MOUSE_MOVE, IE_UP, m_lX, m_lY, m_lZ);
		}
		if (m_Delta.z != 0)
		{
			(*m_pMsgProc)(IT_MOUSE, IE_WHEEL_MOVE, IE_UP, m_lX, m_lY, m_lZ);
		}
	}

	bool JaxInput::IsPressed(size_t inputType, UINT btn)
	{
		if (inputType == IT_KEYBOARD)
			return IsKeyBoardPressed(btn);
		else if (inputType == IT_MOUSE)
			return IsMousePressed(btn);
		else
			return false;
	}

	bool JaxInput::IsReleased(size_t inputType, UINT btn)
	{
		if (inputType == IT_KEYBOARD)
			return IsKeyBoardReleased(btn);
		else if (inputType == IT_MOUSE)
			return IsMouseReleased(btn);
		else
			return false;
	}
}
