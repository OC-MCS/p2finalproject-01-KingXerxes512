#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

class Enemy : public sf::Sprite
{
private:
	bool m_hasBeenHit = false;
public:
	Enemy(sf::Texture& m_alienTexture, int& count)
	{
		setTexture(m_alienTexture);
		setScale(1.6f, 1.6f);
		float alienX = 0 + (count * 83.0f);
		float alienY = 10;
		setPosition(alienX, alienY);
	}

	// Moves the enemy
	void moveEnemy(bool& shouldEnemyMove)
	{

		const float DISTANCE = 7.0f;

		if (shouldEnemyMove)
		{
			move(0, DISTANCE);
		}
	}

	// Returns the sprite of the enemy instance
	Enemy& getEnemySprite()
	{
		return *this;
	}

	// Returns true or false if the enemy has encountered a missile
	bool hasBeenHit()
	{
		return m_hasBeenHit;
	}

	void enemyHasBeenHit()
	{
		m_hasBeenHit = true;
	}

	Enemy& getEnemy()
	{
		return *this;
	}
};