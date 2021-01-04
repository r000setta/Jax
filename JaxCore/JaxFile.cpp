#include "JaxFile.h"

namespace Jax
{
	TCHAR JaxFile::sm_openMode[OM_MAX][5] =
	{
		_T("rb"),
		_T("wb"),
		_T("rt"),
		_T("wt"),
	};

	size_t JaxFile::m_uiSeekFlag[] =
	{
		SEEK_CUR,
		SEEK_END,
		SEEK_SET
	};

	JaxFile::JaxFile() :m_pFileHandle(NULL),
		m_uiOpenMode(0), m_uiFileSize(0) {}

	JaxFile::~JaxFile()
	{
		if (m_pFileHandle)
		{
			fclose(m_pFileHandle);
			m_pFileHandle = NULL;
		}
	}

	bool JaxFile::Flush()
	{
		return fflush(m_pFileHandle) == 0;
	}

	bool JaxFile::Seek(size_t offset, size_t origin)
	{
		if (!m_pFileHandle)
		{
			return false;
		}
		fseek(m_pFileHandle, offset, origin);
		return true;
	}

	bool JaxFile::Open(const TCHAR* fileName, size_t openMode)
	{
		if (m_pFileHandle)
		{
			fclose(m_pFileHandle);
		}
		if (!fileName || openMode >= OM_MAX)
		{
			return false;
		}

		size_t len = JaxStrlen(fileName);
		if (len < JAX_MAXPATH - 1)
		{
			if (!JaxMemcpy(m_fileName, fileName, len + 1))
			{
				return false;
			}
		}
		else
		{
			return false;
		}

		m_uiOpenMode = openMode;
		if (m_uiOpenMode == OM_RB || m_uiOpenMode == OM_RT)
		{
			struct _stat64i32 stat;
			if (_tstat(fileName, &stat) != 0)
			{
				return false;
			}
			m_uiFileSize = stat.st_size;
		}

		errno_t error = _tfopen_s(&m_pFileHandle, fileName, sm_openMode[m_uiOpenMode]);
		if (error)
		{
			return false;
		}
		if (!m_pFileHandle)
		{
			return false;
		}

		return true;
	}

	bool JaxFile::Write(const void* pBuffer, size_t size, size_t count)
	{
		if (!m_pFileHandle)
		{
			return false;
		}

		if (!pBuffer || !size || !count)
		{
			return false;
		}

		fwrite(pBuffer, size, count, m_pFileHandle);
		return true;
	}

	bool JaxFile::Read(void* pBuffer, size_t size, size_t count)
	{
		if (!m_pFileHandle)
		{
			return false;
		}

		if (!pBuffer || !size || !count)
		{
			return false;
		}

		fread(pBuffer, size, count, m_pFileHandle);
		return true;
	}

	bool JaxFile::GetLine(void* pBuffer, size_t size)
	{
		if (!m_pFileHandle)
		{
			return false;
		}

		if (!pBuffer || !size)
		{
			return false;
		}

		if (!_fgetts((TCHAR*)pBuffer, size, m_pFileHandle))
		{
			return false;
		}
		return true;
	}
}
