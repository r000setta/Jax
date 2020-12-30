#pragma once
#include "JaxSystem.h"
#include <mmsystem.h>

namespace Jax
{
	class JAXCORE_API JaxTimer
	{
	private:
		bool m_bUseLargeTime;
		__int64 m_i64OneSecondTicks;
		__int64 m_i64TimeTickStartCounts;
		unsigned int m_ulTimeStart;
		int m_iFrameCount;
		double m_fFPS;
		double m_fTime, m_fLastFPSTime, m_fTimeSlice;
		double m_fDetTime, m_fLastTime;
		void InitGameTime();
	public:
		JaxTimer();
		~JaxTimer();

		double GetGamePlayTime();
		void UpdateFPS();
		FORCEINLINE double GetFPS() { return m_fFPS; }
		static JaxTimer* sm_pTimer;
		double GetDetTime() { return m_fDetTime; }
		int GetRandSeed();
	};
}