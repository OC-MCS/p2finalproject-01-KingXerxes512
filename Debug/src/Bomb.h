#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

#define ACTIVE true
#define INACTIVE false

class Bomb {
private:
	bool m_isBombActive = INACTIVE;
	bool m_bombHit = false;
	Sprite m_bombSprite;
public:
	Bomb(Texture& m_bombTexture) {
		m_bombSprite.setTexture(m_bombTexture);
		m_bombSprite.setScale(0.15f, 0.15f);
	}

	// Sets the bomb's coordinates to be that of the selected enemy
	void initializeBomb(Enemy& enemy) {
		m_bombSprite.setPosition(Vector2f((enemy).getEnemySprite().getPosition().x + 10, (enemy).getEnemySprite().getPosition().y + 50));
	}

	//// Overload of the previous function to work with a pointer parameter
	//void initializeBomb(Enemy* enemy) {
	//	m_bombSprite.setPosition(Vector2f((*enemy).getEnemySprite().getPosition().x + 10, (*enemy).getEnemySprite().getPosition().y + 50));
	//}

	Sprite& getBombSprite() {
		return m_bombSprite;
	}

	void setBombStatus(bool status) {
		m_isBombActive = status;
	}

	bool getBombStatus() {
		return m_isBombActive;
	}

	void setBombPos(Vector2f pos) {
		m_bombSprite.setPosition(pos);
	}

	void setBombHit(bool status) {
		m_bombHit = status;
	}

	bool hasBombHit() {
		return m_bombHit;
	}
};