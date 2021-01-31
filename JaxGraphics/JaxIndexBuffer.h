#pragma once
#include "JaxObject.h"
#include "JaxBind.h"
#include "JaxDataBuffer.h"

namespace Jax
{
	class JaxStream;
	class JAXGRAPHIC_API JaxIndexBuffer :public JaxBind
	{
		DECLARE_RTTI
		DECLARE_INITIAL

	public:
		virtual ~JaxIndexBuffer();
		JaxIndexBuffer();
		JaxIndexBuffer(size_t num, size_t DT = JaxDataBuffer::DT_USHORT);
		bool SetData(JaxDataBuffer* pData);
	public:
		virtual void* Lock();
		virtual void UnLock();

		virtual bool LoadResource(JaxRenderer* render);
		virtual void ClearInfo();
		FORCEINLINE JaxDataBuffer* GetIndexData() const
		{
			return m_pData;
		}

		size_t GetNum() const;
		virtual size_t GetByteSize() const;
		FORCEINLINE void* GetLockDataPtr() const
		{
			return m_pLockData;
		}

		FORCEINLINE size_t GetDataType() const
		{
			return m_uiDT;
		}

	protected:
		virtual bool OnLoadResource(JaxResourceIdentifier*& id);
		virtual bool OnReleaseResource(JaxResourceIdentifier* id);
		JaxDataBufferPtr m_pData;
		size_t m_uiNum;
		size_t m_uiDT;
		void* m_pLockData;
	};

	DECLARE_PTR(JaxIndexBuffer)
	JAXTYPE_MARCO(JaxIndexBuffer)
}