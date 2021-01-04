#pragma once
#include "JaxSystem.h"
#include "JaxRtti.h"
#include "JaxMap.h"
#include "JaxString.h"
#include "JaxReference.h"

namespace Jax
{
	class JaxObject;
	typedef JaxObject* (*FactoryFunction)();
	class JaxFastObjectManager
	{
	public:
		enum
		{
			MAX_OBJECT_FLAG=10000,
			MAX_OBJECT_NUM=MAX_OBJECT_FLAG-1
		};
		JaxFastObjectManager();
		~JaxFastObjectManager();
		size_t AddObject(JaxObject* p);
		void DeleteObject(JaxObject* p);
		bool IsClear();
		
		size_t GetObjectNum();
		
	protected:
		JaxObject* m_ObjectArray[MAX_OBJECT_FLAG];
		JaxArray<size_t> m_FreeTable;
	};

	class JAXGRAPHIC_API JaxObject :public JaxReference, public JaxMemObject
	{
	public:
		friend class JaxFastObjectManager;
		static JaxFastObjectManager& GetObjectManager()
		{
			static JaxFastObjectManager sm_ObjectManager;
			return sm_ObjectManager;
		}

		virtual ~JaxObject() = 0;
		JaxObject(const JaxObject& object);
		JaxObject& operator=(const JaxObject& object);
		JaxObject();

		DECLARE_RTTI

		bool IsSameType(const JaxObject* pObject) const;
		bool IsDerived(const JaxObject* pObject) const;
		bool IsSameType(const JaxRtti& type) const;
		bool IsDerived(const JaxRtti& type) const;

		JaxObject* GetNoGCInstance(const JaxString& rttiName);

	protected:
		size_t m_uiObjectID;
		

	public:
		size_t m_uiFlag;
	};
}