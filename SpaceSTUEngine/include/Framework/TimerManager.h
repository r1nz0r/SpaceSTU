#pragma once
#include <functional>
#include "Framework/NonCopyable.h"
#include "Framework/Core.h"
#include "Framework/Object.h"

namespace SSTU
{
	class TimerHandler
	{
	public:
		TimerHandler();
		uint32_t GetTimerKey() const { return m_timerKey; }
	private:
		uint32_t m_timerKey;
		static uint32_t timerKeyCounter;
		static uint32_t GetNextTimerKey() { return ++timerKeyCounter; }
	};

	bool operator==(const TimerHandler& lhs, const TimerHandler& rhs);

	struct TimerHandlerHashFunction
	{
	public:
		std::size_t operator()(const TimerHandler& timerHandler) const
		{
			return timerHandler.GetTimerKey();
		}
	};

	class Timer
	{
	public:
		Timer(
			std::weak_ptr<Object> ptr,
			std::function<void()> callback,
			float duration,
			bool bShouldLoop
		);
		void TickTime(float deltaTime);
		bool Expired() const;
		void SetExpired();

	private:
		std::pair<std::weak_ptr<Object>, std::function<void()>> m_listener;
		float m_duration;
		float m_timeCounter;
		bool m_bIsLooping;
		bool m_bIsExpired;

	};

	class TimerManager : public NonCopyable
	{
	public:
		static TimerManager& Instance();
		void UpdateTimer(float deltaTime);
		
		template<typename ClassName>
		TimerHandler SetTimer(
			std::weak_ptr<Object> ptr,
			void(ClassName::* callback)(),
			float duration,
			bool bIsLooping = false
		);
		
		void ClearTimer(TimerHandler handler);

	protected:
		TimerManager();
	private:
		static std::unique_ptr<TimerManager> instance;
		Dictionary<TimerHandler, Timer, TimerHandlerHashFunction> m_timers;
		
	};


	template<typename ClassName>
	inline TimerHandler TimerManager::SetTimer(
		std::weak_ptr<Object> ptr,
		void(ClassName::* callback)(),
		float duration,
		bool bIsLooping
	)
	{
		TimerHandler newHandler {};
		auto func = [=]() { (static_cast<ClassName*>(ptr.lock().get())->*callback)(); };
		m_timers.insert({ newHandler, Timer(ptr, func, duration, bIsLooping) });
		return newHandler;
	}
}