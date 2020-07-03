#include "Game.h"


namespace GameDev2D
{
	Game::Game()
	{
		LoadTexture("Ship");

		m_Circle = new Polygon();
		m_Circle->MakeCircle(15.0f, true, 36);
		m_Circle->SetAnchor(0.5f, 0.5f);
		m_Circle->SetPosition(0.0f, 0.0f);
		m_Circle->SetColor(Color::CharcoalColor(1.0f));
	}

	Game::~Game()
	{
		delete m_Circle;
	}

	void Game::Update(double delta)
	{
		m_time = delta;
	}

	void Game::Draw()
	{
		m_Circle->Draw();
	}

	void Game::HandleLeftMouseClick(float mouseX, float mouseY)
	{
		m_newPositionX = mouseX;
		m_newPositionY = mouseY;

		m_Circle->SetPosition(m_newPositionX, m_newPositionY);
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

	void Game::MoveObject()
	{

	}
}