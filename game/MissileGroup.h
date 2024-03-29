#pragma once
#include <SFML/Graphics.hpp>

#include "Missile.h"
#include "EnemyGroup.h"
#include "Ship.h"

#include <list>

class MissileGroup
{
private:
	sf::Texture m_missileTexture;
	std::list<Missile*> m_missiles;
public:

	MissileGroup()
	{
		m_missileTexture = Assets::loadGameTextureAsset(Assets::pacmanMissilePNGPath);
	}

	// Adds a missile to the list of active missiles
	void FireMissile(Ship& ship)
	{
		Missile* mslPtr;
		mslPtr = new Missile(m_missileTexture);
		m_missiles.push_back(mslPtr);
		mslPtr->initializeMissile(ship);
		//cout << "Missile added\n";
	}

	// Checks to see if the missile should be removed from the list
	void CheckMissiles()
	{
		std::list<Missile*>::iterator itr;
		//cout << m_missiles.size() << endl;
		for (itr = m_missiles.begin(); itr != m_missiles.end(); )
		{
			if (!(*itr)->isInFlight())
			{
				itr = m_missiles.erase(itr);
			}
			else
				itr++;
		}
		//cout << m_missiles.size() << endl;
	}

	// Called in main
	// Deletes the list of missiles (triggered only when a life is lost)
	void ResetGroup()
	{
		std::list<Missile*>::iterator itr;
		for (itr = m_missiles.begin(); itr != m_missiles.end(); itr++)
		{
			delete* itr;
		}
		m_missiles.clear();
	}

	// Runs through list of missiles and moves them up the screen, then
	// checks if any missiles should still be in flight
	void moveMissiles(sf::RenderWindow& win, EnemyGroup& enemyGroup)
	{
		if (!(enemyGroup.getEnemies().size() == 0))
		{
			sf::FloatRect missileBounds;
			std::list<Missile*>::iterator missileItr;
			for (missileItr = m_missiles.begin(); missileItr != m_missiles.end(); missileItr++)
			{
				const float SPEED = 9.5f;
				missileBounds = (*missileItr)->getMissileSprite().getGlobalBounds();
				win.draw((*missileItr)->getMissileSprite());
				(*missileItr)->getMissileSprite().move(0, -SPEED);
				if ((*missileItr)->getMissileSprite().getPosition().y < -10.0f)
				{
					(*missileItr)->setFlight(false);
				}
				checkIntersect(enemyGroup, missileBounds, missileItr);
			}
			CheckMissiles();
		}
	}

	// Called in moveMissiles  to see if any missiles intersect the bounds of any aliens
	void checkIntersect(EnemyGroup& enemyGroup, sf::FloatRect& missileBounds, std::list<Missile*>::iterator missileItr)
	{
		sf::FloatRect alienBounds;
		std::list<Enemy*>::iterator enemyItr;
		if (enemyGroup.getEnemies().size() != 0)
		{
			for (enemyItr = (enemyGroup.getEnemies()).begin(); enemyItr != (enemyGroup.getEnemies()).end(); enemyItr++)
			{
				alienBounds = (*enemyItr)->getEnemySprite().getGlobalBounds();
				if (missileBounds.intersects(alienBounds))
				{
					(*enemyItr)->enemyHasBeenHit();
					((*missileItr)->getMissileSprite()).setPosition(0.0f, -100.0f);
				}
			}
		}
	}

	// Returns the size of the list A.K.A. the number of missiles in flight
	int getNumberOfMissiles()
	{
		return (int)m_missiles.size();
	}
};