#include <GameDev2D.h>
#include "Game.h"
#include "Constants.h"

using namespace GameDev2D;

Game::Game()
{
	m_Timer.SetDuration(ANIMATION_DURATION);
	m_Timer.SetDoesLoop(true);
	m_Timer.Start();

	m_Ball = new GameDev2D::Polygon();
	m_Ball->MakeCircle(15.0f, true);
	m_Ball->SetColor(Color::CrimsonRedColor());
	m_Ball->SetAnchor(Vector2(0.5f, 0.5f));
	m_Ball->SetPosition(Vector2(512.0f, 748.0f));

	m_Velocity = Vector2::Zero;

	m_TrajectoryPoint = new GameDev2D::Polygon();
	m_TrajectoryPoint->MakeCircle(3.0f, true);

	m_TurretTop = new GameDev2D::Polygon();
	m_TurretTop->MakeCircle(70.0f, true);
	m_TurretTop->SetAnchor(Vector2(0.5f, 0.5f));
	m_TurretTop->SetPosition(Vector2(ROTATION_POINT));

	m_Cannon = new GameDev2D::Polygon();
	m_Cannon->MakeRectangle(140.0f, 40.0f, true);
	m_Cannon->SetColor(Color::BlackColor());
	m_Cannon->SetAnchor(Vector2(0.5f, 0.5f));
	m_Cannon->SetPosition(Vector2(ROTATION_POINT));

	m_CannonCenter = GameDev2D::Vector2(90.0f, 160.0f);

	m_CannonLength = m_Cannon->GetWidth() * (1.0f - m_Cannon->GetAnchor().x);

	m_BallMotion = 0;
	m_IsBallActive = false;
	m_IsBallReloaded = true;

	m_Catcher = new GameDev2D::Polygon();
	m_Catcher->MakeRectangle(300.0f, 30.0f, true);
	m_Catcher->SetAnchor(Vector2(0.5f, 0.5f));

	m_Balls = new GameDev2D::Polygon();
	m_Balls->MakeCircle(15.0f, true);
	m_Balls->SetAnchor(Vector2(0.5f, 0.5f));
	m_Balls->SetPosition(WINDOW_WIDTH - 15.0f, WINDOW_HEIGHT - 15.0f);

	m_BallCount = 8;
}

Game::~Game()
{
	if (m_Ball != nullptr)
	{
		delete m_Ball;
		m_Ball = nullptr;
	}

	if (m_TrajectoryPoint != nullptr)
	{
		delete m_TrajectoryPoint;
		m_TrajectoryPoint = nullptr;
	}

	if (m_TurretTop != nullptr)
	{
		delete m_TurretTop;
		m_TurretTop = nullptr;
	}

	if (m_Cannon != nullptr)
	{
		delete m_Cannon;
		m_Cannon = nullptr;
	}

	if (m_Catcher != nullptr)
	{
		delete m_Catcher;
		m_Catcher = nullptr;
	}
}

void Game::Update(double delta)
{
	m_Timer.Update(delta);

	m_Endpoint.x = m_CannonLength * cosf(m_Cannon->GetRadians());
	m_Endpoint.y = m_CannonLength * sinf(m_Cannon->GetRadians());
	m_CannonEnd.x = m_Endpoint.x + m_Cannon->GetPosition().x;
	m_CannonEnd.y = m_Endpoint.y + m_Cannon->GetPosition().y;

	m_Velocity += GRAVITY * delta;

	m_Cannon->SetPosition(m_CannonPosition);

	Vector2 position = m_Ball->GetPosition();
	Vector2 increment = m_Velocity * delta;
	m_Ball->SetPosition(position + increment);

	float speed = 650.0f;
	Vector2 velocity = Vector2(cosf(m_turretAngle), sinf(m_turretAngle)) * speed;
	position = m_CannonEnd;

	m_Trajectory.clear();
	for (int i = 0; i < 180; i++)
	{
		Vector2 point = Math::CalculateTrajectory(position, velocity, GRAVITY, TARGET_FPS, i);
		m_Trajectory.push_back(point);
	}
	if (m_BallCount >= 1)
	{
		if (m_IsBallActive)
		{
			Vector2 pos = m_BallPath.at(m_BallMotion);
			m_Ball->SetPosition(pos);
			m_BallMotion++;
			if (m_Ball->GetPosition().y <= 0.0f || m_Ball->GetPosition().x <= 0.0f || m_Ball->GetPosition().x >= WINDOW_WIDTH)
			{
				m_IsBallActive = false;
				m_BallCount--;
			}
		}
		if (m_IsBallActive == false)
		{
			m_IsBallReloaded = true;
		}
		if (m_BallCount >= 1)
		{

			if (m_IsBallReloaded)
			{
				m_Ball->SetPosition(m_CannonEnd);
			}
		}
	}
	Rotation rotation2 = Rotation::Radians((2.0f * PI) * m_Timer.GetPercentage());
	
	float x2 = WAVE_LENGTH * NUM_WAVES * m_Timer.GetPercentage();
	float y2 = sinf((2 * PI * (x2 / WAVE_LENGTH))) * AMPLITUDE2;
	
	m_Catcher->SetPosition(Vector2(WINDOW_WIDTH * AXES_X_PERCENTAGE2, WINDOW_HEIGHT * AXES_Y_PERCENTAGE2) + Vector2(y2, 0));
}

void Game::Draw()
{
	for (int i = 0; i < m_Trajectory.size(); i++)
	{
		Vector2 point = m_Trajectory.at(i);
		m_TrajectoryPoint->SetPosition(point);
		m_TrajectoryPoint->Draw();
	}

	m_Ball->Draw();
	m_Cannon->Draw();
	m_TurretTop->Draw();
	m_Catcher->Draw();
	for (int i = 0; i < m_BallCount; i++)
	{
		Vector2 BallChain = Vector2(WINDOW_WIDTH - (25 + i*35), WINDOW_HEIGHT - 20.0f);
		m_Balls->SetPosition(BallChain);
		m_Balls->Draw();
	}
}

void Game::HandleLeftMouseClick(float aMouseX, float aMouseY)
{
	if (m_IsBallReloaded)
	{
		m_BallMotion = 0;
		m_IsBallReloaded = false;
		m_IsBallActive = true;
		m_BallPath = m_Trajectory;
	}
}

void Game::HandleRightMouseClick(float aMouseX, float aMouseY)
{

}

void Game::HandleMouseMove(float aMouseX, float aMouseY, float aPreviousX, float aPreviousY)
{
	HandleAngle(aMouseX, aMouseY, 70.0f);
}

void Game::HandleKeyPress(Keyboard::Key aKey)
{
    if( aKey == Keyboard::Key::Escape )
    {
        Services::GetApplication()->Shutdown();
    }
}

void Game::HandleKeyReleased(Keyboard::Key key)
{

}

void Game::HandleAngle(float x, float y, float r)
{
	Vector2 tempRotate = Vector2(x - ROTATION_POINT.x, y - ROTATION_POINT.y);
	m_turretAngle = atan2(tempRotate.y, tempRotate.x);
	m_Cannon->SetRadians(m_turretAngle);
	tempRotate = Vector2(ROTATION_POINT.x + (cosf(m_turretAngle) * r), ROTATION_POINT.y + (sinf(m_turretAngle) * r));

	m_CannonPosition = tempRotate;
}
