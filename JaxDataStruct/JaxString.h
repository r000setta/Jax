#pragma once
#include "JaxContainer.h"
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
}