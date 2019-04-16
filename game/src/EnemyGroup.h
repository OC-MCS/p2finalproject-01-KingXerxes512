#pragma once
#include <list>
#include "Enemy.h"

using namespace std; using namespace sf;

enum reloadEnum {NEW, SAME};

class EnemyGroup {
private:
	const int m_MAX_ENEMIES = 10;
	Texture m_alienTexture_1;
	Texture m_alienTexture_2;
	Texture m_alienTexture_3;
	Texture m_alienTexture_4;
	Texture m_currentTexture;
	list<Enemy*> m_enemies;
	bool enemyWasHit;
	bool levelWasReset;
	bool levelComplete;
	int shouldEnemiesMoveCounter = 0;
	int moveFrequency = 15;	// The lower this value is, the fast the enemies will move down
public:
	EnemyGroup() {
		if (!m_alienTexture_1.loadFromFile("src\\PACMAN RED ENEMY.png")) {
			cout << "Unable to load alien texture!" << endl;
			exit(EXIT_FAILURE);
		}
		if (!m_alienTexture_2.loadFromFile("src\\PACMAN CYAN ENEMY.png")) {
			cout << "Unable to load alien texture!" << endl;
			exit(EXIT_FAILURE);
		}
		if (!m_alienTexture_3.loadFromFile("src\\PACMAN ORANGE ENEMY.png")) {
			cout << "Unable to load alien texture!" << endl;
			exit(EXIT_FAILURE);
		}
		if (!m_alienTexture_4.loadFromFile("src\\PACMAN PINK ENEMY.png")) {
			cout << "Unable to load alien texture!" << endl;
			exit(EXIT_FAILURE);
		}
		loadEnemies(NEW);
		levelComplete = false;
	}

	// Runs through the list of enemies and checks to see which enemies should be removed from the list
	void updateEnemies(RenderWindow& win) {
		enemyWasHit = false;
		list<Enemy*>::iterator itr;
		if (m_enemies.size() == 0) {
			setLevelCompletion(true);
		}
		else {
			shouldEnemiesMoveCounter++;
			bool shouldEnemiesMove = (!(shouldEnemiesMoveCounter % moveFrequency));
			for (itr = m_enemies.begin(); itr != m_enemies.end(); ) {
				if ((*itr)->hasBeenHit()) {
					itr = m_enemies.erase(itr);
					enemyWasHit = true;
				}
				else
					itr++;
			}
			for (itr = m_enemies.begin(); itr != m_enemies.end(); itr++) {
				(*itr)->moveEnemy(shouldEnemiesMove);
				win.draw((*itr)->getEnemySprite());
			}
		}
	}

	// Deletes the entire list of enemies and calls the loadEnemies function to 'reset' the enemies
	void ResetGroup() {
		levelWasReset = true;
		list<Enemy*>::iterator itr;
		for (itr = m_enemies.begin(); itr != m_enemies.end(); itr++) {
			delete *itr;
		}
		m_enemies.clear();
		loadEnemies(SAME);	// SAME makes it not load a new texture since it's the same enemies
	}

	// This will setup for the next level
	void StartNextLevel() {
		list<Enemy*>::iterator itr;
		for (itr = m_enemies.begin(); itr != m_enemies.end(); itr++) {
			delete *itr;
		}
		m_enemies.clear();
		loadEnemies(NEW);	// NEW makes it load a potential new texture for aliens
		setLevelCompletion(false);
	}

	// Returns a reference to the list of enemies
	list<Enemy*>& getEnemies() {
		return m_enemies;
	}

	void setTextures() {
		// Generates a random number and assigns the corresponding texture
		int random;
		random = ((rand() % 4) + 1);
		switch (random) {
		case 1: m_currentTexture = m_alienTexture_1;
			break;
		case 2: m_currentTexture = m_alienTexture_2;
			break;
		case 3: m_currentTexture = m_alienTexture_3;
			break;
		case 4: m_currentTexture = m_alienTexture_4;
			break;
		}
		//cout << "random = " << random << endl;
	}

	// Loads the list of enemies to display
	// Called for constructor and when a life is lost
	void loadEnemies(reloadEnum value) {
		if (value == NEW) {
			setTextures();
			Enemy* m_enemyPtr;
			for (int count = 0; count < m_MAX_ENEMIES; count++) {
				m_enemyPtr = new Enemy(m_currentTexture, count);
				m_enemies.push_back(m_enemyPtr);
			}
		}
		else {
			Enemy* m_enemyPtr;
			for (int count = 0; count < m_MAX_ENEMIES; count++) {
				m_enemyPtr = new Enemy(m_currentTexture, count);
				m_enemies.push_back(m_enemyPtr);
			}
		}
		
	}
	
	// Returns the max number of aliens created
	int getMaxEnemies() {
		return m_MAX_ENEMIES;
	}

	// Returns a true or false if an enemy was hit
	bool wasEnemyHit() {
		return enemyWasHit;
	}

	// Returns a true or false if the level is complete
	bool isLevelComplete() {
		return levelComplete;
	}

	// Sets the completion status of the level (true = completed)
	void setLevelCompletion(bool status) {
		levelComplete = status;
	}

	// Returns a true or false if the level was reset
	bool wasLevelReset() {
		return levelWasReset;
	}

	// Sets the reset boolean
	void setReset(bool reset) {
		levelWasReset = reset;
	}
};