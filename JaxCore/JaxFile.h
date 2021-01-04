#pragma once
#include "JaxSystem.h"

namespace Jax
{
#define JAX_MAXPATH 256

	class JAXCORE_API JaxFile
	{
	public:
		enum
		{
			OM_RB,
			OM_WB,
			OM_RT,
			OM_WT,
			OM_MAX
		};

		enum
		{
			SF_CUR,
			SF_END,
			SF_SET,
			SF_MAX
		};

		JaxFile();
		~JaxFile();

		bool Flush();

		bool Seek(size_t offset, size_t origin);
		bool Open(const TCHAR* fileName, size_t openMode);
		bool Write(const void* pBuffer, size_t size, size_t count);
		bool Read(void* pBuffer, size_t size, size_t count);
		bool GetLine(void* pBuffer, size_t size);
		
		FORCEINLINE size_t GetFileSize()
		{
			return m_uiFileSize;
		}

	protected:
		static TCHAR sm_openMode[OM_MAX][5];
		static size_t m_uiSeekFlag[];
		FILE* m_pFileHandle;
		size_t m_uiOpenMode;
		size_t m_uiFileSize;
		TCHAR m_fileName[JAX_MAXPATH];
	};
}