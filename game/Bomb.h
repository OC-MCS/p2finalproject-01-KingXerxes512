#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

#define ACTIVE true
#define INACTIVE false

class Bomb : public sf::Sprite
{
private:
	bool m_isBombActive = INACTIVE;
	bool m_bombHit = false;
public:
	Bomb(sf::Texture& m_bombTexture)
	{
		setTexture(m_bombTexture);
		setScale(0.15f, 0.15f);
	}

	// Sets the bomb's coordinates to be that of the selected enemy
	void initializeBomb(Enemy& enemy)
	{
		setPosition(sf::Vector2f((enemy).getEnemySprite().getPosition().x + 10, (enemy).getEnemySprite().getPosition().y + 50));
	}

	//// Overload of the previous function to work with a pointer parameter
	//void initializeBomb(Enemy* enemy) {
	//	m_bombSprite.setPosition(Vector2f((*enemy).getEnemySprite().getPosition().x + 10, (*enemy).getEnemySprite().getPosition().y + 50));
	//}

	Bomb& getBombSprite()
	{
		return *this;
	}

	void setBombStatus(bool status)
	{
		m_isBombActive = status;
	}

	bool getBombStatus() const
	{
		return m_isBombActive;
	}

	void setBombPos(sf::Vector2f pos)
	{
		setPosition(pos);
	}

	void setBombHit(bool status)
	{
		m_bombHit = status;
	}

	bool hasBombHit() const 
	{
		return m_bombHit;
	}
};