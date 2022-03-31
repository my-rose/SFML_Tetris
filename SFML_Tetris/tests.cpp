#include <SFML\Graphics.hpp>

using namespace sf;

int not_main()
{
	// ������, �������, ����������, �������� ������� ����� ����������
	RenderWindow window(VideoMode(200, 400), "SFML Works!");

	// ������� ���� ����������. �����������, ���� ������� ����
	while (window.isOpen())
	{
		// ������������ ������� ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			// ������������ ����� �� �������� � ����� ������� ����?
			if (event.type == Event::Closed)
				// ����� ��������� ���
				window.close();
		}
		// ������ ���� ����
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

		// ��������� ����	
		window.display();
	}

	return 0;
}