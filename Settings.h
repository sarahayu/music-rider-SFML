#pragma once

namespace Settings
{
	const float A = 0.0102651509f;
	const float JUMP_DISTANCE = 172.146f;
	const float X_SPEED = 400.f;
	const float START_VELOCITY = -JUMP_DISTANCE*A*X_SPEED;
	const float VEL_STEP = std::pow(X_SPEED, 2)*A * 2;

	const float A2 = 0.005f;
	const float FLY_STEP = std::pow(X_SPEED, 2)*A2 * 2;

	const std::string SUFFIX = ".level";
}