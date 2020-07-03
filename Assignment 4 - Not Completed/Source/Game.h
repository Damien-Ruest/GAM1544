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
		SpriteAtlas* m_Background;
		SpriteAtlas* m_Sun;

		SpriteAtlas* m_Mercury;
		float m_MercuryRotation;
		Polygon* m_MercuryOrbit;

		SpriteAtlas* m_Venus;
		float m_VenusRotation;
		Polygon* m_VenusOrbit;

		SpriteAtlas* m_Earth;
		float m_EarthRotation;
		Polygon* m_EarthOrbit;

		SpriteAtlas* m_Mars;
		float m_MarsRotation;
		Polygon* m_MarsOrbit;
	};
}
