#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "map.h"
#include "enums.h"
#include "actor.h"
#include "levels.h"

using namespace sf;

Map::Map(int level){
	sizeX=10;
	sizeY=10;

	currLevel = level;
	loadLevel(level);

	loadTextures();
}
void Map::loadTextures(){
	if (!grassTexture.LoadFromFile("textures/grass.png"))
	{
		std::cout << "Cannot load grass" << std::endl;
	}
	if (!wallTexture.LoadFromFile("textures/wall.png"))
	{
		std::cout << "Cannot load wall" << std::endl;
	}
	if (!boxTexture.LoadFromFile("textures/box.png"))
	{
		std::cout << "Cannot load box" << std::endl;
	}
	if (!exitTexture.LoadFromFile("textures/exit.png"))
	{
		std::cout << "Cannot load exit" << std::endl;
	}
	if (!playerTexture.LoadFromFile("textures/player.png"))
	{
		std::cout << "Cannot load player" << std::endl;
	}
	if (!exitBoxTexture.LoadFromFile("textures/boxExit.png"))
	{
		std::cout << "Cannot load exitBox" << std::endl;
	}
}

void Map::draw(RenderWindow *window){
	for(int i=0; i<sizeY; i++){
		for(int j=0; j<sizeX; j++){
			if(tile[i][j]==Wall){
				Sprite wall;
				wall.SetImage(wallTexture);
				wall.Resize(RESOLUTION,RESOLUTION);
				wall.SetPosition(j*RESOLUTION, i*RESOLUTION);
				window->Draw(wall);
			}
			if(tile[i][j]==Grass){
				Sprite grass;
				grass.SetImage(grassTexture);
				grass.Resize(RESOLUTION,RESOLUTION);
				grass.SetPosition(j*RESOLUTION, i*RESOLUTION);
				window->Draw(grass);
			}
			if(tile[i][j]==Box){
				Sprite box;
				box.SetImage(boxTexture);
				box.Resize(RESOLUTION,RESOLUTION);
				box.SetPosition(j*RESOLUTION, i*RESOLUTION);
				window->Draw(box);
			}
			if(tile[i][j]==ExitBox){
				Sprite exitBox;
				exitBox.SetImage(exitBoxTexture);
				exitBox.Resize(RESOLUTION,RESOLUTION);
				exitBox.SetPosition(j*RESOLUTION, i*RESOLUTION);
				window->Draw(exitBox);
			}
			if(tile[i][j]==Exit){
				Sprite exit;
				Sprite grass;
				exit.SetImage(exitTexture);
				grass.SetImage(grassTexture);
				exit.Resize(RESOLUTION,RESOLUTION);
				grass.Resize(RESOLUTION,RESOLUTION);
				exit.SetPosition(j*RESOLUTION, i*RESOLUTION);
				grass.SetPosition(j*RESOLUTION, i*RESOLUTION);
				window->Draw(grass);
				window->Draw(exit);
			}
			if(tile[i][j]==GrassPlayer){
				Sprite player;
				Sprite grass;
				player.SetImage(playerTexture);
				grass.SetImage(grassTexture);
				player.Resize(RESOLUTION,RESOLUTION);
				grass.Resize(RESOLUTION,RESOLUTION);
				player.SetPosition(j*RESOLUTION, i*RESOLUTION);
				grass.SetPosition(j*RESOLUTION, i*RESOLUTION);
				window->Draw(grass);
				window->Draw(player);
			}
			if(tile[i][j]==ExitPlayer){
				Sprite exit;
				Sprite player;
				Sprite grass;

				player.SetImage(playerTexture);
				grass.SetImage(grassTexture);
				exit.SetImage(exitTexture);

				exit.Resize(RESOLUTION,RESOLUTION);
				player.Resize(RESOLUTION,RESOLUTION);
				grass.Resize(RESOLUTION,RESOLUTION);

				player.SetPosition(j*RESOLUTION, i*RESOLUTION);
				grass.SetPosition(j*RESOLUTION, i*RESOLUTION);
				exit.SetPosition(j*RESOLUTION, i*RESOLUTION);

				window->Draw(grass);
				window->Draw(exit);
				window->Draw(player);
			}
		}
	}

}

int Map::getSizeX(){
	return sizeX;
}
int Map::getSizeY(){
	return sizeY;
}

void Map::loadLevel(int level){
	Levels levels;
	tile.clear();

	std::cout << "Loading level " << level << "..." << std::endl;
	levels.getLevel(&tile, level);
	this->sizeY = tile.size();
	this->sizeX = tile[0].size();

}
void Map::print(){

	for(int i=0; i<sizeY; i++){
		for(int j=0; j<sizeX; j++){
			std::cout << tile[i][j];
		}
		std::cout << std::endl;
	}
}

void Map::nextLevel(){
	currLevel++;
	loadLevel(currLevel);
}
