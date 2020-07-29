#pragma once
#include "Timer.h"
// Class definition
class Game
{
public:
    Game();  // Constructor
    ~Game(); // Destructor

    // Write game logic in the Update method
    void Update(double delta);

    // Render game objects in the Draw method
    void Draw();

    // Input methods
    void HandleLeftMouseClick(float mouseX, float mouseY);
    void HandleRightMouseClick(float mouseX, float mouseY);
    void HandleMouseMove(float mouseX, float mouseY, float previousX, float previousY);
    void HandleKeyPress(GameDev2D::Keyboard::Key key);
    void HandleKeyReleased(GameDev2D::Keyboard::Key key);

    void HandleAngle(float x, float y, float r);

private:
    // Member variables GO HERE 
    GameDev2D::Polygon* m_Ball;
    GameDev2D::Vector2 m_Velocity;

    GameDev2D::Polygon* m_TurretTop;
    GameDev2D::Polygon* m_Cannon;

    GameDev2D::Vector2 m_CannonCenter;

    GameDev2D::Polygon* m_TrajectoryPoint;
    std::vector<GameDev2D::Vector2> m_Trajectory;

    GameDev2D::Vector2 m_mousePosition;
    float m_turretAngle;

    GameDev2D::Vector2 m_Endpoint;
    GameDev2D::Vector2 m_CannonEnd;
    float m_CannonLength;
    GameDev2D::Vector2 m_CannonPosition;

    int m_BallMotion;
    bool m_IsBallActive;
    bool m_IsBallReloaded;
    std::vector<GameDev2D::Vector2> m_BallPath;

    int m_BallCount;
    GameDev2D::Polygon* m_Balls;

    GameDev2D::Polygon* m_Catcher;
    Timer m_Timer;
};
