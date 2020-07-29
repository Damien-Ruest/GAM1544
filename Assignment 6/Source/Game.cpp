
#include "Game.h"

namespace GameDev2D
{
	Game::Game()
	{
		LoadTexture("Tank");

		m_Body = new SpriteAtlas("Tank");
		m_Body->UseFrame("Body");
		m_Body->SetAnchor(Vector2(0.5f, 0.5f));
		m_Body->SetPosition(Vector2(100.0f, 100.0f));

		m_Turret = new SpriteAtlas("Tank");
		m_Turret->UseFrame("Turret");
		m_Turret->SetAnchor(Vector2(0.2f, 0.5f));
		m_Turret->SetPosition(Vector2(100.0f, 100.0f));

		m_Shell = new SpriteAtlas("Tank");
		m_Shell->UseFrame("Shell");
		m_Shell->SetAnchor(Vector2(0.5f, 0.5f));
		m_Shell->SetPosition(Vector2(200.0f, 100.0f));


		m_Angle = 0.0f;
		m_Speed = 0.0f;
		m_Rotation = 0.0f;
		m_ShellSpeed = 0.0f;
	}

	Game::~Game()
	{
		if (m_Body != nullptr)
		{
			delete m_Body;
			m_Body = nullptr;
		}

		UnloadTexture("Body");

		if (m_Turret != nullptr)
		{
			delete m_Turret;
			m_Turret = nullptr;
		}

		UnloadTexture("Turret");

		if (m_Shell != nullptr)
		{
			delete m_Shell;
			m_Shell = nullptr;
		}

		UnloadTexture("Shell");
	}

	void Game::Update(double delta)
	{
		//Body
		if (IsKeyDown(Keyboard::A) == true)
		{
			m_Angle += BODY_ANGULAR_VELOCITY * delta;
		}
		if (IsKeyDown(Keyboard::D) == true)
		{
			m_Angle -= BODY_ANGULAR_VELOCITY * delta;
		}
		if (IsKeyDown(Keyboard::W) == true)
		{
			m_Speed += BODY_ACCELERATION * delta;

			if (m_Speed >= BODY_MAX_SPEED)
			{
				m_Speed = BODY_MAX_SPEED;
			}
		}
		else
		{
			float drag = 1.0f - BODY_DRAG;
			m_Speed *= drag;
			if (m_Speed < 1.5)
			{
				m_Speed = 0.0f;
			}
		}
		Vector2 direction = Rotation::Degrees(m_Angle).GetDirection();
		Vector2 velocity = direction * m_Speed;
		Vector2 ShellVelocity = direction * (m_ShellSpeed * delta);
		Vector2 position = m_Body->GetPosition() + velocity * delta;
		Vector2 ShellPosition = m_Shell->GetPosition() + ShellVelocity * delta;

		m_Body->SetPosition(position);
		m_Body->SetDegrees(m_Angle);

		m_Turret->SetPosition(position);
		m_Turret->SetDegrees(m_Angle + m_Rotation);

		m_Shell->SetPosition(position);
		m_Shell->SetDegrees(m_Angle + m_Rotation);
		//Turret
		if (IsKeyDown(Keyboard::Left) == true)
		{
			m_Rotation += TURRET_ANGULAR_VELOCITY * delta;
		}
		if (IsKeyDown(Keyboard::Right) == true)
		{
			m_Rotation -= TURRET_ANGULAR_VELOCITY * delta;
		}

		if (IsKeyDown(Keyboard::Spacebar) == true)
		{
			m_ShellSpeed = m_ShellSpeed + BULLET_SPEED;
			m_Shell->SetPosition(position + ShellPosition);
		}
	}

	void Game::Draw()
	{
		m_Body->Draw();

		m_Shell->Draw();

		m_Turret->Draw();
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