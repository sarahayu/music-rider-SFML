#pragma once


const float A = 0.03f;
const float JUMP_DISTANCE = 125.f;

const float X_SPEED = 300.f;
const float START_VELOCITY = -JUMP_DISTANCE*A*X_SPEED;
const float VEL_STEP = std::pow(X_SPEED,2)*A*2;

const float A2 = 0.01f;

const float FLY_STEP = std::pow(X_SPEED, 2)*A2 * 2;
const float NOSE_ANGLE_SPEED = 90.f;