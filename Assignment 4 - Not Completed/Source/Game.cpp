#include "Game.h"


namespace GameDev2D
{
	Game::Game()
	{
		LoadTexture("Solar");

		m_Background = new SpriteAtlas("Solar");
		m_Background->UseFrame("Background");
		m_Background->SetAnchor(Vector2(0.0f, 0.0f));
		m_Background->SetPosition(Vector2(0.0f, 0.0f));

		m_Sun = new SpriteAtlas("Solar");
		m_Sun->UseFrame("Sun");
		m_Sun->SetAnchor(Vector2(0.5f, 0.5f));
		m_Sun->SetPosition(Vector2(512.0f, 384.0f));

		m_Mercury = new SpriteAtlas("Solar");
		m_Mercury->UseFrame("Mercury");
		m_Mercury->SetAnchor(Vector2(0.5f, 0.5f));
		m_Mercury->SetPosition(Vector2(512.0f, 384.0f + MERCURY_FROM_SUN));
		float m_MercuryRotation = 0.0;
		m_MercuryOrbit = new Polygon();
		m_MercuryOrbit->MakeCircle(MERCURY_FROM_SUN, false);
		m_MercuryOrbit->SetAnchor(Vector2(0.5f, 0.5f));
		m_MercuryOrbit->SetPosition(Vector2(512.0f, 384.0f));

		m_Venus = new SpriteAtlas("Solar");
		m_Venus->UseFrame("Venus");
		m_Venus->SetAnchor(Vector2(0.5f, 0.5f));
		m_Venus->SetPosition(Vector2(512.0f, 384.0f + VENUS_FROM_SUN));
		float m_VenusRotation = 0.0;
		m_VenusOrbit = new Polygon();
		m_VenusOrbit->MakeCircle(VENUS_FROM_SUN, false);
		m_VenusOrbit->SetAnchor(Vector2(0.5f, 0.5f));
		m_VenusOrbit->SetPosition(Vector2(512.0f, 384.0f));

		m_Earth = new SpriteAtlas("Solar");
		m_Earth->UseFrame("Earth");
		m_Earth->SetAnchor(Vector2(0.5f, 0.5f));
		m_Earth->SetPosition(Vector2(512.0f, 384.0f + EARTH_FROM_SUN));
		float m_EarthRotation = 0.0;
		m_EarthOrbit = new Polygon();
		m_EarthOrbit->MakeCircle(EARTH_FROM_SUN, false);
		m_EarthOrbit->SetAnchor(Vector2(0.5f, 0.5f));
		m_EarthOrbit->SetPosition(Vector2(512.0f, 384.0f));

		m_Mars = new SpriteAtlas("Solar");
		m_Mars->UseFrame("Mars");
		m_Mars->SetAnchor(Vector2(0.5f, 0.5f));
		m_Mars->SetPosition(Vector2(512.0f, 384.0f + MARS_FROM_SUN));
		float m_MarsRotation = 0.0;
		m_MarsOrbit = new Polygon();
		m_MarsOrbit->MakeCircle(MARS_FROM_SUN, false);
		m_MarsOrbit->SetAnchor(Vector2(0.5f, 0.5f));
		m_MarsOrbit->SetPosition(Vector2(512.0f, 384.0f));
	}

	Game::~Game()
	{
		if (m_Background != nullptr)
		{
			delete m_Background;
			m_Background = nullptr;
		}
		if (m_Sun != nullptr)
		{
			delete m_Sun;
			m_Sun = nullptr;
		}
		if (m_Mercury != nullptr)
		{
			delete m_Mercury;
			m_Mercury = nullptr;
		}
		if (m_Venus != nullptr)
		{
			delete m_Venus;
			m_Venus = nullptr;
		}
		if (m_Earth != nullptr)
		{
			delete m_Earth;
			m_Earth = nullptr;
		}
		if (m_Mars != nullptr)
		{
			delete m_Mars;
			m_Mars = nullptr;
		}

		UnloadTexture("Background");
		UnloadTexture("Sun");
		UnloadTexture("Mercury");
		UnloadTexture("Venus");
		UnloadTexture("Earth");
		UnloadTexture("Mars");
	}

	void Game::Update(double delta)
	{
		
	}

	void Game::Draw()
	{
		m_Background->Draw();

		m_Sun->Draw();
		
		m_MercuryOrbit->Draw();
		m_Mercury->Draw();
		
		m_VenusOrbit->Draw();
		m_Venus->Draw();

		m_EarthOrbit->Draw();
		m_Earth->Draw();

		m_MarsOrbit->Draw();
		m_Mars->Draw();
	}

	void Game::HandleLeftMouseClick(float mouseX, float mouseY)
	{
	
	}

	void Game::HandleRightMouseClick(float mouseX, float mouseY)
	{

	}

	void Game::HandleMouseMove(float mouseX, float mouseY, float previousX, float previousY)
	{
		
	}

	void Game::HandleKeyPress(Keyboard::Key key)
	{
  
	}

	void Game::HandleKeyReleased(Keyboard::Key key)
	{

	}
}