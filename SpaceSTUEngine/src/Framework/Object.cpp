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
	
	std::weak_ptr<Object> Object::GetWeakPtr()
	{
		return weak_from_this();
	}

	std::weak_ptr<const Object> Object::GetWeakPtr() const
	{
		return weak_from_this();
	}
}