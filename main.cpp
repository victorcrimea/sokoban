#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

enum Direction {Left, Up, Right, Down};
enum Tile {Wall, Grass, Box, Exit, Player};

const int RESOLUTION = 64;
const int MAPX=10;
const int MAPY=10;


class Actor {
private:
	int x;
	int y;
	Sprite sprite;
	Image playerTexture;
	void update(){
		sprite.SetPosition(x*RESOLUTION, y*RESOLUTION);
		//std::cout << "x=" << x <<"; y=" << y <<std::endl;
	}

public:

	Actor(){
		if (!playerTexture.LoadFromFile("textures/player.png"))
		{
			std::cout << "Cannot load player" << std::endl;
		}
		sprite.SetImage(playerTexture);
		x=0;
		y=0;
	}

	void put(int x, int y){
		this->x = x;
		this->y = y;
		update();
	}
	void move(Direction dir, Map *map){
		if(dir == Left){
			x -= 1;
		}else if(dir == Up){
			y -=1;
		}else if(dir == Right){
			x +=1;
		}else if(dir == Down){
			y +=1;
		}

		if(x>(MAPX-1)) x=MAPX-1;
		if(y>(MAPY-1)) y=MAPY-1;
		if(x<0) x=0;
		if(y<0) y=0;

		update();
	}
};

class Map {
private:
	Image grassTexture;
	Image wallTexture;
	Image boxTexture;
	Image exitTexture;
	Image playerTexture;

	std::string tileMap[MAPY]= {
		"XXXXXXXXXX",
		"X        X",
		"X        X",
		"X   P    X",
		"X  XXX   X",
		"X  B B   X",
		"X   O    X",
		"X        X",
		"X        X",
		"XXXXXXXXXX"
	};
	void loadTextures(){
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

public:
	Tile tile[MAPY][MAPX];
	Map(Actor &actor){
		for(int i=0; i<MAPY; i++){
			for(int j=0; j<MAPX; j++){
				if(tileMap[i][j]=='X') tile[i][j]=Wall;
				if(tileMap[i][j]==' ') tile[i][j]=Grass;
				if(tileMap[i][j]=='B') tile[i][j]=Box;
				if(tileMap[i][j]=='O') tile[i][j]=Exit;
				if(tileMap[i][j]=='P') {
					tile[i][j]=Player;
					actor.put(i,j);
				}
			}
		}
		loadTextures();
	}
	void draw(RenderWindow *window){
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
				if(tile[i][j]==Player){
					Sprite player;
					Sprite grass;
					player.SetImage(playerTexture);
					grass.SetImage(grassTexture);
					player.SetPosition(j*RESOLUTION, i*RESOLUTION);
					grass.SetPosition(j*RESOLUTION, i*RESOLUTION);
					window->Draw(grass);
					window->Draw(player);
				}
			}
		}
	}

};




int main()
{
	RenderWindow window(VideoMode(640, 640, 32), "Sokoban game");

	Actor actor;
	Map map(actor);

	while(window.IsOpened())
	{
		// handling events in cycle
		Event event;

		while(window.GetEvent(event))
		{
			// This game can be closed with escape button too
			if(event.Type == Event::Closed || (event.Type == Event::KeyPressed && event.Key.Code == Key::Escape)){
				window.Close();
			}

			// Handle player movements
			if(event.Type == Event::KeyPressed && event.Key.Code == Key::Left){
				actor.move(Left);
			}
			if(event.Type == Event::KeyPressed && event.Key.Code == Key::Up){
				actor.move(Up);
			}
			if(event.Type == Event::KeyPressed && event.Key.Code == Key::Right){
				actor.move(Right);
			}
			if(event.Type == Event::KeyPressed && event.Key.Code == Key::Down){
				actor.move(Down);
			}

		}

		//Clearing window
		window.Clear();

		map.draw(&window);


		// Drawing
		window.Display();
	}



	return 0;
}
