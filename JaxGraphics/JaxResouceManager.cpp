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