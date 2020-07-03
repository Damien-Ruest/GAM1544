#include "Game.h"


namespace GameDev2D
{
	Game::Game()
	{
		float screenWidth = (float)GetScreenWidth();
		float screenHeight = (float)GetScreenHeight();

		//Initialize the timer
		m_Timer.SetDuration(ANIMATION_DURATION);
		m_Timer.SetDoesLoop(true);
		m_Timer.Start();

		//Create the Sine wave
		m_SineWave = new GameDev2D::Polygon();
		m_SineWave->SetColor(Color::LicoriceColor());
		m_SineWave->SetRenderMode(RenderMode_LineStrip);
		m_SineWave->SetPosition(Vector2(screenWidth * AXES_X_PERCENTAGE, screenHeight * AXES_Y_PERCENTAGE));

	}

	void Game::Update(double delta)
	{
		float screenWidth = (float)GetScreenWidth();
		float screenHeight = (float)GetScreenHeight();

		//Calculate the sine wave end point's position
		Rotation rotation = Rotation::Radians((2.0f * PI) * m_Timer.GetPercentage());
		float radians = rotation.GetRadians();
		float x = radians * UNIT_CIRCLE_RADIUS;
		float y = sinf(radians) * UNIT_CIRCLE_RADIUS;

	}

	void Game::Draw()
	{
		m_SineWave->Draw();
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