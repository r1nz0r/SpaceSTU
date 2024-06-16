#pragma once
#include <memory>

namespace SSTU
{
	class Object : protected std::enable_shared_from_this<Object>
	{
	public:
		Object();
		virtual ~Object();

		virtual void Destroy();
		bool IsPendingDestroy() const { return m_bIsPendingDestroy; }
		std::weak_ptr<Object> GetWeakPtr();
		std::weak_ptr<const Object> GetWeakPtr() const;

	private:
		bool m_bIsPendingDestroy;
	};
}