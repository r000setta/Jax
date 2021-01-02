#pragma once
#include "JaxName.h"
#include "JaxReference.h"
#include "JaxPriority.h"
#include "JaxString.h"

namespace Jax
{
	class JAXGRAPHIC_API JaxName :public JaxReference, public JaxMemObject
	{
	public:
		~JaxName();
		explicit JaxName(const TCHAR* pChar, size_t id);
		explicit JaxName(const JaxString& string, size_t id);

		FORCEINLINE const TCHAR* GetBuffer() const
		{
			return m_String.GetBuffer();
		}

		FORCEINLINE const JaxString& GetString() const
		{
			return m_String;
		}

		FORCEINLINE size_t GetLength() const
		{
			return m_String.GetLength();
		}

		FORCEINLINE size_t GetID() const
		{
			return m_uiID;
		}

	private:
		size_t m_uiID;
		JaxString m_String;
	};

	DECLARE_PTR(JaxName);

	class JaxStream;
	class JAXGRAPHIC_API JaxUsedName
	{

	};
}