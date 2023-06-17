#include <SFML/Graphics.hpp>
#include "Game.cpp"
#include "Help Screen.h"
#include "StoryBoard.h"
#include "Credits.h"

constexpr auto MAX_NUMBER_OF_ITEMS = 5;

class Menu
{
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Texture texturebackground;
	sf::Sprite background;
public:
	Menu(float width, float height);
	~Menu();
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int getPressedItem() { return selectedItemIndex; };
};

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("CARTOON FREE.ttf"))
	{
		// handle error
	}
	if (!texturebackground.loadFromFile("MainMenu.png"))
	{
		// handle error
	}

	background.setTexture(texturebackground);

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setCharacterSize(35);
	menu[0].setPosition(350, 300);

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::Yellow);
	menu[1].setString("Storyboard");
	menu[1].setCharacterSize(35);
	menu[1].setPosition(350, 350);

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::Yellow);
	menu[2].setString("Help");
	menu[2].setCharacterSize(35);
	menu[2].setPosition(350, 400);

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::Yellow);
	menu[3].setString("Credits");
	menu[3].setCharacterSize(35);
	menu[3].setPosition(350, 450);

	menu[4].setFont(font);
	menu[4].setFillColor(sf::Color::Yellow);
	menu[4].setString("Exit");
	menu[4].setCharacterSize(35);
	menu[4].setPosition(350, 500);

	selectedItemIndex = 0;
}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow &mWindow)
{
	mWindow.draw(background);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		mWindow.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

int main() {
	sf::RenderWindow mWindow(sf::VideoMode(800, 600), "GidaMAN!");
	Menu menu(mWindow.getSize().x, mWindow.getSize().y);

	sf::SoundBuffer sMenu;
	sf::Sound soundm;
	sMenu.loadFromFile("menu.ogg");
	soundm.setBuffer(sMenu);
	soundm.play();
	soundm.setLoop(true);

	while (mWindow.isOpen())
	{
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;
				case sf::Keyboard::Down:
					menu.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (menu.getPressedItem())
					{
					case 0:
						soundm.stop();
						startgame();
						break;
					case 1:
						soundm.play();
						StoryBoardScreen();
						break;
					case 2:
						soundm.play();
						HelpScreen();
						break;
					case 3:
						soundm.play();
						CreditsScreen();
						break;
					case 4:
						soundm.play();
						mWindow.close();
						break;
					}
					break;
				}
				break;
			case sf::Event::Closed:
				mWindow.close();
				break;
			}
		}
		mWindow.clear();
		menu.draw(mWindow);
		mWindow.display();
	}
	return 0;
}


