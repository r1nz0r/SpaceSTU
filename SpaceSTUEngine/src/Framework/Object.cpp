#include "Framework/Object.h"
#include "Framework/Core.h"

namespace SSTU
{
	uint64_t Object::s_uniqueIdCounter = 0;

	Object::Object()
		: m_bIsPendingDestroy(false)
		, m_Id(GetNextAvailableId())
	{

	}

	Object::~Object()
	{
		LOG("Object destroyed!");
	}

	void Object::Destroy()
	{
		onDestroy.Notify(this);
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

	uint64_t Object::GetNextAvailableId()
	{
		return ++s_uniqueIdCounter;
	}
}