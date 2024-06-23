#pragma once
#include <memory>
#include "Framework/Delegate.h"

namespace SSTU
{
	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		Object();
		virtual ~Object();

		virtual void Destroy();
		bool IsPendingDestroy() const { return m_bIsPendingDestroy; }
		std::weak_ptr<Object> GetWeakPtr();
		std::weak_ptr<const Object> GetWeakPtr() const;

		Delegate<Object*> onDestroy;

	private:
		bool m_bIsPendingDestroy;
	};
}