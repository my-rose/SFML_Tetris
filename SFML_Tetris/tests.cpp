#include <SFML\Graphics.hpp>

using namespace sf;

int not_main()
{
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(200, 400), "SFML Works!");

	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// тогда закрываем его
				window.close();
		}
		// Задаем цвет фона
		window.clear(Color(250, 220, 100, 0));

		CircleShape circle(50);
		circle.setFillColor(Color(10, 100, 200));
		window.draw(circle);
		circle.move(100, 0);
		window.draw(circle);

		RectangleShape rectangle(Vector2f(74, 284));
		rectangle.setFillColor(Color(10, 100, 200));
		rectangle.move(63, 30);
		window.draw(rectangle);

		Texture texture;
		texture.loadFromFile("C:\\resurses\\cat.jpg");
		Sprite sprite(texture);
		window.draw(sprite);

		// Отрисовка окна	
		window.display();
	}

	return 0;
}