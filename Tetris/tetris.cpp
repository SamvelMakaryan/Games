#include <SFML/Graphics.hpp>
#include <random>
#include <array>

#include "Tetris.hpp"

int main() {
	constexpr const int cubeSize = 18;
	std::array<Point, 4> currentPosition, previousPosition;
	std::array<std::array<int, width>, height> field {};
	std::array<std::array<int, 4>, 7> figures {{
		{1,3,5,7}, 
		{2,4,5,7}, 
		{3,5,4,6}, 
		{3,5,4,7}, 
		{2,3,5,7}, 
		{3,5,7,6}, 
		{2,3,4,5} 
	}};
	sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris!");
	sf::Image cubesImage;
	sf::Image backgroundImage;
	sf::Image frameImage;
	sf::Texture cubesTexture;
	sf::Texture backgroundTexture;
	sf::Texture frameTexture;
	cubesImage.loadFromFile("images/cubes.png");
	backgroundImage.loadFromFile("images/background.png");
	frameImage.loadFromFile("images/frame.png");
	cubesTexture.loadFromImage(cubesImage);
	backgroundTexture.loadFromImage(backgroundImage);
	frameTexture.loadFromImage(frameImage);
	sf::Sprite cubesSprite(cubesTexture);
	sf::Sprite backgroundSprite(backgroundTexture);
	sf::Sprite frameSprite(frameTexture);
	cubesSprite.setTextureRect(sf::IntRect(0, 0, cubeSize, cubeSize));
	std::random_device rd;
	bool rotate = false; 
	bool start = true; 
	int step = 0; 
	int color = 1; 
	int cubeNumber = rd() % 7;
	float timer = 0.0; 
	float delay = 0.3;
	sf::Clock clock;
	sf::Event event;
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}	
			if (event.type == sf::Event::Resized) {
				sf::FloatRect view(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(view));
			}		
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					rotate = true;
				} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					step = -1;
				} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					step = 1;
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			delay = 0.05;
		}
		for (int i = 0; i < 4; i++) {
			previousPosition[i] = currentPosition[i]; 
			currentPosition[i].x += step; 
		}
		if (!check(field, currentPosition)) {
			for (int i = 0; i < 4; i++) {
				currentPosition[i] = previousPosition[i];
			}
		}
		if (rotate) {
			Point p = currentPosition[1];
			for (int i = 0; i < 4; i++) {
				int x = currentPosition[i].y - p.y; 
				int y = currentPosition[i].x - p.x; 
				currentPosition[i].x = p.x - x;
				currentPosition[i].y = p.y + y;
			}
			if (!check(field, currentPosition)) { 
				for (int i = 0; i < 4; i++) {
					currentPosition[i] = previousPosition[i]; 
				}
			}
		}	
		if (timer > delay) {
			for (int i = 0; i < 4; i++) { 
				previousPosition[i] = currentPosition[i]; 
				currentPosition[i].y += 1; 
			}
			if (!check(field, currentPosition)) {
				for (int i = 0; i < 4; i++) {
					field[previousPosition[i].y][previousPosition[i].x] = color;
				}
				color = 1 + rd() % 7;
				cubeNumber = rd() % 7;
				for (int i = 0; i < 4; i++) {
					currentPosition[i].x = figures[cubeNumber][i] % 2;
					currentPosition[i].y = figures[cubeNumber][i] / 2;
				}
			}
			timer = 0;
		}
		int k = height - 1;
		for (int i = height - 1; i > 0; i--) {
			int count = 0;
			for (int j = 0; j < width; j++) {
				if (field[i][j]) {
					count++;
				}
				field[k][j] = field[i][j];
			}
			if (count < width) {
				k--;
			}
		}
		if (start) {
			start = false;
			cubeNumber = rd() % 7;
			for (int i = 0; i < 4; i++) {
				currentPosition[i].x = figures[cubeNumber][i] % 2;
				currentPosition[i].y = figures[cubeNumber][i] / 2;
			}
		}
		step = 0; 
		rotate = 0; 
		delay = 0.3;
		window.clear(sf::Color::Blue);
		window.draw(backgroundSprite);
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (field[i][j] == 0) {
					continue;
				}
				cubesSprite.setTextureRect(sf::IntRect(field[i][j] * cubeSize, 0, cubeSize, cubeSize));
				cubesSprite.setPosition(j * cubeSize, i * cubeSize);
				cubesSprite.move(28, 31);
				window.draw(cubesSprite);
			}
		}
		for (int i = 0; i < 4; i++) {
			cubesSprite.setTextureRect(sf::IntRect(color * cubeSize, 0, cubeSize, cubeSize));
			cubesSprite.setPosition(currentPosition[i].x * cubeSize, currentPosition[i].y * cubeSize);
			cubesSprite.move(28, 31); 
			window.draw(cubesSprite);
		}
		window.draw(frameSprite);
		window.display();
	}
}
