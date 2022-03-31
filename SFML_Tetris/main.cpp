#include <SFML\Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(320, 480), "Tetris?");

	Texture texture;
	texture.loadFromFile("C:\\Users\\Леночка\\source\\repos\\SFML_Tetris\\images\\tiles.png");

	Sprite sprite(texture);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear(Color::White);

		window.draw(sprite);

		window.display();
	}
}