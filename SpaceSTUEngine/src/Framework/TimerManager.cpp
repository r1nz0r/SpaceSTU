#include "Framework/TimerManager.h"

namespace SSTU
{
	std::unique_ptr<TimerManager> TimerManager::instance { nullptr };

	void TimerManager::ClearTimer(TimerHandler handler)
	{
		auto iter = m_timers.find(handler);

		if (iter != m_timers.end())
			iter->second.SetExpired();
	}

	TimerManager::TimerManager() : m_timers() {}

	TimerManager& TimerManager::Instance()
	{
		if (!instance)
			instance = std::move(std::unique_ptr<TimerManager>(new TimerManager {}));

		return *instance;
	}

	void TimerManager::UpdateTimer(float deltaTime)
	{
		for (auto iter = m_timers.begin(); iter != m_timers.end();)
		{
			if (iter->second.Expired())
				iter = m_timers.erase(iter);
			else
				iter++->second.TickTime(deltaTime);
		}
	}

	Timer::Timer(
		std::weak_ptr<Object> ptr,
		std::function<void()> callback,
		float duration,
		bool bShouldLoop
	)
		: m_listener {ptr, callback}
		, m_duration{duration}
		, m_bIsLooping{bShouldLoop}
		, m_timeCounter{0.f}
		, m_bIsExpired{false}
	{

	}

	void Timer::TickTime(float deltaTime)
	{
		if (Expired())
			return;

		m_timeCounter += deltaTime;
		
		if (m_timeCounter >= m_duration)
		{
			m_listener.second();

			if (m_bIsLooping)
				m_timeCounter = 0.f;
			else
				SetExpired();
		}
	}

	bool Timer::Expired() const
	{
		return m_bIsExpired || m_listener.first.expired() || m_listener.first.lock()->IsPendingDestroy();
	}

	void Timer::SetExpired()
	{
		m_bIsExpired = true;
	}

	uint32_t TimerHandler::timerKeyCounter { 0 };

	TimerHandler::TimerHandler() : m_timerKey(GetNextTimerKey()) {}

	bool operator==(const TimerHandler& lhs, const TimerHandler& rhs)
	{
		return lhs.GetTimerKey() == rhs.GetTimerKey();
	}
}