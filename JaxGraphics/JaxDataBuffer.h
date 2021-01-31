#pragma once
#include "JaxObject.h"

namespace Jax
{
	class JaxStream;
	class JAXGRAPHIC_API JaxDataBuffer :public JaxObject
	{
		DECLARE_RTTI
		DECLARE_INITIAL

	public:
		enum	//Date Type
		{
			DT_FLOAT32_1,// 1D VSREAL expanded to (value, 0., 0., 1.)
			DT_FLOAT32_2,// 2D VSREAL expanded to (value, value, 0., 1.)
			DT_FLOAT32_3,// 3D VSREAL expanded to (value, value, value, 1.)
			DT_FLOAT32_4,// 4D VSREAL

			DT_USHORT,
			DT_UINT,

			DT_UBYTE4,	// 4D unsigned byte
			DT_UBYTE4N, // Each of 4 bytes is normalized by dividing to 255.0

			DT_SHORT2,	// 2D signed short expanded to (value, value, 0., 1.)
			DT_SHORT2N,	// 2D signed short normalized (v[0]/32767.0,v[1]/32767.0,0,1)
			DT_USHORT2N,// 2D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,0,1)

			DT_SHORT4,	// 4D signed short
			DT_SHORT4N,	// 4D signed short normalized (v[0]/32767.0,v[1]/32767.0,v[2]/32767.0,v[3]/32767.0)
			DT_USHORT4N,// 4D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,v[2]/65535.0,v[3]/65535.0)

			DT_FLOAT16_2,// Two 16-bit floating point values, expanded to (value, value, 0, 1)
			DT_FLOAT16_4,// Four 16-bit floating point values

			DT_COLOR,	// 4D packed unsigned bytes mapped to 0. to 1. range
						// Input is in D3DCOLOR format (ARGB) expanded to (R, G, B, A)
			DT_MAXNUM
		};

		virtual ~JaxDataBuffer();
		JaxDataBuffer();

	public:
		FORCEINLINE size_t GetDT() const
		{
			return m_uiDT;
		}
		FORCEINLINE size_t GetStride() const
		{
			return sm_uiDataTypeByte[m_uiDT];
		}
		FORCEINLINE size_t GetChannel() const
		{
			return sm_uiDataTypeChannel[m_uiDT];
		}
		FORCEINLINE size_t GetNum() const
		{
			return m_uiNum;
		}
		FORCEINLINE size_t GetSize() const
		{
			return GetStride() * m_uiNum;
		}

		FORCEINLINE void* GetData() const
		{
			return m_pData;
		}

		bool SetData(const void* data, size_t num, size_t DT);
		bool AddData(const void* data, size_t num, size_t DT);
		bool CreateEmptyBuffer(size_t num, size_t DT);

		static size_t sm_uiDataTypeByte[DT_MAXNUM];
		static size_t sm_uiDataTypeChannel[DT_MAXNUM];

	protected:
		size_t m_uiDT;
		size_t m_uiNum;
		byte* m_pData;
		size_t m_uiSize;
	};

	DECLARE_PTR(JaxDataBuffer);
	JAXTYPE_MARCO(JaxDataBuffer);
}