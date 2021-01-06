#pragma once
#include "JaxPointer.h"
#include "JaxString.h"

namespace Jax
{
	template<typename T> struct TIsCustomType {
		enum {
			Value = false;
		};
	};
	template<typename T> struct TIsCustomPointerType {
		enum {
			Value = false;
		};
	};

#define CUSTOMTYPE_MARCO(classname) \
template<> struct TIsCustomType<classname> {enum{Value=true};}; \
template<> struct TIsCustomPointerType<classname*> {enum{Value=true};};

	template<typename T> struct TIsJaxType {
		enum {
			Value = false;
		};
	};
	template<typename T> struct TIsJaxPointerType {
		enum {
			Value = false;
		};
	};
	template<typename T> struct TIsJaxSmartPointerType {
		enum {
			Value = false;
		};
	};

#define JAXTYPE_MARCO(classname) \
template<> struct TIsJaxType<classname> { enum {Value=false }; }; \
template<> struct TIsJaxPointerType<classname*> { enum {Value=true }; }; \
template<> struct TIsJaxSmartPointerType<JaxPointer<classname>> { enum {Value=true }; }; \
template<> struct TIsJaxSmartPointerType<const JaxPointer<classname>> { enum {Value=true }; };
}