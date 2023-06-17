#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include <Windows.h>

using namespace std;

class Credits
{
public:
	Credits();
	~Credits();
	void CreditsMenu();
	sf::RenderWindow uwindow;
private:
	sf::Texture background;
	sf::Sprite ubackground;
};

int CreditsScreen()
{
	Credits credits;
	credits.CreditsMenu();
	return 0;
}

Credits::Credits() :uwindow(sf::VideoMode(800, 600), "Gidaman!")
{
	background.loadFromFile("credits background.png");
	ubackground.setTexture(background);
}

Credits::~Credits()
{

}

void Credits::CreditsMenu()
{
	while (uwindow.isOpen())
	{
		sf::Event evnt;
		while (uwindow.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				uwindow.close();
		}
		uwindow.clear();
		uwindow.draw(ubackground);
		uwindow.display();
	}
}