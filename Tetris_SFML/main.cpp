#include <SFML/Graphics.hpp>

const int HEIGHT = 20; // Height of game field
const int WIDTH = 10; // Width of game field

int field[HEIGHT][WIDTH] = { 0 }; // Game field

// Setup for tatramino figures
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


int main()
{
	sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");

	// Creating and loading game tetramino texture
	sf::Texture texture;
	texture.loadFromFile("Y:\\IT\\C++\\Tetris_SFML\\tiles.png");

	// Sprite creating
	sf::Sprite sprite(texture);

	// Cutting 18õ18 pixels cube
	sprite.setTextureRect(sf::IntRect(0, 0, 18, 18));

	// Setup Horizontal Movement and rotating
	bool rotate = 0;
	int horizontalMovement = 0;

	// Setup timer and delay
	float timer = 0, delay = 0.3;

	// Setup clock (timer)
	sf::Clock clock;


	// Main cycle of app
	while (window.isOpen())
	{
		// Getting time from begin and convert it to seconds
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		// Schedule of event in cycle
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window event
			if (event.type == sf::Event::Closed)
				window.close();

			// Checking what key was pressed
			if (event.type == sf::Event::KeyPressed)
				// Rotate
				if (event.key.code == sf::Keyboard::Up) rotate = true;
			// Move to the left
				else if (event.key.code == sf::Keyboard::Left) horizontalMovement = -1;
			// Move to the right
				else if (event.key.code == sf::Keyboard::Right) horizontalMovement = 1;
		}

		// Horizontal Movement
		for (int i = 0; i < 4; i++) a[i].x += horizontalMovement;

		// Rotate
		if (rotate)
		{
			Point p = a[1]; // Setup center of rotating
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
		}

		// Falling down tetraminos
		if (timer > delay)
		{
			for (int i = 0; i < 4; i++) a[i].y += 1;
			timer = 0;

		}


		// Setup tetramino type
		int teraminoType = 3;

		// Appearence on the field
		if (a[0].x == 0)
			for (int i = 0; i < 4; i++)
			{
				a[i].x = figures[teraminoType][i] % 2;
				a[i].y = figures[teraminoType][i] / 2;
			}
		horizontalMovement = 0; rotate = 0;

		// Setup background
		window.clear(sf::Color::White);

		for (int i = 0; i < 4; i++)
		{
			// Setup position for eact tetramino piece
			sprite.setPosition(a[i].x * 18, a[i].y * 18);

			// Sprite drawing
			window.draw(sprite);
		}
		// Window drawing
		window.display();
	}

	return 0;
}