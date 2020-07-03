#pragma once

#include <GameDev2D.h>


namespace GameDev2D
{
	//Class definition
	class Game
	{
	public:
		Game();  //Constructor
		~Game(); //Deconstructor

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

		void MoveObject();
		
	private:
		//Member variables GO HERE 
		GameDev2D::Polygon* m_Circle;
		//Before click
		float m_oldPositionX = 0;
		float m_oldPositionY = 0;

		//After click
		float m_newPositionX = 0;
		float m_newPositionY = 0;

		float m_time = 0;
	};
}
