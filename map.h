#ifndef MAP_H
#define MAP_H
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
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

/*	std::string tileMap[MAPY]= {
		"XXXXXXXXXX",
		"X        X",
		"X        X",
		"X   P    X",
		"X  XXX   X",
		"X  B B   X",
		"X   O    X",
		"X        X",
		"X        X",
		"XXXXXXXXXX"};
*/

	std::string tileMap[MAPY]= {
			"XXXXXXXXXX",
			"X        X",
			"X   BXXX X",
			"XX  P    X",
			"XX XXX X X",
			"XX B B XOX",
			"X   O  X X",
			"X   X  X X",
			"X        X",
			"XXXXXXXXXX"};

	void loadTextures();

public:
	Map(Actor *actor);
	Tile tile[MAPY][MAPX];


	void draw(RenderWindow *window);

};

#endif // MAP_H
