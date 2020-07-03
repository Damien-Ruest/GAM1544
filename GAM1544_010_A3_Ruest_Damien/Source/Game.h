#pragma once
#include "Game.h"
#include "Constants.h"
#include "Timer.h"
#include <GameDev2D.h>


namespace GameDev2D
{
	//Class definition
	class Game
	{
	public:
		Game();  //Constructor

		//Write game logic in the Update method
		void Update(double delta);

		//Render game objects in the Draw method
		void Draw();

		//Input methods
		void HandleLeftMouseClick(float mouseX, float mouseY);
		void HandleRightMouseClick(float mouseX, float mouseY);
		void HandleMouseMove(float mouseX, float mouseY, float previousX, float previousY);
		void HandleKeyPress(Keyboard::Key key);
		void HandleKeyReleased(Keyboard::Key key);
		
	private:
		//Member variables GO HERE 
		GameDev2D::Polygon* m_SineWave;
		Timer m_Timer;
	};
}
