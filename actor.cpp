#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "actor.h"
#include "map.h"
#include "enums.h"
using namespace sf;
Actor::Actor(){
	if (!playerTexture.LoadFromFile("textures/player.png"))
	{
		std::cout << "Cannot load player" << std::endl;
	}
	sprite.SetImage(playerTexture);
	x=0;
	y=0;
}

void Actor::put(int x, int y){
	this->x = x;
	this->y = y;
	update();
}

void Actor::move(Direction dir, Map *map){

	Tile &current = map->tile[y][x];
	if(dir == Left){
		Tile &next = map->tile[y][x-1];
		Tile &nextNext = map->tile[y][x-2];
		if(performMove(&current, &next, &nextNext)) x-=1;
	}else if(dir == Up){
		Tile &next = map->tile[y-1][x];
		Tile &nextNext = map->tile[y-2][x];
		if(performMove(&current, &next, &nextNext)) y -= 1;
	}else if(dir == Right){
		Tile &next = map->tile[y][x+1];
		Tile &nextNext = map->tile[y][x+2];
		if(performMove(&current, &next, &nextNext)) x+= 1;
	}else if(dir == Down){
		Tile &next = map->tile[y+1][x];
		Tile &nextNext = map->tile[y+2][x];
		if(performMove(&current, &next, &nextNext)) y+= 1;
	}

	if(x>(MAPX-1)) x=MAPX-1;
	if(y>(MAPY-1)) y=MAPY-1;
	if(x<0) x=0;
	if(y<0) y=0;

	update();
}

void Actor::update(){
	sprite.SetPosition(x*RESOLUTION, y*RESOLUTION);
	std::cout << "x=" << x <<"; y=" << y <<std::endl;
}
bool Actor::performMove(Tile *current, Tile *next, Tile *nextNext){
	if(*next!=Wall){
		if(*next==Box ){ //Box meeting
			if(*nextNext==Exit){ //When we successfully moving box to the exit
				*next=GrassPlayer;
				if(*current==GrassPlayer){
					*current=Grass;
				}else {
					*current=Exit;
				}
				return true;
			}else if(*nextNext==Grass){
				*nextNext=Box;
				*next=GrassPlayer;
				if(*current==GrassPlayer){
					*current=Grass;
				}else {
					*current=Exit;
				}
				return true;
			}
		}else if(*next==Exit){ // When we going to the Exit
			*next=ExitPlayer;
			if(*current==GrassPlayer){
				*current=Grass;
			}else {
				*current=Exit;
			}
			return true;
		}else{ // Just regular step to the grass
			*next=GrassPlayer;
			if(*current==GrassPlayer){
				*current=Grass;
			}else {
				*current=Exit;
			}
			return true;
		}
	}
	return false;
}

