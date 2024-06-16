#pragma once
#include "Framework/Core.h"
#include "Framework/Object.h"
#include "functional"

namespace SSTU
{
	template<typename... Args>
	class Delegate
	{
	public:
		using Callback = std::function<bool(Args...)>;

		template<typename ClassName>
		void BindAction(std::weak_ptr<Object> obj, void(ClassName::*callback)(Args...))
		{
			Callback callbackFunc =
				[obj, callback](Args... args) -> bool
				{
					if (obj.expired())
						return false;

					(static_cast<ClassName*>(obj.lock().get())->*callback)(args...);
					return true;
				};
			
			m_callbacks.push_back(callbackFunc);
		}

		void Notify(Args... args)
		{
			for (auto iter = m_callbacks.begin(); iter != m_callbacks.end();)
			{
				if ((*iter)(args...))
					++iter;
				else
					iter = m_callbacks.erase(iter);
			}
		}

	private:
		List<Callback> m_callbacks;
	};
}