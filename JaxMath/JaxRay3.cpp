#include "JaxRay3.h"

namespace Jax
{
	JaxRay3::JaxRay3()
		:JaxLine3()
	{
	}

	JaxRay3::JaxRay3(const JaxVector3& orig, const JaxVector3& dir)
		:JaxLine3(orig,dir)
	{
	}

	JaxRay3::~JaxRay3()
	{
	}

	void JaxRay3::Transform(const JaxRay3& ray, const JaxMatrix4x4& mat)
	{
		JaxLine3::Transform(ray, mat);
	}


}
