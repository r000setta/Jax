#include "JaxString.h"

namespace Jax
{
	JaxString JaxString::sm_StringNULL;
	TCHAR JaxString::tmpBuffer[BUFFER_SIZE] = { 0 };
	JaxString::JaxString()
	{
		m_pBuffer = NULL;
		m_pBuffer = JAX_NEW TCHAR[1];
		JAX_ASSERT(m_pBuffer);
		m_pBuffer[0] = _T('\0');
	}

	JaxString::JaxString(const TCHAR* String)
	{
		JAX_ASSERT(String);
		m_pBuffer = NULL;
		if (String)
		{
			size_t length = JaxStrlen(String);
			m_pBuffer = JAX_NEW TCHAR[length + 1];
			JAX_ASSERT(m_pBuffer);
			JaxStrCopy(m_pBuffer, length + 1, String);
		}
		else
		{
			m_pBuffer = JAX_NEW TCHAR[1];
			JAX_ASSERT(m_pBuffer);
			m_pBuffer[0] = _T('\0');
		}
	}

	JaxString::JaxString(const JaxString& String)
	{
		m_pBuffer = NULL;
		size_t length = String.GetLength();
		m_pBuffer = JAX_NEW TCHAR[length + 1];
		JAX_ASSERT(m_pBuffer);
		JaxStrCopy(m_pBuffer, length + 1, String.GetBuffer());
	}

	JaxString::~JaxString()
	{
		JAXMAC_DELETEA(m_pBuffer);
	}


	void JaxString::SetTCHARBufferNum(size_t length)
	{
		JAXMAC_DELETEA(m_pBuffer);
		m_pBuffer = JAX_NEW TCHAR[length + 1];
		m_pBuffer[length] = _T('\0');
	}

	void JaxString::Clear()
	{
		JAXMAC_DELETEA(m_pBuffer);
		m_pBuffer = JAX_NEW TCHAR[1];
		JAX_ASSERT(m_pBuffer);
		m_pBuffer[0] = _T('\0');
	}

	JaxString& JaxString::operator=(const JaxString& String)
	{
		JAXMAC_DELETEA(m_pBuffer);
		size_t length = String.GetLength();
		m_pBuffer = JAX_NEW TCHAR[length + 1];
		JAX_ASSERT(m_pBuffer);
		JaxStrCopy(m_pBuffer, length + 1, String.GetBuffer());
		return *this;
	}

	JaxString& JaxString::operator=(const TCHAR* String)
	{
		JAX_ASSERT(String);
		JAXMAC_DELETEA(m_pBuffer);
		if (String)
		{
			size_t length = JaxStrlen(String);
			m_pBuffer = JAX_NEW TCHAR[length + 1];
			JAX_ASSERT(m_pBuffer);
			JaxStrCopy(m_pBuffer, length + 1, String);
		}
		else
		{
			JaxString();
		}
		return *this;
	}

	TCHAR& JaxString::operator[](size_t i)
	{
		JAX_ASSERT(i >= 0 && i < GetLength());
		return m_pBuffer[i];
	}

	const JaxString& JaxString::operator+=(const JaxString& String)
	{
		size_t len1 = GetLength();
		size_t len2 = String.GetLength();
		if (!len1)
		{
			*this = String;
			return *this;
		}
		else if (!len2)
		{
			return *this;
		}
		else
		{
			TCHAR* pBuffer = NULL;
			size_t len = len1 + len2 + 1;
			pBuffer = JAX_NEW TCHAR[len];
			JAX_ASSERT(pBuffer);
			JaxStrCopy(pBuffer, len, GetBuffer());
			JaxStrcat(pBuffer, len, String.GetBuffer());

			JAXMAC_DELETEA(m_pBuffer);
			m_pBuffer = pBuffer;
			return *this;
		}
	}

	bool JaxString::GetString(const JaxString& string, size_t find, bool isFront, bool isHaveFind)
	{
		if (find >= string.GetLength())
		{
			return false;
		}
		size_t length = 0;
		size_t idx = 0;
		if (isFront)
		{
			length = find;
			idx = 0;
		}
		else
		{
			length = string.GetLength() - find - 1;
			idx = find + 1;
		}
		if (isHaveFind)
		{
			length++;
			if (!isFront)
			{
				idx--;
			}
		}
		if (idx >= string.GetLength())
		{
			return false;
		}
		JAXMAC_DELETEA(m_pBuffer);
		m_pBuffer = JAX_NEW TCHAR[length + 1];
		JaxMemcpy(m_pBuffer, &string.m_pBuffer[idx], length, length + 1);
		m_pBuffer[length] = _T('\0');
		return true;
	}


	bool JaxString::GetString(const JaxString& string, TCHAR find, int findNum, bool isFront, bool isHaveFind)
	{
		if (findNum == 0)
		{
			return false;
		}
		size_t findNumTmp = 0;
		int idx = -1;
		for (size_t i = 0; i < string.GetLength(); ++i)
		{
			if (find == string.m_pBuffer[i])
			{
				findNumTmp++;
				idx = i;
			}
			if (findNumTmp == findNum)
			{
				break;
			}
		}
		if (idx == -1)
		{
			return false;
		}
		return GetString(string, idx, isFront, isHaveFind);
	}

