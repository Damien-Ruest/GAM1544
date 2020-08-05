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
	m_Ball->MakeCircle(10.0f, true);
	m_Ball->SetColor(Color::CrimsonRedColor());
	m_Ball->SetAnchor(Vector2(0.5f, 0.5f));
	m_Ball->SetPosition(Vector2(512.0f, 748.0f));

	m_Velocity = Vector2::Zero;
	m_CatcherEndPoint_A = Vector2::Zero;
	m_CatcherEndPoint_B = Vector2::Zero;
	m_BucketEndPoint_A = Vector2::Zero;
	m_BucketEndPoint_B = Vector2::Zero;

	m_TrajectoryPoint = new GameDev2D::Polygon();
	m_TrajectoryPoint->MakeCircle(6.0f, true);

	m_Turret = new GameDev2D::Polygon();
	m_Turret->MakeCircle(70.0f, true);
	m_Turret->SetAnchor(Vector2(0.5f, 0.5f));
	m_Turret->SetPosition(Vector2(ROTATION_POINT));

	m_TurretCenter = new GameDev2D::Polygon();
	m_TurretCenter->MakeCircle(50.0f, true);
	m_TurretCenter->SetColor(Color::BlackColor());
	m_TurretCenter->SetAnchor(Vector2(0.5f, 0.5f));
	m_TurretCenter->SetPosition(Vector2(ROTATION_POINT));

	m_Cannon = new GameDev2D::Polygon();
	m_Cannon->MakeRectangle(140.0f, 30.0f, true);
	m_Cannon->SetColor(Color::BlackColor());
	m_Cannon->SetAnchor(Vector2(0.5f, 0.5f));
	m_Cannon->SetPosition(Vector2(ROTATION_POINT));

	m_CannonCenter = GameDev2D::Vector2(90.0f, 160.0f);

	m_CannonLength = m_Cannon->GetWidth() * (1.0f - m_Cannon->GetAnchor().x);

	m_BallMotion = 0;
	m_IsBallActive = false;
	m_IsBallReloaded = true;

	m_Catcher = new GameDev2D::Polygon();
	m_Catcher->MakeRectangle(250.0f, 25.0f, true);
	m_Catcher->SetAnchor(Vector2(0.5f, 0.5f));
	
	m_Bucket = new GameDev2D::Polygon();
	m_Bucket->MakeRectangle(220.0f, 14.0f, true);
	m_Bucket->SetAnchor(Vector2(0.5f, 0.0f));
	m_Bucket->SetColor(Color::BlackColor());

	/*m_Catcher_Left = new GameDev2D::Polygon();
	m_Catcher_Left->MakeCircle(12.5f, true);
	m_Catcher_Left->SetAnchor(Vector2(0.5f, 0.5f));
	m_Catcher_Left->SetColor(Color::BlackColor());

	m_Catcher_Right = new GameDev2D::Polygon();
	m_Catcher_Right->MakeCircle(12.5f, true);
	m_Catcher_Right->SetAnchor(Vector2(0.5f, 0.5f));
	m_Catcher_Right->SetColor(Color::BlackColor());*/

	m_Balls = new GameDev2D::Polygon();
	m_Balls->MakeCircle(SIZE_OF_BALL, true);
	m_Balls->SetAnchor(Vector2(0.5f, 0.5f));
	m_Balls->SetPosition(WINDOW_WIDTH - 15.0f, WINDOW_HEIGHT - 12.0f);

	m_BallCount = 8;

	m_LeftWall = new GameDev2D::Polygon();
	m_LeftWall->AddVertex(LEFT_WALL_ENDPOINT_A);
	m_LeftWall->AddVertex(LEFT_WALL_ENDPOINT_B);
	m_LeftWall->MakeRectangle(5.0f, WINDOW_HEIGHT, true);
	m_LeftWall->SetAnchor(Vector2(0.0f, 0.0f));

	m_RightWall = new GameDev2D::Polygon();
	m_RightWall->AddVertex(RIGHT_WALL_ENDPOINT_A);
	m_RightWall->AddVertex(RIGHT_WALL_ENDPOINT_B);
	m_RightWall->MakeRectangle(5.0f, WINDOW_HEIGHT, true);
	m_RightWall->SetAnchor(Vector2(1.0f, 0.0f));
	m_RightWall->SetPosition(WINDOW_WIDTH, 0.0f);

	m_TopWall = new GameDev2D::Polygon();
	m_TopWall->AddVertex(TOP_WALL_ENDPOINT_A);
	m_TopWall->AddVertex(TOP_WALL_ENDPOINT_B);
	m_TopWall->MakeRectangle(WINDOW_WIDTH, 5.0f, true);
	m_TopWall->SetAnchor(Vector2(0.0, 1.0f));
	m_TopWall->SetPosition(0.0f, WINDOW_HEIGHT - 39.0f);

	LoadFont("OpenSans-CondBold_32");
	m_CollisionCheck = new GameDev2D::SpriteFont("OpenSans-CondBold_32");
	m_CollisionCheck->SetAnchor(Vector2(0.5f, 0.5f));
	m_CollisionCheck->SetText("No collision");
	m_CollisionCheck->SetPosition(Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT /2));
	
	m_FreeBall = new GameDev2D::SpriteFont("OpenSans-CondBold_32");
	m_FreeBall->SetAnchor(Vector2(0.5f, 0.5f));
	m_FreeBall->SetText(" ");
	m_FreeBall->SetPosition(Vector2(WINDOW_WIDTH / 2, (WINDOW_HEIGHT / 2) - 40.0f));

	m_textDuration = 0;

	m_ClosestPoint_LeftWall = new GameDev2D::Polygon();
	m_ClosestPoint_LeftWall->MakeCircle(5.0f, true);
	m_ClosestPoint_LeftWall->SetColor(Color::CrimsonRedColor());
	m_ClosestPoint_LeftWall->SetAnchor(Vector2(0.5f, 0.5f));
	m_ClosestPoint_LeftWall->SetPosition(LEFT_WALL_ENDPOINT_A);

	m_ClosestPoint_RightWall = new GameDev2D::Polygon();
	m_ClosestPoint_RightWall->MakeCircle(5.0f, true);
	m_ClosestPoint_RightWall->SetColor(Color::CrimsonRedColor());
	m_ClosestPoint_RightWall->SetAnchor(Vector2(0.5f, 0.5f));
	m_ClosestPoint_RightWall->SetPosition(RIGHT_WALL_ENDPOINT_A);

	m_ClosestPoint_TopWall = new GameDev2D::Polygon();
	m_ClosestPoint_TopWall->MakeCircle(5.0f, true);
	m_ClosestPoint_TopWall->SetColor(Color::CrimsonRedColor());
	m_ClosestPoint_TopWall->SetAnchor(Vector2(0.5f, 0.5f));
	m_ClosestPoint_TopWall->SetPosition(TOP_WALL_ENDPOINT_A);

	m_ClosestPoint_Catcher = new GameDev2D::Polygon();
	m_ClosestPoint_Catcher->MakeCircle(5.0f, true);
	m_ClosestPoint_Catcher->SetColor(Color::CrimsonRedColor());
	m_ClosestPoint_Catcher->SetAnchor(Vector2(0.5f, 0.5f));
	m_ClosestPoint_Catcher->SetPosition(m_CatcherEndPoint_A);

	m_ClosestPoint_Bucket = new GameDev2D::Polygon();
	m_ClosestPoint_Bucket->MakeCircle(5.0f, true);
	m_ClosestPoint_Bucket->SetColor(Color::CrimsonRedColor());
	m_ClosestPoint_Bucket->SetAnchor(Vector2(0.5f, 0.5f));
	m_ClosestPoint_Bucket->SetPosition(m_BucketEndPoint_A);

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

	if (m_Turret != nullptr)
	{
		delete m_Turret;
		m_Turret = nullptr;
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

	/*if (m_Catcher_Left != nullptr)
	{
		delete m_Catcher_Left;
		m_Catcher_Left = nullptr;
	}

	if (m_Catcher_Right != nullptr)
	{
		delete m_Catcher_Right;
		m_Catcher_Right = nullptr;
	}*/

	if (m_LeftWall != nullptr)
	{
		delete m_LeftWall;
		m_LeftWall = nullptr;
	}

	if (m_RightWall != nullptr)
	{
		delete m_RightWall;
		m_RightWall = nullptr;
	}

	if (m_TopWall != nullptr)
	{
		delete m_TopWall;
		m_TopWall = nullptr;
	}

	if (m_Bucket != nullptr)
	{
		delete m_Bucket;
		m_Bucket = nullptr;
	}

	if (m_CollisionCheck != nullptr)
	{
		delete m_CollisionCheck;
		m_CollisionCheck = nullptr;
	}

	if (m_FreeBall != nullptr)
	{
		delete m_FreeBall;
		m_FreeBall = nullptr;
	}
	UnloadFont("OpenSans-CondBold_32");

	if (m_ClosestPoint_LeftWall != nullptr)
	{
		delete m_ClosestPoint_LeftWall;
		m_ClosestPoint_LeftWall = nullptr;
	}

	if (m_ClosestPoint_RightWall != nullptr)
	{
		delete m_ClosestPoint_RightWall;
		m_ClosestPoint_RightWall = nullptr;
	}

	if (m_ClosestPoint_TopWall != nullptr)
	{
		delete m_ClosestPoint_TopWall;
		m_ClosestPoint_TopWall = nullptr;
	}

	if (m_ClosestPoint_Catcher != nullptr)
	{
		delete m_ClosestPoint_Catcher;
		m_ClosestPoint_Catcher = nullptr;
	}
	
	if (m_ClosestPoint_Catcher != nullptr)
	{
		delete m_ClosestPoint_Catcher;
		m_ClosestPoint_Catcher = nullptr;
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

	float speed = 1000.0f;
	Vector2 velocity = Vector2(cosf(m_turretAngle), sinf(m_turretAngle)) * speed;
	position = m_CannonEnd;

	m_Trajectory.clear();
	for (int i = 0; i < 500; i++)
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
			if (m_Ball->GetPosition().y <= 0.0f /*|| m_Ball->GetPosition().x <= 0.0f || m_Ball->GetPosition().x >= WINDOW_WIDTH*/)
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
	float y2 = sinf((2 * PI * (x2 / WAVE_LENGTH))) * AMPLITUDE;
	
	m_CatcherEndPoint_A = (Vector2(WINDOW_WIDTH * AXES_X_PERCENTAGE - 125.0f, WINDOW_HEIGHT * AXES_Y_PERCENTAGE) + Vector2(y2, 0));
	m_CatcherEndPoint_B = (Vector2(WINDOW_WIDTH * AXES_X_PERCENTAGE + 125.0f, WINDOW_HEIGHT * AXES_Y_PERCENTAGE) + Vector2(y2, 0));

	m_BucketEndPoint_A = (Vector2(WINDOW_WIDTH * AXES_X_PERCENTAGE - 110.0f, WINDOW_HEIGHT * AXES_Y_PERCENTAGE) + Vector2(y2, 0));
	m_BucketEndPoint_B = (Vector2(WINDOW_WIDTH * AXES_X_PERCENTAGE + 110.0f, WINDOW_HEIGHT * AXES_Y_PERCENTAGE) + Vector2(y2, 0));

	m_Catcher->SetPosition(Vector2(WINDOW_WIDTH * AXES_X_PERCENTAGE, WINDOW_HEIGHT * AXES_Y_PERCENTAGE) + Vector2(y2, 0));
	/*m_Catcher_Left->SetPosition(Vector2(WINDOW_WIDTH * AXES_X_PERCENTAGE + 125.0f, WINDOW_HEIGHT * AXES_Y_PERCENTAGE) + Vector2(y2, 0));
	m_Catcher_Right->SetPosition(Vector2(WINDOW_WIDTH * AXES_X_PERCENTAGE - 125.0f, WINDOW_HEIGHT * AXES_Y_PERCENTAGE) + Vector2(y2, 0));*/
	m_Bucket->SetPosition(Vector2(WINDOW_WIDTH * AXES_X_PERCENTAGE, WINDOW_HEIGHT * AXES_Y_PERCENTAGE) + Vector2(y2, 0));

	Vector2 closestPoint_L = Math::CalculateClosestPoint(m_Ball->GetPosition(), SIZE_OF_BALL, LEFT_WALL_ENDPOINT_A, LEFT_WALL_ENDPOINT_B);
	m_ClosestPoint_LeftWall->SetPosition(closestPoint_L);

	Vector2 closestPoint_R = Math::CalculateClosestPoint(m_Ball->GetPosition(), SIZE_OF_BALL, RIGHT_WALL_ENDPOINT_A, RIGHT_WALL_ENDPOINT_B);
	m_ClosestPoint_RightWall->SetPosition(closestPoint_R);

	Vector2 closestPoint_T = Math::CalculateClosestPoint(m_Ball->GetPosition(), SIZE_OF_BALL, TOP_WALL_ENDPOINT_A, TOP_WALL_ENDPOINT_B);
	m_ClosestPoint_TopWall->SetPosition(closestPoint_T);

	Vector2 closestPoint_C = Math::CalculateClosestPoint(m_Ball->GetPosition(), SIZE_OF_BALL, m_CatcherEndPoint_A, m_CatcherEndPoint_B);
	m_ClosestPoint_Catcher->SetPosition(closestPoint_C);

	float distanceSquared_L = m_Ball->GetPosition().DistanceSquared(closestPoint_L);
	float distanceSquared_R = m_Ball->GetPosition().DistanceSquared(closestPoint_R);
	float distanceSquared_T = m_Ball->GetPosition().DistanceSquared(closestPoint_T);
	float distanceSquared_C = m_Ball->GetPosition().DistanceSquared(closestPoint_C);
	
	if (distanceSquared_L <= SIZE_OF_BALL * SIZE_OF_BALL)
	{
		float distance_L = sqrt(distanceSquared_L);
		Vector2 ballNormal_L = m_Velocity.Normalized();
		Vector2 wallNormal_L = (closestPoint_L - m_Ball->GetPosition()) / distance_L;

		if (ballNormal_L.DotProduct(closestPoint_L - m_Ball->GetPosition()) < 0)
		{
			wallNormal_L *= -1.0f;
		}
		if (wallNormal_L != Vector2::Zero)
		{
			float dotResult = wallNormal_L.DotProduct(m_Velocity);
			//Vector2 reflexion_L = -2.0f * dotResult * wallNormal_L + m_Velocity;
			Vector2 reflexion_L = Vector2(1.0f + (1.0f - closestPoint_L.x), closestPoint_L.y);
			m_Ball->SetPosition(reflexion_L);
		}
		m_CollisionCheck->SetText("Collision");
	}
	else if (distanceSquared_R <= SIZE_OF_BALL * SIZE_OF_BALL)
	{
		float distance_R = sqrt(distanceSquared_R);
		Vector2 ballNormal_R = m_Velocity.Normalized();
		Vector2 wallNormal_R = (closestPoint_R - m_Ball->GetPosition()) / distance_R;

		if (ballNormal_R.DotProduct(closestPoint_R - m_Ball->GetPosition()) < 0)
		{
			wallNormal_R *= -1.0f;
		}
		if (wallNormal_R != Vector2::Zero)
		{
			float dotResult = wallNormal_R.DotProduct(m_Velocity);
			Vector2 reflexion_R = -2.0f * dotResult * wallNormal_R + m_Velocity;
			m_Velocity = reflexion_R;
		}
		m_CollisionCheck->SetText("Collision");
	}
	else if (distanceSquared_T <= SIZE_OF_BALL * SIZE_OF_BALL)
	{
		float distance_T = sqrt(distanceSquared_T);
		Vector2 ballNormal_T = m_Velocity.Normalized();
		Vector2 wallNormal_T = (closestPoint_T - m_Ball->GetPosition()) / distance_T;

		if (ballNormal_T.DotProduct(closestPoint_T - m_Ball->GetPosition()) < 0)
		{
			wallNormal_T *= -1.0f;
		}
		if (wallNormal_T != Vector2::Zero)
		{
			float dotResult = wallNormal_T.DotProduct(m_Velocity);
			Vector2 reflexion_T = -2.0f * dotResult * wallNormal_T + m_Velocity;
			m_Velocity = reflexion_T;
		}
		m_CollisionCheck->SetText("Collision");
	}
	else
	{
		m_CollisionCheck->SetText("No collision");
	}

	FreeBallCollision();
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
	m_Catcher->Draw();
	/*m_Catcher_Left->Draw();
	m_Catcher_Right->Draw();*/

	for (int i = 0; i < m_BallCount; i++)
	{
		Vector2 BallChain = Vector2(WINDOW_WIDTH - (25 + i*35), WINDOW_HEIGHT - 20.0f);
		m_Balls->SetPosition(BallChain);
		m_Balls->Draw();
	}

	m_LeftWall->Draw();
	m_RightWall->Draw();
	m_TopWall->Draw();
	m_Bucket->Draw();

	m_Turret->Draw();
	m_TurretCenter->Draw();

	m_ClosestPoint_LeftWall->Draw();
	m_ClosestPoint_RightWall->Draw();
	m_ClosestPoint_TopWall->Draw();
	m_ClosestPoint_Catcher->Draw();
	m_ClosestPoint_Bucket->Draw();
	m_CollisionCheck->Draw();
	m_FreeBall->Draw();

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

void Game::FreeBallCollision()
{
	Vector2 position = m_Ball->GetPosition();
	Vector2 closestPoint = Math::CalculateClosestPoint(position, SIZE_OF_BALL, m_BucketEndPoint_A, m_BucketEndPoint_B);
	float distanceSquared = position.DistanceSquared(closestPoint);

	if (distanceSquared <= SIZE_OF_BALL * SIZE_OF_BALL)
	{
		m_textDuration = 0;
		m_IsBallActive = false;
		m_IsBallReloaded = true;
		m_FreeBall->SetText("FREE BALL");
	}
	else
	{
		m_textDuration++;
		if (m_textDuration >= TEXT_LENGTH)
		{
			m_FreeBall->SetText("");
			m_textDuration = 0;
		}
	}
}