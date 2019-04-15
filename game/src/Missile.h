#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ship.h"

using namespace std; using namespace sf;

class Missile {
private:
	bool m_isMissileInFlight = true;
	Sprite m_missileSprite;
public:

	Missile(Texture& m_missileTexture) {
		m_missileSprite.setTexture(m_missileTexture);
		m_missileSprite.setScale(0.35f, 0.35f);
	}
	
	// Sets the coordinates of where the missile is going to start
	void initializeMissile(Ship& ship) {
		float misX = (ship.getPos().x);
		float misY = (ship.getPos().y) - 7;
		Vector2f pos(misX, misY);
		m_missileSprite.setPosition(pos);
	}

	// Returns if a missile is in flight or not
	// for removal from active missiles list
	bool isInFlight() {
		return m_isMissileInFlight;
	}

	// Sets if the missile is or isn't in flight
	void setFlight(bool value) {
		m_isMissileInFlight = value;
	}

	// Returns the sprite for the missile instance
	Sprite& getMissileSprite() {
		return m_missileSprite;
	}


};