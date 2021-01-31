#pragma once
#include "JaxObject.h"
#include "JaxBind.h"

namespace Jax
{
	class JaxStream;
	class JAXGRAPHIC_API JaxVertexFormat :public JaxBind
	{
		DECLARE_RTTI
		DECLARE_INITIAL

	public:
		JaxVertexFormat();
		virtual ~JaxVertexFormat();

		enum
		{
			VF_POSITION,
			VF_TEXCOORD,
			VF_NORMAL,
			VF_TANGENT,
			VF_BINORMAL,
			VF_PSIZE,
			VF_COLOR,
			VF_FOG,
			VF_DEPTH,
			VF_BLENDWEIGHT,
			VF_BLENDINDICES,
			VF_MAX
		};

		struct VERTEXFORMAT_TYPE
		{
			VERTEXFORMAT_TYPE() :offset(0), dataType(0), semantices(0), semanticesIndex(0) {}
			~VERTEXFORMAT_TYPE() {}
			UINT offset;
			UINT dataType;
			UINT semantices;
			UINT semanticesIndex;
		};

	public:
		friend class JaxRenderer;
		friend class JaxResourceManager;

		JaxArray<JaxVertexFormat::VERTEXFORMAT_TYPE> m_FormatArray;

		FORCEINLINE size_t GetVertexFormatCode() const
		{
			return m_uiVertexFormatCode;
		}

	protected:
		virtual bool OnLoadResource(JaxResourceIdentifier*& id);
		virtual bool OnReleaseResource(JaxResourceIdentifier* id);

		size_t m_uiVertexFormatCode;

	};

	DECLARE_PTR(JaxVertexFormat);
	JAXTYPE_MARCO(JaxVertexFormat);
}