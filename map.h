#ifndef MAP_H
#define MAP_H
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "enums.h"
#include "actor.h"

using namespace sf;
class Actor;
class Map {

private:
	Image grassTexture;
	Image wallTexture;
	Image boxTexture;
	Image exitTexture;
	Image playerTexture;
	Image exitBoxTexture;
	int sizeX;
	int sizeY;
	int currLevel;

	std::vector<std::string> tileMap= {
			"XXXXXXXXXX",
			"X        X",
			"X   *XXX X",
			"XX  @    X",
			"XX XXX X X",
			"XX * * X.X",
			"X    X X.X",
			"X   X  X.X",
			"X        X",
			"XXXXXXXXXX"};

	void loadTextures();

public:
	Map(int level);
	std::vector<std::vector<Tile>> tile;
	void draw(RenderWindow *window);
	int getSizeX();
	int getSizeY();
	void loadLevel(int level);
	void print();
	void nextLevel();
};

#endif // MAP_H
