#pragma once
#include <SFML/Graphics.hpp>

#include "Ship.h"

#include <iostream>

class Missile : public sf::Sprite
{
private:
	bool m_isMissileInFlight = true;
public:

	Missile(sf::Texture& m_missileTexture)
	{
		setTexture(m_missileTexture);
		setScale(0.35f, 0.35f);
	}

	// Sets the coordinates of where the missile is going to start
	void initializeMissile(Ship& ship)
	{
		float misX = (ship.getPos().x);
		float misY = (ship.getPos().y) - 7;
		sf::Vector2f pos(misX, misY);
		setPosition(pos);
	}

	// Returns if a missile is in flight or not
	// for removal from active missiles list
	bool isInFlight()
	{
		return m_isMissileInFlight;
	}

	// Sets if the missile is or isn't in flight
	void setFlight(bool value)
	{
		m_isMissileInFlight = value;
	}

	// Returns the sprite for the missile instance
	Missile& getMissileSprite()
	{
		return *this;
	}


};