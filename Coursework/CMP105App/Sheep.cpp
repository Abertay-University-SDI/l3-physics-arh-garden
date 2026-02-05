#include "Sheep.h"

Sheep::Sheep()
{
	// initialise animations
	for (int i = 0; i < 4; i++)
		m_walkDown.addFrame({ { 64 * i, 0 }, { 64, 64 } });
	m_walkDown.setLooping(true);
	m_walkDown.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkUp.addFrame({ { (64 * (i + 4)), 0 }, { 64, 64 } });
	m_walkUp.setLooping(true);
	m_walkUp.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkUpRight.addFrame({ { 64 * i, 64 }, { 64, 64 } });
	m_walkUpRight.setLooping(true);
	m_walkUpRight.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkRight.addFrame({ { (64 * (i + 4)), 64 }, { 64, 64 } });
	m_walkRight.setLooping(true);
	m_walkRight.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkDownRight.addFrame({ { 64 * i, 128 }, { 64, 64 } });
	m_walkDownRight.setLooping(true);
	m_walkDownRight.setFrameSpeed(0.25f);

	// the next 4 animations go clockwise from Up through Right to Down.

	m_currentAnimation = &m_walkDown;
	setTextureRect(m_currentAnimation->getCurrentFrame());

	// initialise collision shape
	m_collisionBox.size = { 36, 52 };
	m_collisionBox.position = { 14, 6 };
}

Sheep::~Sheep()
{
}

void Sheep::handleInput(float dt)
{
	sf::Vector2f inputDir = { 0,0 };

	inputDir.x = m_input->isKeyDown(sf::Keyboard::Scancode::D) - m_input->isKeyDown(sf::Keyboard::Scancode::A);
	inputDir.y = m_input->isKeyDown(sf::Keyboard::Scancode::S) - m_input->isKeyDown(sf::Keyboard::Scancode::W);
	

	if (inputDir.lengthSquared() >= pow(FLT_EPSILON, 2)) {
		//std::cout << "{ " + std::to_string(inputDir.x) + "," + std::to_string(inputDir.y) + " }\n";
		m_acceleration = inputDir.normalized() * ACCELERATION * dt;
	}
	else {
		m_acceleration = { 0,0 };
	}
}


void Sheep::update(float dt)
{
	m_velocity -= m_velocity * DRAG_FACTOR * dt;
	m_velocity += m_acceleration * dt;

	checkWallBounce({ 1024,1024 });

	std::cout << "pos: { " + std::to_string(getPosition().x) + "," + std::to_string(getPosition().y) + " }\n";
	//std::cout << "collision rect: { { " + std::to_string(getCollisionBox().size.x) + "," + std::to_string(getCollisionBox().size.y)
	//	+ "} , { " + std::to_string(getCollisionBox().position.x) + "," + std::to_string(getCollisionBox().position.y) + "}\n";

	m_velocity.x = std::clamp(m_velocity.x, -MAX_SPEED, MAX_SPEED);
	m_velocity.y = std::clamp(m_velocity.y, -MAX_SPEED, MAX_SPEED);

	move(m_velocity);
}


void Sheep::checkWallBounce(const sf::Vector2f bgSize)
{
	sf::Vector2f bodyMin = -getCollisionBox().size / 2.f;
	sf::Vector2f bodyMax = getCollisionBox().size / 2.f;
	sf::Vector2f bgMin = { 0,0 };
	sf::Vector2f bgMax = bgSize - getSize();

	// x
	if (getPosition().x <= 0 || getPosition().x >= bgMax.x) {
		m_velocity.x = -m_velocity.x;

		float target = std::clamp(getPosition().x, bodyMin.x, bgMax.x);
		setPosition({ target,getPosition().y });
	}
	// y
	if (getPosition().y <= 0 || getPosition().y >= bgMax.y) {
		m_velocity.y = -m_velocity.y;

		float target = std::clamp(getPosition().y, bodyMin.y, bgMax.y);
		setPosition({ getPosition().x,target });
	}
}