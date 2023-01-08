#pragma once
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Entity
{
public:
	Entity()
	{
		infected = false;
		rectangleDimension = sf::Vector2f(0, 0);
		rectanglePosition = sf::Vector2f(0, 0);
		rectangleVelocity = sf::Vector2f(0, 0);
		window = sf::Vector2f(0, 0);
		rect = sf::RectangleShape(rectangleDimension);
	}

	Entity(sf::Vector2f rectSize, sf::Vector2f rectPos, sf::Vector2f rectVelo, sf::Vector2f w)
	{
		infected = false;
		rectangleDimension = rectSize;
		rectanglePosition = rectPos;
		rectangleVelocity = sf::Vector2f(0, 0);
		window = sf::Vector2f(w);
		rect = sf::RectangleShape(rectangleDimension);;
	}

	bool getInfected()
	{
		return infected;
	}

	void setInfected(bool status)
	{
		infected = status;
	}

	sf::Vector2f getRectDimension()
	{
		return rectangleDimension;
	}

	void setRectDimension(sf::Vector2f dimension)
	{
		rectangleDimension = dimension;
	}

	sf::Vector2f getRectPosition()
	{
		return rectanglePosition;
	}

	void setRectPosition(sf::Vector2f position)
	{
		rectanglePosition = position;
	}

	sf::Vector2f getRectVelocity()
	{
		return rectangleVelocity;
	}

	void setRectVelocity(sf::Vector2f velocity)
	{
		rectangleVelocity = velocity;
	}

	sf::Vector2f getWindow()
	{
		return window;
	}

	void setWindow(float x, float y)
	{
		window = sf::Vector2f(x, y);
	}

	sf::RectangleShape getRectangle()
	{
		return rect;
	}

	void spawn()
	{
		rect.setSize(rectangleDimension);
		rect.setPosition(rectanglePosition);
		rect.setFillColor(sf::Color::Green);
	}

	void movement()
	{
		if (rectanglePosition.x < 0 || rectanglePosition.x > (window.x - rectangleDimension.x))
		{
			rectangleVelocity.x *= -1;
		}
		else if (rectanglePosition.y < 0 || rectanglePosition.y > (window.y - rectangleDimension.y))
		{
			rectangleVelocity.y *= -1;
		}

		rectanglePosition.x += rectangleVelocity.x;
		rectanglePosition.y += rectangleVelocity.y;

		rect.setPosition(rectanglePosition);
	}

	void collision(Entity otherEntity)
	{
		if (rect.getGlobalBounds().intersects(otherEntity.getRectangle().getGlobalBounds()))
		{
			if (infected == false && otherEntity.getInfected() == true)
			{
				infect();
			}
		}
	}

	void infect()
	{
		setInfected(true);
		rect.setFillColor(sf::Color::Red);
	}

private:
	bool infected;

	sf::Vector2f rectangleDimension;
	sf::Vector2f rectanglePosition;
	sf::Vector2f rectangleVelocity;
	sf::Vector2f window;
	sf::RectangleShape rect;

}; 