#pragma once
#include "JaxObject.h"
#include "JaxBind.h"
#include "JaxDataBuffer.h"
#include "JaxMain.h"
#include "JaxVertexFormat.h"

namespace Jax
{
	class Stream;
	class JAXGRAPHIC_API JaxVertexBuffer :public JaxBind
	{
		DECLARE_RTTI
		DECLARE_INITIAL

	public:
		friend class JaxVertexFormat;
		friend class JaxResourceManager;
		JaxVertexBuffer(bool bIsStatic);
		JaxVertexBuffer(JaxArray<JaxVertexFormat::VERTEXFORMAT_TYPE>& format, size_t num);
		virtual ~JaxVertexBuffer();
		bool SetData(JaxDataBuffer* data, size_t vf);
		FORCEINLINE JaxDataBuffer* GetData(size_t vf, size_t level) const
		{
			if (vf >= JaxVertexFormat::VF_MAX)
				return nullptr;
			if (level >= m_pData[vf].GetNum())
				return nullptr;
			return m_pData[vf][level];
		}
		FORCEINLINE size_t GetLevel(size_t vf) const
		{
			if (vf >= JaxVertexFormat::VF_MAX)
				return 0;
			else
				return GetSemanticsNum(vf);
		}
		FORCEINLINE JaxDataBuffer* GetPositionData(size_t level) const
		{
			if (level < m_pData[JaxVertexFormat::VF_POSITION].GetNum())
				return m_pData[JaxVertexFormat::VF_POSITION][level];
			else
				return nullptr;
		}
		FORCEINLINE JaxDataBuffer* GetNormalData(size_t level) const
		{
			if (level < m_pData[JaxVertexFormat::VF_NORMAL].GetNum())
				return m_pData[JaxVertexFormat::VF_NORMAL][level];
			else
				return nullptr;
		}
		FORCEINLINE JaxDataBuffer* GetPSizeData() const
		{
			if (m_pData[JaxVertexFormat::VF_PSIZE].GetNum())
				return m_pData[JaxVertexFormat::VF_PSIZE][0];
			else
				return nullptr;
		}
		FORCEINLINE JaxDataBuffer* GetColorData(size_t level) const
		{
			if (level < m_pData[JaxVertexFormat::VF_COLOR].GetNum())
				return m_pData[JaxVertexFormat::VF_COLOR][level];
			else
				return nullptr;
		}
		FORCEINLINE JaxDataBuffer* GetBlendWeightData() const
		{
			if (m_pData[JaxVertexFormat::VF_BLENDWEIGHT].GetNum())
				return m_pData[JaxVertexFormat::VF_BLENDWEIGHT][0];
			else
				return nullptr;
		}
		FORCEINLINE JaxDataBuffer* GetBlendIndicesData() const
		{
			if (m_pData[JaxVertexFormat::VF_BLENDINDICES].GetNum())
				return m_pData[JaxVertexFormat::VF_BLENDINDICES][0];
			else
				return nullptr;
		}
		FORCEINLINE JaxDataBuffer* GetTangentData() const
		{
			if (m_pData[JaxVertexFormat::VF_TANGENT].GetNum())
				return m_pData[JaxVertexFormat::VF_TANGENT][0];
			else
				return nullptr;
		}
		FORCEINLINE JaxDataBuffer* GetBinormalData() const
		{
			if (m_pData[JaxVertexFormat::VF_BINORMAL].GetNum())
				return m_pData[JaxVertexFormat::VF_BINORMAL][0];
			else
				return nullptr;
		}
		FORCEINLINE JaxDataBuffer* GetFogData() const
		{
			if (m_pData[JaxVertexFormat::VF_FOG].GetNum())
				return m_pData[JaxVertexFormat::VF_FOG][0];
			else
				return nullptr;
		}
		FORCEINLINE JaxDataBuffer* GetDepthData() const
		{
			if (m_pData[JaxVertexFormat::VF_BLENDWEIGHT].GetNum())
				return m_pData[JaxVertexFormat::VF_BLENDWEIGHT][0];
			else
				return nullptr;
		}
		FORCEINLINE JaxDataBuffer* GetTexCoordData(size_t level) const
		{
			if (level < m_pData[JaxVertexFormat::VF_TEXCOORD].GetNum())
				return m_pData[JaxVertexFormat::VF_TEXCOORD][level];
			else
				return nullptr;
		}
		FORCEINLINE size_t GetPositionLevel() const
		{
			return GetSemanticsNum(JaxVertexFormat::VF_POSITION);
		}
		FORCEINLINE size_t GetColorLevel() const
		{
			return GetSemanticsNum(JaxVertexFormat::VF_COLOR);
		}
		FORCEINLINE size_t GetNormalLevel() const
		{
			return GetSemanticsNum(JaxVertexFormat::VF_NORMAL);
		}
		FORCEINLINE size_t GetTexCoordLevel() const
		{
			return GetSemanticsNum(JaxVertexFormat::VF_TEXCOORD);
		}
		FORCEINLINE size_t GetVertexNum() const
		{
			return m_uiVertexNum;
		}

		bool GetVertexFormat(JaxArray<JaxVertexFormat::VERTEXFORMAT_TYPE>& format);
		FORCEINLINE JaxVertexFormat* GetVertexFormat() const
		{
			return m_pVertexFormat;
		}

		size_t GetSemanticsNum(size_t semantics) const;

	protected:
		friend class JaxVertexFormat;
		friend class JaxGeometry;
		JaxVertexBuffer();
		JaxArray<JaxDataBufferPtr> m_pData[JaxVertexFormat::VF_MAX];
		size_t m_uiVertexNum;
		size_t m_uiOneVertexSize;

		JaxVertexFormatPtr m_pVertexFormat;
		void* m_pLockData;

		virtual bool OnLoadResource(JaxResourceIdentifier*& id);
		virtual bool OnReleaseResource(JaxResourceIdentifier* id);

	public:
		virtual bool LoadResource(JaxRenderer* render);
		void* Lock();
		void Unlock();
		FORCEINLINE void* GetLockDataPtr() const
		{
			return m_pLockData;
		}

		virtual void ClearInfo();
	};

	DECLARE_PTR(JaxVertexBuffer);
	JAXTYPE_MARCO(JaxVertexBuffer);
}