#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace sf;

class Actor {
private:
	int x;
	int y;
public:

};

int main()
{

	Window window(VideoMode(800, 600, 32), "SFML Window");


	// Главный цикл приложения
	while(window.IsOpened())
	{
		// Обрабатываем события в цикле
		Event event;

		while(window.GetEvent(event))
		{
			// Кроме обычного способа наше окно будет закрываться по нажатию на Escape
			if(event.Type == Event::Closed || (event.Type == Event::KeyPressed && event.Key.Code == Key::Escape))
			window.Close();
		}

		// Тут будут вызываться функции обновления и отрисовки объектов
		// Отрисовка
		window.Display();
	}



	return 0;
}
