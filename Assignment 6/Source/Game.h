#pragma once

#include "Constants.h"
#include <GameDev2D.h>

namespace GameDev2D
{
	//Class definition
	class Game
	{
	public:
		Game();  //Constructor

		~Game();

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
		SpriteAtlas* m_Body;
		SpriteAtlas* m_Turret;
		SpriteAtlas* m_Shell;
		float m_Angle;
		float m_Speed;
		float m_Rotation;
		float m_ShellSpeed;
	};
}
