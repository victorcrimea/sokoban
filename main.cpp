#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "actor.h"
#include "map.h"
#include "enums.h"
#include <iostream>

using namespace sf;

int main(int argc, char **argv)
{
	RenderWindow window(VideoMode(928, 640, 32), "Sokoban game");

	int currLevel =0;
	if(argc>1){

		currLevel=atoi(argv[1]);
	}
	std::cout<< currLevel << std::endl;

	Actor actor;
	Map map(currLevel);

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
				actor.move(Left, &map);
			}
			if(event.Type == Event::KeyPressed && event.Key.Code == Key::Up){
				actor.move(Up, &map);
			}
			if(event.Type == Event::KeyPressed && event.Key.Code == Key::Right){
				actor.move(Right, &map);
			}
			if(event.Type == Event::KeyPressed && event.Key.Code == Key::Down){
				actor.move(Down, &map);
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
