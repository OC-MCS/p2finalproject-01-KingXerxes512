#pragma once
#include <SFML/Graphics.hpp>

#include "EnemyGroup.h"
#include "Assets.h"

#include <list>

class Ship : public sf::Sprite
{
private:
	int m_lives;
	bool m_isShipAlive;
	sf::Texture m_shipTexture;
	sf::Vector2f m_pos;
public:

	Ship()
	{
		m_shipTexture = Assets::loadGameTextureAsset(Assets::pacmanClosedMouthPNGPath);
		setTexture(m_shipTexture);

		// Initial position of the ship
		float shipX = 0;
		float shipY = 450;
		setPosition(shipX, shipY);
		m_lives = 3;
		m_isShipAlive = true;
	}
	// Moves the ship left or right, corresponding to which arrow key is pressed
	void moveShip(sf::RenderWindow& win)
	{

		m_pos = getPosition();

		const float DISTANCE = 6.5;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// left arrow is pressed: move our ship left 5 pixels
			// 2nd parm is y direction. We don't want to move up/down, so it's zero.
			// if statement to keep ship within frame
			move(-DISTANCE, 0);
			m_pos = getPosition();
			if (m_pos.x <= 0)
			{
				setPosition(0, m_pos.y);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			// right arrow is pressed: move our ship right 5 pixels
			// if statement to keep ship within frame
			move(DISTANCE, 0);
			m_pos = getPosition();
			if (m_pos.x >= 800 - 60)
			{
				setPosition(800 - 60, m_pos.y);
			}
		}
		win.draw(*this);
	}

	// When a life is lost, the level is reset
	// Once there are no more lives to take, the ship is no longer alive
	void lostLife(EnemyGroup& enemyGroup)
	{
		m_lives--;
		if (m_lives > 0)
		{
			enemyGroup.ResetGroup();
		}
		if (m_lives <= 0)
		{
			m_isShipAlive = false;
		}
	}

	// Checks if the enemies have gotten to the same y level as the ship
	// Takes a life and resets the level if this is true
	void checkShip(EnemyGroup& enemyGroup)
	{

		if (enemyGroup.getEnemies().size() != 0)
		{
			std::list<Enemy*>::iterator enemyItr;
			enemyItr = (enemyGroup.getEnemies()).begin();
			if (!((getPosition().y) - 40 >= (*enemyItr)->getEnemySprite().getPosition().y))
			{
				lostLife(enemyGroup);
			}
		}
	}

	// Returns the position vector of the ship
	sf::Vector2f getPos()
	{
		return m_pos;
	}

	// Returns the ship sprite
	Ship& getShipSprite()
	{
		return *this;
	}

	// Returns if the ship is or isn't alive (still has lives remaining)
	bool getShipStatus()
	{
		return m_isShipAlive;
	}

	// Returns the number of lives the ship currently has
	int getShipLives()
	{
		return m_lives;
	}

	// Sets the number of lives
	void setLives(int value)
	{
		m_lives = value;
	}
};