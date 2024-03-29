#pragma once

#include "Ship.h"
#include "Assets.h"

#include <string>

class UI
{
private:
	sf::Font font;
	sf::Texture m_starsTexture;
	sf::Texture m_heartTexture;
	sf::Sprite m_background;
	bool m_paused = true;
	int m_Score = 0;
	int m_PreviousLevelScore = 0;

	static inline float scaleX = 1.25f;
	static inline float scaleY = 1.25f;

	static inline std::string m_hitCountString = "Score: 0";

public:
	UI()
	{
		m_starsTexture = Assets::loadGameTextureAsset(Assets::starsBackgroundJPGPath);
		m_heartTexture = Assets::loadGameTextureAsset(Assets::heartPNGPath);
		font = Assets::loadGameFontAsset(Assets::arialFontPath);

		m_background.setScale(scaleX, scaleY);
		m_background.setTexture(m_starsTexture);
	}

	// This will draw the background of the game along with the hit count string
	void drawBackground(sf::RenderWindow& win)
	{
		sf::Text scoreDisplay(m_hitCountString, font, 30);
		scoreDisplay.setFillColor(sf::Color::White);
		scoreDisplay.setOutlineColor(sf::Color::Black);
		scoreDisplay.setPosition(sf::Vector2f(10.0f, 550.0f));
		win.draw(m_background);
		win.draw(scoreDisplay);
	}

	// Sets the string to output the hit count
	void setString()
	{
		m_hitCountString = "Score: ";
		m_hitCountString = m_hitCountString + std::to_string(m_Score);
	}

	// Function which is called whenever an enemy is hit to update the hit count
	void enemyHit()
	{
		m_Score = m_Score + 100;
		setString();
	}

	// This is drawn whenever the ship has run out of lives
	void drawEndGame(sf::RenderWindow& win)
	{
		sf::Text gameOver("GAME OVER\n ALIENS WIN!", font, 45);
		gameOver.setFillColor(sf::Color::Red);
		gameOver.setPosition(250.0f, 250.0f);
		win.draw(gameOver);
	}

	// Draws Text "Lives " and a number of hearts corresponding to the number of lives remaining
	void drawLives(sf::RenderWindow& win, Ship& ship)
	{
		std::list<sf::Sprite> Hearts;
		sf::Sprite m_heart;
		m_heart.setScale(0.07f, 0.07f);
		m_heart.setTexture(m_heartTexture);
		m_heart.setPosition(sf::Vector2f(340.0f, 550.0f));
		Hearts.push_back(m_heart);
		m_heart.setPosition(sf::Vector2f(400.0f, 550.0f));
		Hearts.push_back(m_heart);
		m_heart.setPosition(sf::Vector2f(460.0f, 550.0f));
		Hearts.push_back(m_heart);

		std::list<sf::Sprite>::iterator itr;
		sf::Text Lives("Lives ", font, 30);
		Lives.setFillColor(sf::Color::White);
		Lives.setOutlineColor(sf::Color::Black);
		Lives.setPosition(sf::Vector2f(250.0f, 550.0f));

		if (ship.getShipLives() == 3)
		{
			for (itr = Hearts.begin(); itr != Hearts.end(); itr++)
			{
				win.draw(*itr);
			}
		}
		else if (ship.getShipLives() == 2)
		{
			itr = Hearts.end();	// sets the iterator to the end of the list then goes back one
			itr--;				// Then deletes the last element so only two hearts are drawn
			Hearts.erase(itr);
			for (itr = Hearts.begin(); itr != Hearts.end(); itr++)
			{
				win.draw(*itr);
			}
		}
		else if (ship.getShipLives() == 1)
		{
			for (int count = 0; count < 2; count++)
			{
				itr = Hearts.end();	// Runs through a loop so that it goes to the end of the list and then back one
				itr--;				// It then erases that element so that only one heart is drawn
				Hearts.erase(itr);
			}
			for (itr = Hearts.begin(); itr != Hearts.end(); itr++)
			{
				win.draw(*itr);
			}
		}
		else {}	// Game should be over at this point so not code needed

		win.draw(Lives);
	}

	// Sets the boolean value if the game is paused or not
	void setPause(bool value)
	{
		m_paused = value;
	}

	// Sets the hit value for whenever a level is reset or a different level is reached
	void setScore(int value)
	{
		m_Score = value;
		setString();
	}

	bool getPause()
	{
		return m_paused;
	}

	int getScore()
	{
		return m_Score;
	}

	void setPreviousLevelScore(int value)
	{
		m_PreviousLevelScore = value;
	}

	int getPreviousLevelScore()
	{
		return m_PreviousLevelScore;
	}
};