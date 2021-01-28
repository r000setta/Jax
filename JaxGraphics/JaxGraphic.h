#pragma once
#ifdef JAXGRAPHIC_EXPORTS
#define JAXGRAPHIC_API __declspec(dllexport)
#else
#define JAXGRAPHIC_API __declspec(dllimport)
#endif // JAXGRAPHIC_EXPORTS

#define PROFILER

namespace Jax
{
#define TEXLEVEL 16
}