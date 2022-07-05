#include <SFML/Graphics.hpp>
#include <time.h>

const int HEIGHT = 20; // Height of game field
const int WIDTH = 14; // Width of game field

int field[HEIGHT][WIDTH] = { 0 }; // Setup game field

// Setup of all Tetraminos
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

// Check if we leave a corner lines
bool check()
{
	for (int i = 0; i < 4; i++)
		if (a[i].x < 0 || a[i].x >= WIDTH || a[i].y >= HEIGHT) return 0;
		else if (field[a[i].y][a[i].x]) return 0;

	return 1;
};


int main()
{
	srand(time(0));

	// Create a window
	sf::RenderWindow window(sf::VideoMode(320, 480), "FUCKIN' TETRIS <3");

	// All Textures
	sf::Texture texture, texture_background, texture_frame;
	texture.loadFromFile("Y:\\IT\\C++\\Tetris_SFML\\tiles.png"); // Texture for Tetramino
	texture_background.loadFromFile("Dont forget to add!"); // Texture for background
	texture_frame.loadFromFile("Dont forget to add!"); // Texture for frame

	// Sprite creating
	sf::Sprite sprite(texture), sprite_background(texture_background), sprite_frame(texture_frame);

	// Creating a 18x18 pixels square
	sprite.setTextureRect(sf::IntRect(0, 0, 18, 18));

	// Setup variables
	int horizontalMovement = 0; // Variable for horizontal movement
	bool rotate = 0; // Vairable for rotate
	int colorNum = 1; // Variable for setups a colors
	bool beginGame = true; // Variable for begin game
	int n = rand() % 7;

	// Variables for timer and delay
	float timer = 0, delay = 0.3;

	// Clock / timer
	sf::Clock clock;


	// Main cycle of app
	while (window.isOpen())
	{
		// Setup, convert and restart timer
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		// Event schedule
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Closing window
			if (event.type == sf::Event::Closed)
				window.close();

			// Check keyboard
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Up) rotate = true; // Up button = Rotate
				else if (event.key.code == sf::Keyboard::Left) horizontalMovement = -1; // Left button = Move to the left
				else if (event.key.code == sf::Keyboard::Right) horizontalMovement = 1; // Right button = Move to the right
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) delay = 0.05; // Down button = Increase falling speed

		for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += horizontalMovement; } // Horizontal movement

		// Setup return point
		if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];


		// Rotate
		if (rotate)
		{
			// Setup a rotation point of tetramino
			Point p = a[1];
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y; //y - y0
				int y = a[i].x - p.x; //x - x0
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			// Return point
			if (!check()) { for (int i = 0; i < 4; i++) a[i] = b[i]; }

		}

		// Down movement
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

		// Check vanishing line
		int k = HEIGHT - 1;
		for (int i = HEIGHT - 1; i > 0; i--)
		{
			int count = 0;
			for (int j = 0; j < WIDTH; j++)
			{
				if (field[i][j]) count++;
				field[k][j] = field[i][j];
			}
			if (count < WIDTH) k--;
		}

		// Appearance on the field
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
		horizontalMovement = 0; rotate = 0; delay = 0.3;


		// Drawing
		window.clear(sf::Color::White); // Setup background color as white
		window.draw(sprite_background);
		for (int i = 0; i < HEIGHT; i++)
			for (int j = 0; j < WIDTH; j++)
			{
				if (field[i][j] == 0) continue;
				sprite.setTextureRect(sf::IntRect(field[i][j] * 18, 0, 18, 18));
				sprite.setPosition(j * 18, i * 18);
				sprite.move(28, 31); // ---> OFFSET POSITION <---
				window.draw(sprite);
			}

		for (int i = 0; i < 4; i++)
		{
			// Setup tetramino colors
			sprite.setTextureRect(sf::IntRect(colorNum * 18, 0, 18, 18));

			// Making a new position
			sprite.setPosition(a[i].x * 18, a[i].y * 18);
			sprite.move(28, 31); // ---> OFFSET <---

			// Sprite draw
			window.draw(sprite);
		}
		// Frame draw
		window.draw(sprite_frame);

		// Window draw
		window.display();
	}

	return 0;
}