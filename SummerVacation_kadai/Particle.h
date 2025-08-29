#pragma once
#include "Vec2.h"

class Particle
{
public:
	Particle();
	~Particle();

	void Init(Vec2 startPos, Vec2 Velocity);
	void Update();
	void Draw();
	bool IsAlive() const;

private:
	Vec2 m_pos;
	Vec2 m_velocity;
};

