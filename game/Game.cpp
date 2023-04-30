#include "Game.h"

int Game::Start()
{
	srand((unsigned)time(0));

	sf::Vector2f mousePos;

	// Shapes and text for the pause menu
	sf::Font font = Assets::loadGameFontAsset(Assets::arialFontPath);

	sf::Text startText("Start", font, 32);
	sf::CircleShape startButton;
	startText.setPosition(sf::Vector2f(380.0f, 280.0f));
	startButton.setFillColor(sf::Color::Red);
	startButton.setOutlineColor(sf::Color::Black);
	startButton.setRadius(45);
	startButton.setPosition(sf::Vector2f(368.0f, 255.0f));

	// Counter for if a bomb or should not be dropped
	int bombCounter = 0;
	int bombFreq = 70;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), " Space Invaders -- Remake -- ");
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);

	// ======================================================
	// Class Instantiation
	Ship theShip;
	MissileGroup missiles;
	EnemyGroup enemies;
	UI ui;
	BombGroup bombs(enemies);
	// ======================================================

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		// For now, we just need this so we can click on the window and close it
		mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		sf::Event event;

		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space && missiles.getNumberOfMissiles() < 6)
				{
					missiles.FireMissile(theShip);
				}
				else if (event.key.code == sf::Keyboard::Escape)
				{
					//cout << "key pressed" << endl;
					ui.setPause(true);
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased && startButton.getGlobalBounds().contains(mousePos))
			{
				ui.setPause(false);
			}
		}

		//===========================================================
		// Start of frame drawing
		//===========================================================



		if (ui.getPause())
		{
			//cout << "Paused" << endl;
			ui.drawBackground(window);
			window.draw(startButton);
			window.draw(startText);
		}
		else
		{
			//cout << "Not Paused" << endl;
			// If the ship is alive, this logic will run
			// If not, the game is over
			if (theShip.getShipStatus())
			{

				if (!(enemies.isLevelComplete()))
				{

					// Draws the background for the game
					ui.drawBackground(window);

					// Draws the lives display
					ui.drawLives(window, theShip);

					// Moves the ship if the corresponding key is pressed
					theShip.moveShip(window);

					// Moves the missiles and checks for any intersections with the aliens and if the missile is now off screen
					missiles.moveMissiles(window, enemies);

					// Moves the bombs and checks for any intersections with the ship and if the bomb is now off screen
					bombs.moveBombs(window, enemies, theShip);

					// Checks to see if the size of the enemies list is 0 and should then set the level to COMPLETE
					// Erases any enemies that have the boolean hasBeenHit = true
					// Moves the enemies that are still in the list
					enemies.updateEnemies(window);

					if (enemies.wasEnemyHit())
					{
						bombs.enemyDown();	// If enemy was hit, then reduce the number of enemies that bombs can assign a bomb to
						ui.enemyHit();	// Increase the score
					}

					// Checks if the aliens have reached the ship's y-value
					theShip.checkShip(enemies);

					// Level is only reset when the ship detects that the aliens have reached it's y-value
					// OR when it is struck by a bomb
					// Ship checks for alien y values and BombGroup checks for bomb intersections
					if (enemies.wasLevelReset())
					{
						missiles.ResetGroup();			// If level was resest ( ship was hit by bomb or alien got to the end )
						bombs.ResetGroup(enemies);		// reset the bombs, missiles, and score
						ui.setScore(ui.getPreviousLevelScore());
						enemies.setReset(false);
					}
				}
				bombCounter++;
			}

			// Checks value of counter and if it should then drop a bomb
			if (bombFreq <= 0)
			{
				bombFreq = 1;
			}
			if (bombCounter % bombFreq == 0)
			{
				bombs.dropBomb(enemies);
			}

			// Checks to see if there are any aliens left in the list ( triggered by isLevelComplete )
			// Then resets the lives of the ship, reloads the aliens, and deletes the missiles and bombs
			if (enemies.isLevelComplete())
			{
				//cout << "Moving to next level" << endl;
				ui.setPreviousLevelScore(ui.getScore());
				missiles.ResetGroup();
				enemies.StartNextLevel();
				theShip.setLives(3);
				bombs.ResetGroup(enemies);
				bombFreq -= 10;
			}

			// If the ship is out of lives, it will draw end game screen
			if (!(theShip.getShipStatus()))
			{
				ui.drawBackground(window);
				ui.drawEndGame(window);
			}

			// end the current frame; this makes everything that we have 
			// already "drawn" actually show up on the screen

		} // end body of animation loop
		window.display();
	}
	return 0;
}
