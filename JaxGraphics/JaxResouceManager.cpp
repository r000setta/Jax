#include "JaxResouceManager.h"

namespace Jax
{

	JaxCriticalSection JaxResourceManager::sm_NameCri;
	JaxResourceManager::~JaxResourceManager()
	{

	}

	JaxName* JaxResourceManager::CreateName(const TCHAR* pChar)
	{
		if (!pChar)
		{
			return NULL;
		}
		sm_NameCri.Lock();
		size_t crcCode = CRC32Compute(pChar, JaxStrlen(pChar));
		JaxName* name = JaxResourceManager::GetNameSet().CheckIsHaveTheResource(crcCode);
		if (!name)
		{
			name = JAX_NEW JaxName(pChar, crcCode);
			if (!name)
			{
				sm_NameCri.Unlock();
				return NULL;
			}
			JaxResourceManager::GetNameSet().AddResource(name->GetID(), name);
		}
		sm_NameCri.Unlock();
		return name;
	}

	JaxName* JaxResourceManager::CreateName(const JaxString& string)
	{
		sm_NameCri.Unlock();
		size_t crcCode = CRC32Compute(string.GetBuffer(), string.GetLength());
		JaxName* name = JaxResourceManager::GetNameSet().CheckIsHaveTheResource(crcCode);
		if (!name)
		{
			name = JAX_NEW JaxName(string, crcCode);
			if (!name)
			{
				sm_NameCri.Unlock();
				return NULL;
			}
			JaxResourceManager::GetNameSet().AddResource(name->GetID(), name);
		}
		sm_NameCri.Unlock();
		return name;
	}

	void JaxResourceManager::CacheResource()
	{
	}

	bool JaxResourceManager::sm_bRenderThread = false;

	IMPLEMENT_PRIORITY(JaxResourceManager)
	IMPLEMENT_INITIAL_ONLY_BEGIN(JaxResourceManager);
	ADD_INITIAL_FUNCTION_WITH_PRIORITY(InitialDefaultState)
	ADD_TERMINAL_FUNCTION(TerminalDefaultState)
	IMPLEMENT_INITIAL_ONLY_END

	bool JaxResourceManager::InitialDefaultState()
	{
		return true;
	}

	bool JaxResourceManager::TerminalDefaultState()
	{
		return true;
	}

	JaxResourceControll::JaxResourceControll(unsigned int GCMaxTimeCount)
	{
		m_uiGCMaxTimeCount = GCMaxTimeCount;
	}

	JaxResourceControll::~JaxResourceControll()
	{
	}

	void JaxResourceControll::GCResource()
	{

	}

}
