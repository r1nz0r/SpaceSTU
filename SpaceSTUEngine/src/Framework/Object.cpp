#include "Framework/Object.h"
#include "Framework/Core.h"

namespace SSTU
{
	Object::Object()
		: m_bIsPendingDestroy(false)
	{

	}

	Object::~Object()
	{
		LOG("Object destroyed!");
	}

	void Object::Destroy()
	{
		m_bIsPendingDestroy = true;
	}
}