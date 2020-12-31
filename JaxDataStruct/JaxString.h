#pragma once
#include "JaxContainer.h"
#include "JaxMath.h"

namespace Jax
{
	class JAXDATASTRUCT_API JaxString
	{
	public:
		enum
		{
			BUFFER_SIZE = 2048
		};
		JaxString();
		JaxString(const TCHAR* String);
		JaxString(const JaxString& String);
		~JaxString();

		static JaxString sm_StringNULL;
		static TCHAR tmpBuffer[BUFFER_SIZE];

		FORCEINLINE TCHAR* GetBuffer() const
		{
			return m_pBuffer;
		}
		FORCEINLINE size_t GetLength() const
		{
			return JaxStrlen(m_pBuffer);
		}
		void SetTCHARBufferNum(size_t length);
		void Clear();
		
		JaxString& operator=(const JaxString& String);
		JaxString& operator=(const TCHAR* String);

		TCHAR& operator[](size_t i);

		const JaxString& operator+=(const JaxString& String);
		const JaxString& operator+=(const TCHAR* String);

		bool GetString(const JaxString& string, size_t find, bool isFront = true, bool isHaveFind = false);
		bool GetString(const JaxString& string, TCHAR find, int findNum, bool isFront = true, bool isHaveFind = false);
	protected:
		TCHAR* m_pBuffer;
	};

	JAXDATASTRUCT_API JaxString operator+(const JaxString& String1, const JaxString& String2);
	JAXDATASTRUCT_API JaxString operator+(const JaxString& String1, const TCHAR* String2);
	JAXDATASTRUCT_API JaxString operator+(const TCHAR* String1, const JaxString& String2);

	JAXDATASTRUCT_API int CompareString(const JaxString& String1, const JaxString& String2);
	JAXDATASTRUCT_API int CompareString(const JaxString& String1, const TCHAR* String2);
	JAXDATASTRUCT_API int CompareString(const TCHAR* String1, const JaxString& String2);

	JAXDATASTRUCT_API bool operator==(const JaxString& String1, const JaxString& String2);
	JAXDATASTRUCT_API bool operator==(const JaxString& String1, const TCHAR* String2);
	JAXDATASTRUCT_API bool operator==(const TCHAR* String1, const JaxString& String2);

	JAXDATASTRUCT_API bool operator!=(const JaxString& String1, const JaxString& String2);
	JAXDATASTRUCT_API bool operator!=(const JaxString& String1, const TCHAR* String2);
	JAXDATASTRUCT_API bool operator!=(const TCHAR* String1, const JaxString& String2);

	JAXDATASTRUCT_API int StringToInt(const JaxString& String);
	JAXDATASTRUCT_API JAXREAL StringToReal(const JaxString& String);
}