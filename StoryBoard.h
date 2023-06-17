#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include <Windows.h>

using namespace std;

class StoryBoard
{
public:
	StoryBoard();
	~StoryBoard();
	void StoryBoardMenu();
	sf::RenderWindow twindow;
private:
	sf::Texture background;
	sf::Sprite tbackground;
};

int StoryBoardScreen()
{
	StoryBoard storyboard;
	storyboard.StoryBoardMenu();
	return 0;
}

StoryBoard::StoryBoard() :twindow(sf::VideoMode(800, 600), "Gidaman!")
{
	background.loadFromFile("storyboardbackground.png");
	tbackground.setTexture(background);
}

StoryBoard::~StoryBoard()
{

}

void StoryBoard::StoryBoardMenu()
{
	while (twindow.isOpen())
	{
		sf::Event evnt;
		while (twindow.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				twindow.close();
		}
		twindow.clear();
		twindow.draw(tbackground);
		twindow.display();
	}
}