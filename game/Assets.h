#pragma once

#include <iostream>
#include <string>

namespace Assets
{
	static inline std::string starsBackgroundJPGPath = "src\\stars.jpg";
	static inline std::string heartPNGPath = "src\\heart.png";
	static inline std::string arialFontPath = "C:\\Windows\\Fonts\\arial.ttf";
	static inline std::string pacmanClosedMouthPNGPath = "src\\PACMAN CLOSED MOUTH.png";
	static inline std::string pacmanMissilePNGPath = "src\\PACMAN MISSILE.png";
	static inline std::string pacmanRedEnemyPNGPath = "src\\PACMAN RED ENEMY.png";
	static inline std::string pacmanCyanEnemyPNGPath = "src\\PACMAN CYAN ENEMY.png";
	static inline std::string pacmanOrangeEnemyPNGPath = "src\\PACMAN ORANGE ENEMY.png";
	static inline std::string pacmanPinkEnemyPNGPath = "src\\PACMAN PINK ENEMY.png";
	static inline std::string bombPNGPath = "src\\bomb.png";

	static sf::Texture loadGameTextureAsset(const std::string& path) noexcept;
	static sf::Font loadGameFontAsset(const std::string& path) noexcept;

	// Wrapper to load and sf texture and check return value
	// If this function fails, the program will exit
	sf::Texture loadGameTextureAsset(const std::string& path) noexcept
	{
		sf::Texture newTexture;
		
		if (!newTexture.loadFromFile(path))
		{
			std::cout << "Unable to load texture from \"" << path << "\"" << std::endl;
			exit(EXIT_FAILURE);
		}

		return newTexture;
	}

	// Wrapper to load and sf font and check return value
	// If this function fails, the program will exit
	sf::Font loadGameFontAsset(const std::string& path) noexcept
	{
		sf::Font newFont;

		if (!newFont.loadFromFile(path))
		{
			std::cout << "Unable to load texture from \"" << path << "\"" << std::endl;
			exit(EXIT_FAILURE);
		}

		return newFont;
	}
}
