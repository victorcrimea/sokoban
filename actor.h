#ifndef ACTOR_H
#define ACTOR_H
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.h"
#include "enums.h"
using namespace sf;
class Map;
class Actor {
private:
	int x;
	int y;
	Sprite sprite;
	Image playerTexture;
	void update();
	bool performMove(Tile *curr, Tile *next, Tile *nextNext);
public:

	Actor();
	void put(int x, int y);
	void move(Direction dir, Map *map);
};

#endif // ACTOR_H
