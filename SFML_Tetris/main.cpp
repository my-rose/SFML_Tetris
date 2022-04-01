#include <SFML\Graphics.hpp>
#include <time.h>
#include <iostream>



using namespace sf;

const int M = 20; // высота игрового поля
const int N = 10; // ширина игрового поля

int field[M][N] = { 0 }; // игровое поле

// Массив фигурок-тетрамино
int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

struct Point
{
	int x, y;
} a[4], b[4];

bool check()
{
	for (int i = 0; i < 4; i++)
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
		else if (field[a[i].y][a[i].x]) return 0;

	return 1;
}


int main()
{
	RenderWindow window(VideoMode(320, 480), "The Game!");
	srand(time(0));

	// Создание и загрузка текстуры
	Texture texture;
	texture.loadFromFile("C:\\Users\\Леночка\\source\\repos\\SFML_Tetris\\images\\tiles.png");

	// Создание спрайта
	Sprite sprite(texture);

	// Вырезаем из спрайта отдельный квадратик размером 18х18 пикселей
	sprite.setTextureRect(IntRect(0, 0, 18, 18));

	// Переменные для горизонтального перемещения и вращения
	int dx = 0; bool rotate = 0;
	int colorNum = 1; // цвет
	bool beginGame = true;
	int n = rand() % 7;

	// Переменные для таймера и задержки
	float timer = 0, delay = 0.3;

	// Часы (таймер)
	Clock clock;


	// Главный цикл приложения. Выполняется, пока открыто окно.
	while (window.isOpen())
	{
		// Получаем время, прошедшее с начала отсчета, и конвертируем его в секунды
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет окно закрыть?
			if (event.type == Event::Closed)
				// тогда закрываем его
				window.close();

			// Была нажата кнопка на клавиатуре?
			if (event.type == Event::KeyPressed)
				// Эта кнопка – стрелка вверх?…
				if (event.key.code == Keyboard::Up) rotate = true;
			//…или же стрелка влево?…
				else if (event.key.code == Keyboard::Left) dx = -1;
			////…ну тогда может это стрелка вправо?
				else if (event.key.code == Keyboard::Right) dx = 1;
				else if (event.key.code == Keyboard::T) std::cout << "Working!";
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;

		// Горизонтальное перемещение
		for (int i = 0; i < 4; i++) {
			b[i] = a[i];
			a[i].x += dx;
		}

		// Если вышли за пределы поля после перемещения, то возвращаем старые координаты
		if (!check()) {
			for (int i = 0; i < 4; i++)
				a[i] = b[i];
		}

		// Вращение
		if (rotate)
		{
			Point p = a[1]; // указываем центр вращения
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y; //y-y0
				int y = a[i].x - p.x; //x-x0
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}

			// Если вышли за пределы поля после поворота, то возвращаем старые координаты 
			if (!check()) {
				for (int i = 0; i < 4; i++)
					a[i] = b[i];
			}
		}

		// Движение тетрамино вниз (Тик таймера)
		if (timer > delay)
		{
			for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }
			if (!check())
			{
				for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum;
				colorNum = 1 + rand() % 7;
				n = rand() % 7;
				for (int i = 0; i < 4; i++)
				{
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}

			}
			timer = 0;

		}

		// Первое появление тетрамино на поле?
		if (beginGame)
		{
			beginGame = false;
			n = rand() % 7;
			for (int i = 0; i < 4; i++)
			{
				a[i].x = figures[n][i] % 2;
				a[i].y = figures[n][i] / 2;
			}
		}
		dx = 0; rotate = 0; delay = 0.3;

		// Указываем цвет фона - белый
		window.clear(Color::White);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			{
				if (field[i][j] == 0) continue;
				sprite.setPosition(j * 18, i * 18);
				window.draw(sprite);
			}
	}

	return 0;
}