	const JaxString& JaxString::operator+=(const TCHAR* String)
	{
		size_t len1 = GetLength();
		size_t len2 = 0;
		if (String)
		{
			len2 = JaxStrlen(String);
		}
		if (!len1)
		{
			*this = String;
			return *this;
		}
		else if (!len2)
		{
			return *this;
		}
		else
		{
			TCHAR* pBuffer = NULL;
			size_t len = len1 + len2 + 1;
			pBuffer = JAX_NEW TCHAR[len];
			JAX_ASSERT(pBuffer);

			JaxStrCopy(pBuffer, len, GetBuffer());
			JaxStrcat(pBuffer, len, String);

			JAXMAC_DELETEA(m_pBuffer);
			m_pBuffer = pBuffer;
			return *this;
		}
	}


	JaxString operator+(const JaxString& String1, const JaxString& String2)
	{
		size_t len1 = String1.GetLength();
		size_t len2 = String2.GetLength();
		if (!len2)
		{
			return String1;
		}
		else if (!len1)
		{
			return String2;
		}
		else
		{
			TCHAR* pBuffer = NULL;
			size_t len = len1 + len2 + 1;
			pBuffer = JAX_NEW TCHAR[len];
			JAX_ASSERT(pBuffer);
			JaxStrCopy(pBuffer, len, String1.GetBuffer());
			JaxStrcat(pBuffer, len, String2.GetBuffer());
			JaxString res(pBuffer);
			JAXMAC_DELETEA(pBuffer);
			return res;
		}
	}

	JaxString operator+(const JaxString& String1, const TCHAR* String2)
	{
		JAX_ASSERT(String2);
		size_t len1 = String1.GetLength();
		size_t len2 = 0;
		if (String2)
		{
			len2 = JaxStrlen(String2);
		}
		if (!len2)
		{
			return String1;
		}
		else if (!len1)
		{
			return JaxString(String2);
		}
		else
		{
			TCHAR* pBuffer = NULL;
			size_t len = len1 + len2 + 1;
			pBuffer = JAX_NEW TCHAR[len];
			JAX_ASSERT(pBuffer);

			JaxStrCopy(pBuffer, len, String1.GetBuffer());
			JaxStrcat(pBuffer, len, String2);
			JaxString res(pBuffer);
			JAXMAC_DELETEA(pBuffer);
			return res;
		}
	}

	JaxString operator+(const TCHAR* String1, const JaxString& String2)
	{
		JAX_ASSERT(String1);
		size_t len1 = 0;
		size_t len2 = String2.GetLength();
		if (String1)
		{
			len1 = JaxStrlen(String1);
		}
		if (!len1)
		{
			return String2;
		}
		else if (!len2)
		{
			return JaxString(String1);
		}
		else
		{
			TCHAR* pBuffer = NULL;
			size_t len = len1 + len2 + 1;
			pBuffer = JAX_NEW TCHAR[len];
			JAX_ASSERT(pBuffer);

			JaxStrCopy(pBuffer, len, String1);
			JaxStrcat(pBuffer, len, String2.GetBuffer());
			JaxString res(pBuffer);
			JAXMAC_DELETEA(pBuffer);
			return res;
		}
	}

	int CompareString(const JaxString& String1, const JaxString& String2)
	{
		return JaxStrCmp(String1.GetBuffer(), String2.GetBuffer());
	}

	int CompareString(const JaxString& String1, const TCHAR* String2)
	{
		return JaxStrCmp(String1.GetBuffer(), String2);
	}

	int CompareString(const TCHAR* String1, const JaxString& String2)
	{
		return JaxStrCmp(String1, String2.GetBuffer());
	}

	bool operator==(const JaxString& String1, const JaxString& String2)
	{
		return JaxStrCmp(String1.GetBuffer(), String2.GetBuffer());
	}

	bool operator==(const JaxString& String1, const TCHAR* String2)
	{
		return JaxStrCmp(String1.GetBuffer(), String2);
	}

	bool operator==(const TCHAR* String1, const JaxString& String2)
	{
		return JaxStrCmp(String1, String2.GetBuffer());
	}

	bool operator!=(const JaxString& String1, const JaxString& String2)
	{
		return JaxStrCmp(String1.GetBuffer(), String2.GetBuffer()) == 0;
	}

	bool operator!=(const JaxString& String1, const TCHAR* String2)
	{
		return JaxStrCmp(String1.GetBuffer(), String2) == 0;
	}

	bool operator!=(const TCHAR* String1, const JaxString& String2)
	{
		return JaxStrCmp(String1, String2.GetBuffer()) == 0;
	}

	int StringToInt(const JaxString& String)
	{
		int i = 0;
		JaxScanf(String.GetBuffer(), _T("%d"), (va_list)&i);
		return i;
	}

	JAXREAL StringToReal(const JaxString& String)
	{
		JAXREAL f = 0.0f;
		_stscanf_s(String.GetBuffer(), _T("%f"), &f);
		return f;
	}

	
}
