#pragma once
#include "JaxSystem.h"
#include "JaxPriority.h"
#include "JaxArray.h"

namespace Jax
{
	typedef bool (*Function)();
	class JaxRtti;
	using FunctionProperty = bool(*)(JaxRtti*);
	
	class JAXGRAPHIC_API JaxMain
	{
	public:
		static void AddInitialPropertyFunction(FunctionProperty func);
		static void AddTerminalPropertyFunction(Function func);
		static void AddInitialFunction(Function func);
		static void AddInitialFunction(Function func, JaxPriority* priority);
		static bool Initialize();
		static void AddTerminalFunction(Function func);
		static void AddTerminalFunction(Function func, JaxPriority* priority);
		static bool Terminate();

	private:
		JaxMain();
		~JaxMain() {}

		struct Element
		{
			Function func;
			JaxPriority* pPriority;

			Element() :func(NULL), pPriority(NULL) {}
			Element(Function func, JaxPriority* p) :func(func), pPriority(p) {}
			~Element()
			{
				func = NULL;
				pPriority = NULL;
			}
			
			bool operator>(const Element& e) const
			{
				static JaxPriority sp1;
				static JaxPriority sp2;
				JaxPriority* p1 = pPriority ? pPriority : &sp1;
				JaxPriority* p2 = e.pPriority ? e.pPriority : &sp2;
				return (*p1) > (*p2);
			}

			bool operator<(const Element& e) const
			{
				static JaxPriority sp1;
				static JaxPriority sp2;
				JaxPriority* p1 = pPriority ? pPriority : &sp1;
				JaxPriority* p2 = e.pPriority ? e.pPriority : &sp2;
				return (*p1) < (*p2);
			}

			bool operator==(const Element& e) const
			{
				static JaxPriority sp1;
				static JaxPriority sp2;
				JaxPriority* p1 = pPriority ? pPriority : &sp1;
				JaxPriority* p2 = e.pPriority ? e.pPriority : &sp2;
				return (*p1) == (*p2);
			}
		};

		static JaxArray<Element>* sm_pInitialArray;
		static JaxArray<FunctionProperty>* sm_pInitialPropertyArray;
		static JaxArray<Function>* sm_pTerminalProperyArray;
		static JaxArray<Element>* sm_pTerminalArray;
		static size_t sm_uiInitialObject;
		static size_t sm_uiTerminalObject;

		class PriorityCompare
		{
		public:
			FORCEINLINE bool operator()(Element& e1, Element& e2)
			{
				static JaxPriority sp1;
				static JaxPriority sp2;
				JaxPriority* p1 = e1.pPriority ? e1.pPriority : &sp1;
				JaxPriority* p2 = e2.pPriority ? e2.pPriority : &sp2;
				return *p1 <= *p2;
			}
		};
	};
}