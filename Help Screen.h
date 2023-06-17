#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include <Windows.h>

using namespace std;

class Help
{
public:
	Help();
	~Help();
	void HelpMenu();
	sf::RenderWindow swindow;
private:
	sf::Texture background;
	sf::Sprite sbackground;
};

int HelpScreen() 
{
	Help help;
	help.HelpMenu();
	return 0;
}

Help::Help() :swindow(sf::VideoMode(800, 600), "Gidaman!")
{
	background.loadFromFile("helpbuttonscreen.png");
	sbackground.setTexture(background);
}

Help::~Help()
{

}

void Help::HelpMenu()
{
	while (swindow.isOpen())
	{
		sf::Event evnt;
		while (swindow.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				swindow.close();
		}
		swindow.clear();
		swindow.draw(sbackground);
		swindow.display();
	}
}