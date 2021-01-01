#pragma once
#include "JaxArray.h"
#include "JaxGraphic.h"

namespace Jax
{
#define DECLARE_PRIORITY \
public: \
static JaxPriority sm_Priority;

#define IMPLEMENT_PRIORITY(classname) \
JaxPriority classname::sm_Priority;


	class JAXGRAPHIC_API JaxPriority
	{
	public:
		JaxPriority();
		JaxPriority(size_t priorityNum);
		~JaxPriority();

		size_t GetPriorityNum();

		JaxPriority& operator=(JaxPriority& r);
		bool operator==(JaxPriority& r);
		bool operator!=(JaxPriority& r);
		bool operator>(JaxPriority& r);
		bool operator<(JaxPriority& r);
		bool operator>=(JaxPriority& r);
		bool operator<=(JaxPriority& r);

	private:
		bool CheckIsCircle(const JaxPriority* checked) const;
		size_t CheckPriorityNum();
		size_t m_uiPriorityNum;
		JaxArray<JaxPriority*> m_pPriorityThanList;
	};
}