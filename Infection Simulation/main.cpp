#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


#include "Entity.h"

sf::Vector2f randPosNum(float xWindow, float yWindow, sf::Vector2f dimension)
{
	float xRandom = rand() % (static_cast<unsigned int>(xWindow - dimension.x));
	float yRandom = rand() % (static_cast<unsigned int>(yWindow - dimension.y));
	sf::Vector2f temp(xRandom, yRandom);
	return temp;
}

sf::Vector2f randVeloNum()
{
	float xRandom = rand() % (2 - (-2));
	float yRandom = rand() % (2 - (-2));
	sf::Vector2f temp(xRandom, yRandom);
	return temp;
}

int main()
{
	std::cout << "SFML active" << std::endl; 

	//random number generator
	srand(time(0));

	//window attributes
	float xWindow = 800;
	float yWindow = 600;

	//setup window
	sf::RenderWindow window(sf::VideoMode(xWindow, yWindow), "My Window");
	window.setFramerateLimit(60);

	std::vector <Entity> entity;
	entity.reserve(5);
	entity.resize(5);
	sf::Vector2f rectDim(25, 25);

	int population = 75;

	for (int i = 0; i < population; i++)
	{
		sf::Vector2f rectPos = randPosNum(xWindow, yWindow, rectDim);
		sf::Vector2f rectVelo = randVeloNum();
		Entity temp;
		entity.push_back(temp);
		entity[i].setWindow(xWindow, yWindow);
		entity[i].setRectDimension(rectDim);
		entity[i].setRectPosition(rectPos);
		entity[i].setRectVelocity(rectVelo);
		entity[i].spawn();
	}

	entity[0].infect();

	

	//frame loop
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					std::cout << "SFML unactive" << std::endl;
				}
			}

			//render
			window.clear(sf::Color::Black);
			
			for (int j = 0; j < population; j++)
			{
				for (int k = 0; k < population; k++)
				{
					if (k == j)
					{
						continue;
					}
					entity[j].collision(entity[k]);
				}
			}

			for (int l = 0; l < population; l++)
			{
				entity[l].movement();
				window.draw(entity[l].getRectangle());
			}
			window.display();
		}

		return 0;
}