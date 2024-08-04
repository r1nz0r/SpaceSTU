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
		uint64_t GetUniqueId() const { return m_Id; }

		Delegate<Object*> onDestroy;

	private:
		static uint64_t s_uniqueIdCounter;
		static uint64_t GetNextAvailableId();

		bool m_bIsPendingDestroy;
		uint64_t m_Id;
	};
}