#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

#include <iostream>
#include <string>

class Sheep :
	public GameObject
{

public:
	Sheep();
	~Sheep();

	void handleInput(float dt) override;
	void update(float dt) override;

	void checkWallBounce(const sf::Shape& collider);

private:
	const float MAX_SPEED = 150.f;
	const float ACCELERATION = 300.0f;
	const float DRAG_FACTOR = 0.99f;	// friction, suggest range 0.7-0.99
	const float COEFF_OF_RESTITUTION = 0.8f;

	sf::Vector2f m_acceleration = { 0,0 };

	Animation m_walkDown;
	Animation m_walkUp;
	Animation m_walkUpRight;
	Animation m_walkRight;
	Animation m_walkDownRight;
	Animation* m_currentAnimation;
};

