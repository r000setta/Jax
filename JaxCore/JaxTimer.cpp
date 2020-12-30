#include "JaxTimer.h"

namespace Jax
{
	JaxTimer* JaxTimer::sm_pTimer = NULL;

	void JaxTimer::InitGameTime()
	{
		m_iFrameCount = 0;
		m_fFPS = 0;
		m_fTime = 0;
		m_fLastFPSTime = 0;
		m_fTimeSlice = 0;
		m_fDetTime = 0;
		if (QueryPerformanceFrequency((LARGE_INTEGER*) & m_i64OneSecondTicks))
		{
			m_bUseLargeTime = true;
			QueryPerformanceCounter((LARGE_INTEGER*)&m_i64TimeTickStartCounts);
		}
		else
		{
			m_bUseLargeTime = false;
			m_ulTimeStart = timeGetTime();
		}
	}

	JaxTimer::JaxTimer()
	{
		InitGameTime();
		sm_pTimer = this;
	}

	JaxTimer::~JaxTimer()
	{

	}

	double JaxTimer::GetGamePlayTime()
	{
		__int64 timeCurrentCounts;
		if (m_bUseLargeTime)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&timeCurrentCounts);
			return ((timeCurrentCounts - m_i64TimeTickStartCounts) * (1.0 / m_i64OneSecondTicks) * 1000.0);
		}
		else
		{
			return ((timeGetTime() - m_ulTimeStart));
		}
	}

	void JaxTimer::UpdateFPS()
	{
		m_fTime = GetGamePlayTime() * 0.001;
		m_fDetTime = m_fTime - m_fLastTime;
		m_fLastTime = m_fTime;
		if (m_fTime - m_fLastFPSTime > 1.0f)
		{
			m_fLastFPSTime = m_fTime;
			m_fFPS = m_iFrameCount;
			m_iFrameCount = 0;
		}
		else {
			m_iFrameCount++;
		}
	}

	int JaxTimer::GetRandSeed()
	{
		return ((LARGE_INTEGER*)&m_i64TimeTickStartCounts)->LowPart;
	}


}
