#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std; using namespace sf;

class Enemy {
private:
	Sprite m_enemySprite;
	bool m_hasBeenHit = false;
public:
	Enemy(Texture& m_alienTexture, int& count) {
		m_enemySprite.setTexture(m_alienTexture);
		m_enemySprite.setScale(1.6f, 1.6f);
		float alienX = 0 + (count * 83.0f);
		float alienY = 10;
		m_enemySprite.setPosition(alienX, alienY);
	}

	// Moves the enemy
	void moveEnemy(bool& shouldEnemyMove) {

		const float DISTANCE = 7.0f;

		if (shouldEnemyMove)
		{
			m_enemySprite.move(0, DISTANCE);
		}
	}

	// Returns the sprite of the enemy instance
	Sprite& getEnemySprite() {
		return m_enemySprite;
	}

	// Returns true or false if the enemy has encountered a missile
	bool hasBeenHit() {
		return m_hasBeenHit;
	}

	void enemyHasBeenHit() {
		m_hasBeenHit = true;
	}

	// Sets whether or not the enemy will drop a bomb
	//void setDropBomb(bool value) {
	//	dropBomb = value;
	//}

	//// Returns if the enemy should drop bomb
	//bool getDropBomb() {
	//	return dropBomb;
	//}

	Enemy& getEnemy() {
		return *this;
	}
};