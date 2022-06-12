#include <SFML/Graphics.hpp>

int main()
{
	const int Height = 20; // Height of the field
	const int Width = 10; // Width of the field

	int field[Height][Width] = { 0 }; // Game field

	// Massive of figures
	int figures[7][4] =
	{
		1,3,5,7, // 1
		2,4,5,7, // 2
		3,5,4,6, // 3
		3,5,4,7, // 4
		2,3,5,7, // 5
		3,5,7,6, // 6
		2,3,4,5, // 7
	};

	struct Point
	{
		int x, y;
	} a[4],b[4];

	// Main Window
	sf::RenderWindow window(sf::VideoMode(320, 480), "The Game!");

	// Create and Load Texture
	sf::Texture texture;
	texture.loadFromFile("Y:\\IT\\C++\\Tetris_SFML\\tiles.png");

	// Create a sprite
	sf::Sprite sprite(texture);

	// Cutting box from sprite
	sprite.setTextureRect(sf::IntRect(0, 0, 18, 18));

	// Main Cycle (Work, while window is open)
	while (window.isOpen())
	{
		// Handling events in a cycle
		sf::Event event;
		while (window.pollEvent(event))
		{
			// If user want to close window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		int n = 3;// ZADAEM TIP TETRAMINO

		for (int i = 0; i < 4; i++)
		{
			a[i].x = figures[n][i] % 2;
			a[i].y = figures[n][i] / 2;
		}

		// Setup background color (White)
		window.clear(sf::Color::White);

		for (int i = 0; i < 4; i++)
		{
			// Setup position for all tetraminos
			sprite.setPosition(a[i].x * 18, a[i].y * 18);
			// Sprite draw
			window.draw(sprite);
		}
		// Window Render
		window.display();
	}
	return 0;
}