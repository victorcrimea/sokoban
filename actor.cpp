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

	getPosition(map);
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

	if(x>(map->getSizeX()-1)) x=map->getSizeX()-1;
	if(y>(map->getSizeY()-1)) y=map->getSizeY()-1;
	if(x<0) x=0;
	if(y<0) y=0;

	update();

	if(isFinished(map)){
		std::cout<< "Level finished" << std::endl;
		map->nextLevel();
	}
}

void Actor::update(){
	sprite.SetPosition(x*RESOLUTION, y*RESOLUTION);
	//std::cout << "x=" << x <<"; y=" << y <<std::endl;
}
bool Actor::performMove(Tile *current, Tile *next, Tile *nextNext){
	if(*next!=Wall){
		if(*next==Box ){ //Box meeting
			if(*nextNext==Exit){ //When we successfully moving box to the exit
				*next=GrassPlayer;
				*nextNext=ExitBox;
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
		}else if(*next==ExitBox ){ //ExitBox meeting
			if(*nextNext==Exit){ //When we successfully moving Exitbox to the exit
				*next=ExitPlayer;
				*nextNext=ExitBox;
				if(*current==GrassPlayer){
					*current=Grass;
				}else {
					*current=Exit;
				}
				return true;
			}else if(*nextNext==Grass){
				*nextNext=Box;
				*next=ExitPlayer;
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

bool Actor::isFinished(Map *map){
	int sizeX = map->getSizeX();
	int sizeY = map->getSizeY();
	int freeBoxes=0;

	for(int i=0; i<sizeY; i++){
		for(int j=0; j<sizeX; j++){
			if(map->tile[i][j]==Box) freeBoxes++;
			//std::cout << "i=" << i << "; j=" << j << "; boxes="<< freeBoxes<< std::endl;
		}
	}

	if(freeBoxes==0) return true;
	return false;
}

void Actor::getPosition(Map *map){
	int sizeX = map->getSizeX();
	int sizeY = map->getSizeY();
	for(int i=0; i<sizeY; i++){
		for(int j=0; j<sizeX; j++){
			if(map->tile[i][j]==GrassPlayer || map->tile[i][j]==ExitPlayer) {
				x=j;
				y=i;
			}

		}
	}
}
