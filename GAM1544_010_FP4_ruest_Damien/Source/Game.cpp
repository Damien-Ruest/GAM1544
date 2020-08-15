#include "Game.h"

namespace GameDev2D
{
	random_device seed;
	mt19937 mersenneTwister(seed());

	Game::Game() 
		: m_LabelTimer(1.0)
		, m_isFiring(false)
    {
		//Create the Ball, Catcher, Launch and Trajectory objects
		m_Ball = new Ball();
		m_Launcher = new Launcher(m_Ball);
		m_Trajectory = new Trajectory();
        m_Catcher = new Catcher();

		//Create the top line Polygon object
		m_TopLine = new Polygon();
		m_TopLine->AddVertex(0.0f, 0.0f);
		m_TopLine->AddVertex(WINDOW_WIDTH, 0.0f);
		m_TopLine->SetRenderMode(RenderMode_LineStrip);
		m_TopLine->SetPosition(Vector2(0.0f, WINDOW_HEIGHT - BALL_RADIUS * 2.0f));
		
		//Create the HUD ball Polygon object
		m_BallsRemaining = new Polygon();
		m_BallsRemaining->MakeCircle(BALL_RADIUS - 1.0f, true);
		m_BallsRemaining->SetAnchor(Vector2(0.5f, 0.5f));

		//Load the Font Data
		LoadFont("heavy_data_150");

		//Create the Label's SpriteFont
		m_Label = new SpriteFont("heavy_data_150");
		m_Label->SetPosition(Vector2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f));
		m_Label->SetAnchor(Vector2(0.5f, 0.5f));
		m_Label->SetJustification(SpriteFont::JustifyCenter);
		m_Label->SetText("");

		//Initialize the number of balls
		m_NumberOfBalls = INITIAL_NUMBER_OF_BALLS;

		for (int j = 0; j < 10; j++)
		{
			bool DuplicateCheck;
			int random;
			do
			{
				DuplicateCheck = false;
				random = RNG(0, PEG_AMOUNT - 1);
				for (int i = 0; i < 10; i++)
				{
					if (random == m_RandomNumber[i])
					{
						DuplicateCheck = true;
					}
				}

			} while (DuplicateCheck);
			m_RandomNumber[j] = random;
		}

		bool AreYouWinning = false;

		for (int i = 0; i < PEG_AMOUNT; i++)
		{
			AreYouWinning = false;

			m_Pegs = new Polygon();
			m_Pegs->MakeCircle(PEG_RADIUS, true);
			m_Pegs->SetPosition(Vector2(100.0f, 100.0f));
			m_Pegs->SetAnchor(Vector2(0.5f, 0.5f));
			m_Pegs->SetColor(Color::BlueColor());

			m_WinningPegs = new Polygon();
			m_WinningPegs->MakeCircle(PEG_RADIUS, true);
			m_WinningPegs->SetAnchor(Vector2(0.5f, 0.5f));
			m_WinningPegs->SetColor(Color::OrangeColor());
			m_WinningPegs->SetPosition(Vector2(100.0f, 100.0f));
			
			for (int j = 0; j < 10; j++)
			{
				if (i == m_RandomNumber[j])
				{
					m_OnScreenPegs.push_back(m_WinningPegs);
					AreYouWinning = true;
				}
			}
			if (AreYouWinning == false)
			{
				m_OnScreenPegs.push_back(m_Pegs);
			}
		}

		int Row_Two = 0;
		int Row_Three = 0;
		int Row_Four = 0;
		int Row_Five = 0;

