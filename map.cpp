#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "map.h"
#include "enums.h"
#include "actor.h"

using namespace sf;

Map::Map(Actor *actor){
	for(int i=0; i<MAPY; i++){
		for(int j=0; j<MAPX; j++){
			if(tileMap[i][j]=='X') tile[i][j]=Wall;
			if(tileMap[i][j]==' ') tile[i][j]=Grass;
			if(tileMap[i][j]=='B') tile[i][j]=Box;
			if(tileMap[i][j]=='O') tile[i][j]=Exit;
			if(tileMap[i][j]=='P') {
				tile[i][j]=GrassPlayer;
				actor->put(j,i);
			}
		}
	}
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
}

void Map::draw(RenderWindow *window){
	for(int i=0; i<MAPY; i++){
		for(int j=0; j<MAPX; j++){
			if(tile[i][j]==Wall){
				Sprite wall;
				wall.SetImage(wallTexture);
				wall.SetPosition(j*RESOLUTION, i*RESOLUTION);
				window->Draw(wall);
			}
			if(tile[i][j]==Grass){
				Sprite grass;
				grass.SetImage(grassTexture);
				grass.SetPosition(j*RESOLUTION, i*RESOLUTION);
				window->Draw(grass);
			}
			if(tile[i][j]==Box){
				Sprite box;
				box.SetImage(boxTexture);
				box.SetPosition(j*RESOLUTION, i*RESOLUTION);
				window->Draw(box);
			}
			if(tile[i][j]==Exit){
				Sprite exit;
				Sprite grass;
				exit.SetImage(exitTexture);
				grass.SetImage(grassTexture);
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
