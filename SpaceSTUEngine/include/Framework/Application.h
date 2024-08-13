#pragma once
#include "SFML/Graphics.hpp"
#include "Framework/Core.h"

namespace SSTU
{
    class World;
    class Application
    {
    public:
        Application(
            uint32_t windowWidth,
            uint32_t windowHeight,
            const std::string& title,
            sf::Uint32 style
        );
        
        void Run();

        template<typename WorldType>
        std::weak_ptr<WorldType> LoadWorld();

        sf::Vector2u GetWindowSize() const;
        sf::RenderWindow& GetWindow() { return m_window; }
        const sf::RenderWindow& GetWindow() const { return m_window; }
        void Quit();

    private:
        void TickInternal(float deltaTime);
        void RenderInternal();
        virtual void Render();
        virtual void Tick(float deltaTime);
        bool DispatchEvent(const sf::Event& event);

        sf::RenderWindow m_window;
        float m_targetFrameRate;
        sf::Clock m_tickClock;

        sf::Clock m_cleanCycleClock;
        sf::Time m_cleanCycleInterval;

        std::shared_ptr<World> m_currentWorld;
        std::shared_ptr<World> m_pendingWorld;

    };

    template<typename WorldType>
    std::weak_ptr<WorldType> Application::LoadWorld()
    {
        static_assert(std::is_base_of<World, WorldType>::value, "WorldType must derive from World");

        auto newWorld = std::make_shared<WorldType>(this);
        m_pendingWorld = newWorld;
        return newWorld;
    }
}