		for (int i = 0; i < m_OnScreenPegs.size(); i++)
		{
			if (i < 12)
			{
				m_OnScreenPegs[i]->SetPosition(Vector2(WINDOW_WIDTH / 13 + ((WINDOW_WIDTH / 13) * i), 550.0f));
			}
			else if (i < 23)
			{
				m_OnScreenPegs[i]->SetPosition(Vector2(WINDOW_WIDTH / 12 + ((WINDOW_WIDTH / 12) * Row_Two), 450.0f));
				Row_Two++;
			}
			else if (i < 35)
			{
				m_OnScreenPegs[i]->SetPosition(Vector2(WINDOW_WIDTH / 13 + ((WINDOW_WIDTH / 13) * Row_Three), 350.0f));
				Row_Three++;
			}
			else if (i < 46)
			{
				m_OnScreenPegs[i]->SetPosition(Vector2(WINDOW_WIDTH / 12 + ((WINDOW_WIDTH / 12) * Row_Four), 250.0f));
				Row_Four++;
			}
			else if (i < m_OnScreenPegs.size())
			{
				m_OnScreenPegs[i]->SetPosition(Vector2(WINDOW_WIDTH / 13 + ((WINDOW_WIDTH / 13) * Row_Five), 150.0f));
				Row_Five++;
			}
		}
	}

	Game::~Game()
	{
        if (m_Ball != nullptr)
        {
            delete m_Ball;
            m_Ball = nullptr;
        }

        if (m_Launcher != nullptr)
        {
            delete m_Launcher;
            m_Launcher = nullptr;
        }

        if (m_Trajectory != nullptr)
        {
            delete m_Trajectory;
            m_Trajectory = nullptr;
        }

        if (m_Catcher != nullptr)
        {
            delete m_Catcher;
            m_Catcher = nullptr;
        }

        if (m_TopLine != nullptr)
        {
            delete m_TopLine;
            m_TopLine = nullptr;
        }

        if (m_BallsRemaining != nullptr)
        {
            delete m_BallsRemaining;
            m_BallsRemaining = nullptr;
        }

		if (m_Label != nullptr)
		{
			delete m_Label;
			m_Label = nullptr;
		}

		if (m_Pegs != nullptr)
		{
			delete m_Pegs;
			m_Pegs = nullptr;
		}

		if (m_WinningPegs != nullptr)
		{
			delete m_WinningPegs;
			m_WinningPegs = nullptr;
		}

		UnloadFont("heavy_data_150");
	}

    void Game::Update(double aDelta)
    {
        //Update the launcher and catcher
        m_Launcher->Update(aDelta);
        m_Catcher->Update(aDelta);

		//Is the Label Timer running? Update it!
		if (m_LabelTimer.IsRunning() == true)
		{
			m_LabelTimer.Update(aDelta);

			//Is the timer done?
			if (m_LabelTimer.GetPercentage() == 1.0f)
			{
				//Show the trajectory and clear the Label
				m_Trajectory->Show();
				m_Label->SetText("");

				/* allow shot to be fired again after timer reset not during it */
				m_isFiring = false;
			}
			else
			{
				return;
			}
		}

        //Apply gravity to the ball and update it
        m_Ball->ApplyGravity(GRAVITY, aDelta);
        m_Ball->Update(aDelta);

		//Check collision with the catcher
		if (CheckCollision(m_Ball, m_Catcher) == true)
		{
			HandleCollision(m_Ball, m_Catcher);
		}

        //Did the ball go off the bottom of the screen?
        if (m_Ball->GetPosition().y <= -BALL_RADIUS)
        {
            m_Ball->Reset();
            m_Trajectory->Show();

			/* reset firing */
			m_isFiring = false;

            //If there are no balls remaining, then its Game over
            if (m_NumberOfBalls == 0)
            {
                m_Trajectory->Hide();
                m_Launcher->ResetBall(false);
            }
        }

        //Build the trajectory for the ball
        BuildTrajectory();

		for (int i = 0; i < m_OnScreenPegs.size(); i++)
		{
			float distanceSquared = m_Ball->GetPosition().DistanceSquared(m_OnScreenPegs[i]->GetPosition());

			//Calculate the collision response
			if (distanceSquared <= (BALL_RADIUS + PEG_RADIUS) * (BALL_RADIUS + PEG_RADIUS))
			{
				//Calculate the collision normal
				float distance = sqrtf(distanceSquared);
				Vector2 normal = (m_OnScreenPegs[i]->GetPosition() - m_Ball->GetPosition()) / distance;

				//Calculate the response velocity
				float ballA = m_Ball->GetVelocity().DotProduct(normal);
				Vector2 responseA = Vector2::Zero;
				responseA.x = m_Ball->GetVelocity().x - ballA * normal.x - ballA * normal.x;
				responseA.y = m_Ball->GetVelocity().y - ballA * normal.y - ballA * normal.y;
				m_Ball->SetVelocity(responseA);
			}
		}

		for (int i = 0; i < m_OnScreenPegs.size(); i++)
		{
			float distanceSquared = m_Ball->GetPosition().DistanceSquared(m_OnScreenPegs[i]->GetPosition());
			if (distanceSquared <= (BALL_RADIUS + PEG_RADIUS) * (BALL_RADIUS + PEG_RADIUS) && !m_OnScreenPegs.empty())
			{
				int LastIndex = m_OnScreenPegs.size() - 1;
				Polygon* temp = m_OnScreenPegs[LastIndex];
				m_OnScreenPegs[i] = temp;

				m_OnScreenPegs.pop_back();
			}
		}
    }

	void Game::Draw()
	{
		//Draw the top line
		m_TopLine->Draw();

		//Draw the number of balls remaining
		Vector2 position = Vector2(BALL_RADIUS, WINDOW_HEIGHT - BALL_RADIUS);
		for (unsigned int i = 0; i < m_NumberOfBalls; i++)
		{
			//Draw the balls remaining polygon
			m_BallsRemaining->SetPosition(position);
			m_BallsRemaining->Draw();

			//Increment the position x value
			position.x += BALL_RADIUS * 2.0f;
		}

        //Draw the trajectory
        m_Trajectory->Draw();

		//Draw the launcher, the ball, the catcher
		m_Ball->Draw();
		m_Launcher->Draw();
        m_Catcher->Draw();

		for (int i = 0; i < m_OnScreenPegs.size(); i++)
		{
			m_OnScreenPegs[i]->Draw();
		}

		//Draw the Label
		m_Label->Draw();
	}

	void Game::Reset()
	{
		////Reset the ball
		//m_Ball->Reset();
		//
		////Show the trajectory
		//m_Trajectory->Show();
		//
        ////Reset the launcher - allows the ball to be set by the launcher
        //m_Launcher->ResetBall(true);
		//
		////Reset the number of balls and the number of pegs hit
		//m_NumberOfBalls = INITIAL_NUMBER_OF_BALLS;
	}

	void Game::BuildTrajectory()
	{
		//Clear the trajectory
		m_Trajectory->Clear();

		//Get the launcher's current starting position and initial velocity
		Vector2 startingPosition = m_Launcher->GetLaunchPosition();
		Vector2 startingVelocity = m_Launcher->GetInitialVelocity();

		//Cycle through one second (60 fps) to determine the trajectory point for each frame
		for (int i = 0; i < 90; i++)
		{
			//Get the trajectory position for i
			Vector2 trajectoryPosition = Math::CalculateTrajectoryPoint(startingPosition, startingVelocity, GRAVITY, TARGET_FPS, (float)i);

			//Add the trajectory position to the trajectory
			m_Trajectory->Add(trajectoryPosition);
		}
	}

	bool Game::CheckCollision(Ball* aBall, Catcher* aCatcher)
	{
		//Ensure the ball is moving
		if (aBall->GetVelocity() != Vector2::Zero)
		{
			//Calculate the closest point of the line
			Vector2 lineStart = aCatcher->GetPosition() - Vector2(aCatcher->GetWidth() / 2.0f, 0.0f);
			Vector2 lineEnd = aCatcher->GetPosition() + Vector2(aCatcher->GetWidth() / 2.0f, 0.0f);
			Vector2 closestPoint = Math::CalculateClosestPoint(aBall->GetPosition(), aBall->GetRadius(), lineStart, lineEnd);

			//Calculate the distance between the closest point and the center of the ball
			float distanceSquared = aBall->GetPosition().DistanceSquared(closestPoint);
			float radiiSquared = aBall->GetRadius() * aBall->GetRadius();

			//If the distance squared is less than the radii squared, then there's a collision
			bool didCollide = distanceSquared < radiiSquared;
			return didCollide;
		}
		return false;
	}

	void Game::HandleCollision(Ball* aBall, Catcher* aCatcher)
	{
		//Reset the ball and show the trajectory
		m_Ball->Reset();

		//Free ball
		m_NumberOfBalls++;

		//Set the spritefont text to Free Ball
		m_Label->SetColor(Color::OrangeColor());
		m_Label->SetText("FREE BALL!");
		m_LabelTimer.Restart();

		/* hide trajectory until able to shoot */
		m_Trajectory->Hide();
	}

    void Game::HandleLeftMouseClick(float aMouseX, float aMouseY)
    {
        //Launch the ball
		if (m_NumberOfBalls > 0)
		{
			/* lock firing until reset */
			if (!m_isFiring)
			{
				m_Launcher->Fire();
				
				m_isFiring = true;
	     
				//Decrement the number of balls left
				m_NumberOfBalls--;
			}
		}
    }

	void Game::HandleRightMouseClick(float aMouseX, float aMouseY)
	{

	}

	void Game::HandleMouseMove(float aMouseX, float aMouseY, float aPreviousX, float aPreviousY)
	{
		m_Launcher->HandleMouseMove(aMouseX, aMouseY);  
	}

	void Game::HandleKeyPress(Keyboard::Key aKey)
	{
		if (aKey == Keyboard::R)
		{
			if (m_NumberOfBalls == 0)
				Reset();
		}
		//else if (aKey == Keyboard::B)
		//{
  //          //Cheat key to add another ball
		//	m_NumberOfBalls++;
		//}
	}

	int Game::RNG(int a, int b)
	{
		uniform_int_distribution<int> distribution(a, b);
		return distribution(mersenneTwister);
	}

}