#include "JaxLine3.h"
#include "JaxMatrix4x4.h"
namespace Jax
{
	JaxLine3::JaxLine3()
		:m_Orig(JaxVector3{ 0,0,0 }), dir(JaxVector3{0,0,0})
	{

	}

	JaxLine3::JaxLine3(const JaxVector3& orig, const JaxVector3& dir)
		:m_Orig(orig),m_Dir(dir)
	{

	}

	JaxLine3::~JaxLine3()
	{

	}

	void JaxLine3::Transform(const JaxLine3& line, const JaxMatrix4x4& mat)
	{
		m_Dir = mat.Apply3X3(line.m_Dir);
		m_Dir.Normalize();
		m_Orig = line.m_Orig * mat;
	}

}
