#pragma once

#include <GameDev2D.h>
#include "Timer.h"
#include "Ball.h"
#include "Launcher.h"
#include "Catcher.h"
#include "Trajectory.h"
#include "Constants.h"

namespace GameDev2D
{
	//Class definition
	class Game
	{
	public:
		Game();  //Constructor
		~Game(); //Destructor

		void Update(double delta);
		void Draw();
		void Reset();

		void BuildTrajectory();

		bool CheckCollision(Ball* ball, Catcher* catcher);
		void HandleCollision(Ball* ball, Catcher* catcher);

		void HandleLeftMouseClick(float mouseX, float mouseY);
		void HandleRightMouseClick(float mouseX, float mouseY);
		void HandleMouseMove(float mouseX, float mouseY, float previousX, float previousY);
		void HandleKeyPress(Keyboard::Key key);

		int RNG(int a, int b);

	private:
		//Member variables
		Ball* m_Ball;
		Launcher* m_Launcher;
		Trajectory* m_Trajectory;
        Catcher* m_Catcher;
		Polygon* m_TopLine;
		Polygon* m_BallsRemaining;
		unsigned int m_NumberOfBalls;
		SpriteFont* m_Label;
		Timer m_LabelTimer;
		bool m_isFiring;
		Polygon* m_Pegs;
		std::vector<Polygon*> m_OnScreenPegs;
		Polygon* m_WinningPegs;
		int m_RandomNumber[10];
	};
}
