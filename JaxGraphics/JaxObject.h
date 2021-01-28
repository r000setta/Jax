#pragma once
#include "JaxSystem.h"
#include "JaxReference.h"
#include "JaxPriority.h"
#include "JaxRtti.h"
#include "JaxMap.h"
#include "JaxString.h"
#include "JaxName.h"
#include "JaxMain.h"

namespace Jax
{

	class JaxObject;
	typedef JaxObject* (*FactoryFunction)();
	class JaxStream;
	class JaxResourceProxyBase;
	class JaxRenderer;
	class JaxResourceIdentifier;
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
		friend class JaxStream;

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
	public:
		friend class JaxRtti;
		static JaxObject* GetInstance(const JaxString& rttiName);
		static JaxObject* GetInstance(const JaxRtti& rtti);
		template<typename T>
		static T* GetInstance()
		{
			return (T*)GetInstance(T::sm_Type);
		}

		virtual bool BeforeSave(void* data = NULL);
		virtual bool PostSave(void* data = NULL);
		virtual bool PostLoad(void* data = NULL);


		bool IsSameType(const JaxObject* pObject) const;
		bool IsDerived(const JaxObject* pObject) const;
		bool IsSameType(const JaxRtti& type) const;
		bool IsDerived(const JaxRtti& type) const;

		virtual void LoadEvent(JaxResourceProxyBase* proxy, int data = 0);

		DECLARE_INITIAL_NO_CLASS_FACTORY;

	public:
		static JaxObject* _CloneCreateObject(JaxObject* object, JaxMap<JaxObject*, JaxObject*>& cloneMap);
		static void _CloneObject(JaxObject* src, JaxObject* dest, JaxMap<JaxObject*, JaxObject*>& cloneMap);
		static JaxObject* CloneCreateObject(JaxObject* object);
		static void CloneObject(JaxObject* src,JaxObject* dest);

		virtual bool PostClone(JaxObject* src);

	protected:
		size_t m_uiObjectID;
		static JaxObject* GetNoGCInstance(const JaxString& rttiName);
		static JaxMapOrder<JaxUsedName, FactoryFunction> sm_ClassFactory;

	public:
		enum
		{
			OF_REACH=0x01,
			OF_UNREACH=0x02,
			OF_GCObject=0x04,
			OF_RootObject=0x10,
			OF_MAX
		};

		FORCEINLINE void SetFlag(size_t flag)
		{
			m_uiFlag |= flag;
		}

		FORCEINLINE void ClearFlag(size_t flag)
		{
			m_uiFlag &= ~flag;
		}

		FORCEINLINE bool IsHasFlag(size_t flag)
		{
			return (m_uiFlag & flag) != 0;
		}

		size_t m_uiFlag;
	};

	DECLARE_PTR(JaxObject);
	JAXTYPE_MARCO(JaxObject);
	template<typename T>
	T* StaticCast(JaxObject* obj)
	{
		return (T*)obj;
	}

	template<typename T>
	const T* StaticCast(const JaxObject* obj)
	{
		return (const T*)obj;
	}

	template<typename T>
	T* DynamicCast(JaxObject* obj)
	{
		return obj && obj->IsDerived(T::sm_Type) ? (T*)obj : NULL;
	}

	template<typename T>
	const T* DynamicCast(const JaxObject* obj)
	{
		return obj && obj->IsDerived(T::sm_Type) ? (const T*)obj : NULL;
	}
}