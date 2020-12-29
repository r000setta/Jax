#pragma once
#include "JaxSystem.h"
#include "JaxSynchronize.h"
#include <Windows.h>
#include <new.h>

#define JAX_NEW new
#define JAX_DELETE delete
#define USE_STL_TYPE_TRAIT
#ifdef USE_STL_TYPE_TRAIT
#include <type_traits>
#endif // USE_STL_TYPE_TRAIT

namespace Jax
{
#ifdef USE_STL_TYPE_TRAIT
#define HAS_TRIVIAl_CONSTRUCTOR(T) std::is_trivially_constructible<T>::value
#define HAS_TRIVIAL_DESTRUCTOR(T) std::is_trivially_destructible<T>::value
#define HAS_TRIVIAL_ASSIGN(T) std::is_trivially_assignable<T>::value
#define HAS_TRIVIAL_COPY(T) std::is_trivially_copyable<T>::value
#define IS_POD(T) std::is_pod<T>::value
#define IS_ENUM(T) std::is_enum<T>::value
#define IS_EMPTY(T) std::is_empty<T>::value

	template<typename T> struct TIsFloatType {
		enum {
			Value = std::is_floating_point<T>::value
		};
	};

	template<typename T> struct TIsIntegralType {
		enum {
			Value = std::is_integral<T>::value
		};
	};

	template<typename T> struct TIsArithmeticType {
		enum {
			Value = std::is_arithmetic<T>::value
		};
	};

	template<typename T> struct TIsPointerType {
		enum {
			Value = std::is_pointer<T>::value
		};
	};

	template<typename T> struct TIsVoidType {
		enum {
			Value = std::is_void<T>::value
		};
	};

	template<typename T> struct TIsPODType {
		enum {
			Value = IS_POD(T)
		};
	};

	template<typename T> struct TIsFundamentalType {
		enum {
			Value = std::is_fundamental<T>::value
		};
	};

	template<typename T> struct ValueBase
	{
		enum {
			NeedsConstructor=!HAS_TRIVIAl_CONSTRUCTOR(T) && !TIsPODType<T>::Value
		};
		enum {
			NeedsDestructor=!HAS_TRIVIAL_DESTRUCTOR(T) && !TIsPODType<T>::Value
		};
	};
#endif
	class JAXCORE_API JaxMemManager
	{
	public:
		JaxMemManager();
		virtual ~JaxMemManager() = 0;
		virtual void* Allocate(size_t size, size_t alignment, bool isArray) = 0;
		virtual void Deallocate(char* addr, size_t alignment, bool isArray) = 0;
	};

	class JAXCORE_API JaxDebugMem :public JaxMemManager
	{
	public:
		JaxDebugMem();
		~JaxDebugMem();

		virtual void* Allocate(size_t size, size_t alignment, bool isArray);
		virtual void Deallocate(char* addr, size_t alignment, bool isArray);
		
	private:
		enum
		{
			BEGIN_MASK = 0xDEADC0DE,
			END_MASK = 0xDEADC0DE,
			RECORD_NUM = 32,
			CALLSTACK_NUM=32
		};

		static JaxCriticalSection sm_MemLock;
		class Block
		{
		public:
			Block()
			{
				for (size_t i = 0; i < CALLSTACK_NUM; ++i)
				{
					pAddr[i] = NULL;
				}
				m_pPrev = NULL;
				m_pNext = NULL;
			}
			void* pAddr[CALLSTACK_NUM];
			size_t m_uiStackInfoNum;
			size_t m_uiSize;
			bool m_bIsArray;
			bool m_bAlignment;
			Block* m_pPrev;
			Block* m_pNext;
		};
		size_t m_uiNumNewCalls;
		size_t m_uiNumDeleteCalls;
		Block* m_pHead;
		Block* m_pTail;
		size_t m_uiNumBlocks;
		size_t m_uiNumBytes;
		size_t m_uiMaxNumBytes;
		size_t m_uiMaxNumBlocks;
		size_t m_uiSizeRecord[RECORD_NUM];
		void InsertBlock(Block* pBlock);
		void RemoveBlock(Block* pBlock);
		bool GetFileAndLine(const void* pAddress, TCHAR szFile[MAX_PATH], int& line);
		bool InitDbgHelpLib();
		void FreeDbgHelpLib();
		void FreeLeakMem();
		void PrintInfo();
	};

	class JAXCORE_API JaxMemObject
	{
	public:
		JaxMemObject();
		~JaxMemObject() {}
		static JaxMemManager& GetMemManager();
	};

	typedef JaxMemManager& (*JaxMemManagerFun)();
}

#define USE_CUSTOM_NEW

#ifdef USE_CUSTOM_NEW
FORCEINLINE void* operator new(size_t size)
{
	return Jax::JaxMemObject::GetMemManager().Allocate((size_t)size, 0, false);
}
FORCEINLINE void* operator new[](size_t size)
{
	return Jax::JaxMemObject::GetMemManager().Allocate((size_t)size, 0, true);
}
FORCEINLINE void operator delete(void* pAddr)
{
	return Jax::JaxMemObject::GetMemManager().Deallocate((char*)pAddr, 0, false);
}
FORCEINLINE void operator delete[](void* pAddr)
{
	return Jax::JaxMemObject::GetMemManager().Deallocate((char*)pAddr, 0, true);
}
#endif // USE_CUSTOM_NEW

#define JAXMAC_DELETE(p) if(p) {JAX_DELETE p;p=NULL;}
#define JAXMAC_DELETEA(p) if(p) {JAX_DELETE []p;p=NULL;}