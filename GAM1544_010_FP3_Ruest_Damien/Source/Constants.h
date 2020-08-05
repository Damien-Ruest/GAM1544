#pragma once

#include <GameDev2D.h>

const float PI = M_PI;

const float SIZE_OF_BALL = 15.0f;

const GameDev2D::Vector2 GRAVITY = GameDev2D::Vector2(0.0f, -500.0f);

const GameDev2D::Vector2 ROTATION_POINT = GameDev2D::Vector2(WINDOW_WIDTH/2.0f, WINDOW_HEIGHT-50.0f);

const double ANIMATION_DURATION = 12.0;

const float WAVE_LENGTH = 100.0f;
const float NUM_WAVES = 3.0f;

const float AXES_X_PERCENTAGE = 0.5f;
const float AXES_Y_PERCENTAGE = 0.05f;
const float AMPLITUDE = 500.0f;

const int TEXT_LENGTH = 50;

const GameDev2D::Vector2 LEFT_WALL_ENDPOINT_A = GameDev2D::Vector2(5.0f, 0.0f);
const GameDev2D::Vector2 LEFT_WALL_ENDPOINT_B = GameDev2D::Vector2(5.0f, WINDOW_HEIGHT);

const GameDev2D::Vector2 RIGHT_WALL_ENDPOINT_A = GameDev2D::Vector2(WINDOW_WIDTH - 5.0f, 0.0f);
const GameDev2D::Vector2 RIGHT_WALL_ENDPOINT_B = GameDev2D::Vector2(WINDOW_WIDTH - 5.0f, WINDOW_HEIGHT);

const GameDev2D::Vector2 TOP_WALL_ENDPOINT_A = GameDev2D::Vector2(0.0f, WINDOW_HEIGHT - 44.0f);
const GameDev2D::Vector2 TOP_WALL_ENDPOINT_B = GameDev2D::Vector2(WINDOW_WIDTH, WINDOW_HEIGHT - 44.0f);