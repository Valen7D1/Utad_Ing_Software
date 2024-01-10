#pragma once

const unsigned int NUM_BALLS = 10;  // Max. num balls.
const float MAX_BALL_SPEED = 8.0f;   // Max vel. of ball (pixels/?).

void LogicInitialization();
void ProcessGameLogic();
void Shutdown();