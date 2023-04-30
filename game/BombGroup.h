#pragma once

#include <cstdlib>
#include <ctime>
#include <list>

#include "Assets.h"
#include "EnemyGroup.h"
#include "Bomb.h"
#include "Ship.h"

#define ACTIVE true
#define INACTIVE false

class BombGroup
{
private:
	int m_max;
	const int m_min = 0;
	sf::Texture m_bombTexure;
	std::list<Bomb*> m_bombs;
public:
	BombGroup(EnemyGroup& enemyGroup)
	{
		m_bombTexure = Assets::loadGameTextureAsset(Assets::bombPNGPath);
		m_max = enemyGroup.getMaxEnemies();
	}

	// Produces a random number
	int getRandomNum(int max)
	{
		int random;
		if (max == 0)
		{
			random = 0;
		}
		else
		{
			random = (rand() % max);
		}
		return random;
	}

	// Creates a new bomb with the position parameters of a random enemy passed to the function
	void dropBomb(EnemyGroup& enemies)
	{
		if (enemies.getEnemies().size() > 0)
		{
			int enemy = getRandomNum(m_max);
			int count = 0;
			Bomb* bmbPtr;
			std::list<Enemy*>::iterator itr;
			itr = enemies.getEnemies().begin();
			while (count != enemy)
			{	// Iterates until it finds the enemy corresponding to the random number
				itr++;
				count++;
			}
			bmbPtr = new Bomb(m_bombTexure);
			bmbPtr->setBombStatus(ACTIVE);
			bmbPtr->initializeBomb((*itr)->getEnemy());
			m_bombs.push_back(bmbPtr);
		}
	}

	void CheckBombs()
	{
		std::list<Bomb*>::iterator itr;
		if (m_bombs.size() > 0)
		{
			for (itr = m_bombs.begin(); itr != m_bombs.end(); )
			{
				if (!(*itr)->getBombStatus())
				{
					itr = m_bombs.erase(itr);
				}
				else
					itr++;
			}
		}
	}

	// Move bombs
	void moveBombs(sf::RenderWindow& win, EnemyGroup& enemyGroup, Ship& ship)
	{
		const float SPEED = 5.5f;
		if (enemyGroup.getEnemies().size() > 0)
		{
			sf::FloatRect bombBounds;
			std::list<Bomb*>::iterator bombItr;
			if (m_bombs.size() > 0)
			{
				for (bombItr = m_bombs.begin(); bombItr != m_bombs.end(); bombItr++)
				{
					bombBounds = (*bombItr)->getBombSprite().getGlobalBounds();
					win.draw((*bombItr)->getBombSprite());
					(*bombItr)->getBombSprite().move(0, SPEED);
					if ((*bombItr)->getBombSprite().getPosition().y >= 600)
					{
						(*bombItr)->setBombStatus(INACTIVE);
					}
					checkIntersect(ship, bombBounds, bombItr, enemyGroup);
				}
			}
			CheckBombs();
		}
	}

	// Checks to see if a bomb and the ship have collided
	void checkIntersect(Ship& ship, sf::FloatRect& bombBounds, std::list<Bomb*>::iterator bombItr, EnemyGroup& enemyGroup)
	{
		sf::FloatRect shipBounds;
		if (m_bombs.size() != 0)
		{
			for (bombItr = (m_bombs.begin()); bombItr != (m_bombs.end()); bombItr++)
			{
				shipBounds = ship.getShipSprite().getGlobalBounds();
				if (bombBounds.intersects(shipBounds))
				{
					ship.lostLife(enemyGroup);
					(*bombItr)->setBombHit(true);
					((*bombItr)->setBombPos(sf::Vector2f(0.0f, -100.0f)));
				}
			}
		}
	}

	// Clears all bombs from the list
	void ResetGroup(EnemyGroup& enemyGroup)
	{
		std::list<Bomb*>::iterator bombItr;
		for (bombItr = m_bombs.begin(); bombItr != m_bombs.end(); bombItr++)
		{
			delete* bombItr;
		}
		m_bombs.clear();
		setMax(9);
		m_max = enemyGroup.getMaxEnemies();
	}

	// Update the number of enemies
	void enemyDown()
	{
		m_max--;
	}

	// Returns the max number of enemies
	int getMax()
	{
		return m_max;
	}

	void setMax(int value)
	{
		m_max = value;
	}

	std::list<Bomb*>& getBombs()
	{
		return m_bombs;
	}
};