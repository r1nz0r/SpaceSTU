#include "Widgets/GameplayHUD.h"
#include "Player/PlayerManager.h"
#include "Player/PlayerSpaceship.h"
#include "Framework/Actor.h"
namespace SSTU
{
	GameplayHUD::GameplayHUD()
		: m_frameRateText("Frame Rate:")
		, m_playerHealthBar()
		, m_playerLifesIcon("SpaceShooterRedux/PNG/pickups/playerLife1_blue.png")
		, m_playerLifesText()
		, m_playerScoreIcon("SpaceShooterRedux/PNG/Power-ups/star_gold.png")
		, m_playerScoreText()
		, m_healtyHealtbarColor(128, 255, 128, 255)
		, m_criticalHealthbarColor(255, 0, 0, 255)
		, m_criticalThreshold(0.3f)
		, m_widgetSpacing(10.f)
	{}

	void GameplayHUD::Draw(sf::RenderWindow& window)
	{
		m_frameRateText.NativeDraw(window);
		m_playerHealthBar.NativeDraw(window);
		m_playerLifesIcon.NativeDraw(window);
		m_playerLifesText.NativeDraw(window);
		m_playerScoreIcon.NativeDraw(window);
		m_playerScoreText.NativeDraw(window);
	}

	void GameplayHUD::Tick(float deltaTime)
	{
		int frameRate = 1 / deltaTime;
		std::string frameRateStr = "Frame Rate: " + std::to_string(frameRate);
		m_frameRateText.SetString(frameRateStr);
	}

	void GameplayHUD::Init(const sf::RenderWindow& window)
	{
		int textSize = 20;
		m_frameRateText.SetTextSize(textSize);
		m_playerLifesText.SetTextSize(textSize);
		m_playerScoreText.SetTextSize(textSize);

		auto windowSize = window.getSize();
		m_playerHealthBar.SetLocation(sf::Vector2f(20.f, windowSize.y - 50.f));

		sf::Vector2f nextWidgetPosition = m_playerHealthBar.GetLocation();
		nextWidgetPosition += sf::Vector2f(m_playerHealthBar.GetBound().width + m_widgetSpacing, 0.f);
		m_playerLifesIcon.SetLocation(nextWidgetPosition);

		nextWidgetPosition += sf::Vector2f(m_playerLifesIcon.GetBound().width + m_widgetSpacing, 0.f);
		m_playerLifesText.SetLocation(nextWidgetPosition);

		nextWidgetPosition += sf::Vector2f(m_playerLifesText.GetBound().width + m_widgetSpacing * 4, -4.f);
		m_playerScoreIcon.SetLocation(nextWidgetPosition);

		nextWidgetPosition += sf::Vector2f(m_playerScoreIcon.GetBound().width + m_widgetSpacing, 4.f);
		m_playerScoreText.SetLocation(nextWidgetPosition);

		RefreshHealthbar();
		ConnectPlayerStats();
	}

	void GameplayHUD::OnPlayerHealthUpdated(float amount, float currentHealth, float maxHealth)
	{
		m_playerHealthBar.UpdateValue(currentHealth, maxHealth);

		if (currentHealth / maxHealth < m_criticalThreshold)
			m_playerHealthBar.SetForegroundColor(m_criticalHealthbarColor);
		else
			m_playerHealthBar.SetForegroundColor(m_healtyHealtbarColor);
	}

	void GameplayHUD::OnPlayerSpaceshipDestroyed(Actor* actor)
	{
		RefreshHealthbar();
	}

	void GameplayHUD::RefreshHealthbar()
	{
		auto player = PlayerManager::Instance().GetPlayer();
		if (!player || player->GetSpaceship().expired())
			return;

		auto playerSpaceship = player->GetSpaceship();
		playerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakPtr(), &GameplayHUD::OnPlayerSpaceshipDestroyed);
		auto& healthComponent = player->GetSpaceship().lock()->GetHealthComponent();
		healthComponent.onHealthChanged.BindAction(GetWeakPtr(), &GameplayHUD::OnPlayerHealthUpdated);
		OnPlayerHealthUpdated(0, healthComponent.GetHealth(), healthComponent.GetMaxHealth());
	}

	void GameplayHUD::ConnectPlayerStats()
	{
		auto player = PlayerManager::Instance().GetPlayer();
		if (!player || player->GetSpaceship().expired())
			return;

		m_playerLifesText.SetString(std::to_string(player->GetLifes()));
		player->onLifeChanged.BindAction(GetWeakPtr(), &GameplayHUD::OnPlayerLifesChanged);

		m_playerScoreText.SetString(std::to_string(player->GetScore()));
		player->onScoreChanged.BindAction(GetWeakPtr(), &GameplayHUD::OnPlayerScoreChanged);
	}

	void GameplayHUD::OnPlayerLifesChanged(int amount)
	{
		m_playerLifesText.SetString(std::to_string(amount));
	}

	void GameplayHUD::OnPlayerScoreChanged(int amount)
	{
		m_playerScoreText.SetString(std::to_string(amount));
	}
}