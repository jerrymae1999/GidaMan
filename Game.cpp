#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>
//#include "Help Screen.h"
#include "player.h"
#include "entity.h"
#include "projectile.h"
#include "enemy.h"
#include "random.h"
#include "pickup.h"
#include "wall.h"

using namespace std;


inline int startgame()
{
	//Variables
	srand(time(NULL));
	sf::Clock clock; // player missles
	sf::Clock clock2; // enemy1 missles
	sf::Clock clock3; // enemy2 missles
	sf::Clock clock4; // enemy3 missles
	sf::Clock clock5; // enemy4 missles
	sf::Clock clock6; // Player takes damage from enemy
	sf::Clock clock7; // Player takes damage from enemy2
	sf::Clock clock8; // Player takes damage from enemy3
	sf::Clock clock9; // Player takes damage from enemy4

	int counter = 0;
	int counter2 = 0;
	int counter3 = 0;
	bool flag = false;

	//Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Play GidaMan");
	window.setFramerateLimit(100);

	//View
	sf::View view1(sf::FloatRect(200, 200, 300, 300));
	view1.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	view1.setCenter(sf::Vector2f(view1.getSize().x / 2, view1.getSize().y));
	window.setView(view1);

	//Load Player sprite to display
	sf::Texture texturePlayer;
	if (!texturePlayer.loadFromFile("lucy.png")) {
		return EXIT_FAILURE;
	}

	//Load Enemy sprite to display
	sf::Texture textureEnemy;
	if (!textureEnemy.loadFromFile("white-lady.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture textureEnemy2;
	if (!textureEnemy2.loadFromFile("manananggal.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture textureEnemy3;
	if (!textureEnemy3.loadFromFile("serena.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture textureEnemy4;
	if (!textureEnemy4.loadFromFile("dewende.png")) {
		return EXIT_FAILURE;
	}

	//Load Token
	sf::Texture textureDream;
	if (!textureDream.loadFromFile("dreamcatcher.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture textureHeart;
	if (!textureHeart.loadFromFile("heart.png")) {
		return EXIT_FAILURE;
	}

	//Magic Ball shooting 
	sf::Texture textureMagicBall;
	if (!textureMagicBall.loadFromFile("magic.png")) {
		return EXIT_FAILURE;
	}

	//Load Things
	sf::Texture textureCrate;
	if (!textureCrate.loadFromFile("crate.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture textureTree1;
	if (!textureTree1.loadFromFile("tree1.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture textureTree2;
	if (!textureTree2.loadFromFile("tree2.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture textureRock1;
	if (!textureRock1.loadFromFile("rock1.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture textureRock2;
	if (!textureRock2.loadFromFile("rock2.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture textureRock3;
	if (!textureRock3.loadFromFile("rock3.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture textureGrass;
	if (!textureGrass.loadFromFile("grass.png")) {
		return EXIT_FAILURE;
	}

	//Load Wall
	sf::Texture textureWall;
	if (!textureWall.loadFromFile("wall.png")) {
		return EXIT_FAILURE;
	}

	//Load Floor
	sf::Texture textureFloor;
	if (!textureFloor.loadFromFile("floor.png")) {
		return EXIT_FAILURE;
	}

	sf::Sprite spritePlayer(texturePlayer);
	spritePlayer.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	spritePlayer.setTextureRect(sf::IntRect(0, 0, 40, 40));

	//Create graphical text to display
	sf::Font font;
	if (!font.loadFromFile("gil.ttf"))
	{
		return EXIT_FAILURE;
	}

	//Player Score Text
	sf::Text text("SCORE:", font, 25);
	text.setFillColor(sf::Color::Yellow);
	text.setPosition(0, 0);

	//Player HP Text
	sf::Text textHP("HP:", font, 25);
	textHP.setFillColor(sf::Color::Green);
	textHP.setPosition(0, 0);

	//Gameover
	sf::Text textgameOver("GAME OVER", font, 75);

	//You Win
	sf::Text textyouWin("YOU WIN!", font, 75);

	//Load to play music
	sf::Music music;
	if (!music.openFromFile("music.ogg"))
	{
		return EXIT_FAILURE;
	}

	//Play music
	music.play();
	music.setLoop(true);

	//Sound Effects
	sf::SoundBuffer bufferPlayershot;
	if (!bufferPlayershot.loadFromFile("playershot.ogg"))
		return -1;
	sf::Sound soundPlayershot;
	soundPlayershot.setBuffer(bufferPlayershot);

	//Sound Effects for wall collision
	sf::SoundBuffer bufferCollision;
	if (!bufferCollision.loadFromFile("collide.ogg"))
		return -1;
	sf::Sound soundCollision;
	soundCollision.setBuffer(bufferCollision);

	//Sound Effects for the enemy,'s shot
	sf::SoundBuffer bufferEnemy;
	if (!bufferEnemy.loadFromFile("enemy.ogg"))
		return -1;
	sf::Sound soundEnemy;
	soundEnemy.setBuffer(bufferEnemy);


	//Sound Effects for getting the heart
	sf::SoundBuffer bufferHeart;
	if (!bufferHeart.loadFromFile("heart.ogg"))
		return -1;
	sf::Sound soundHeart;
	soundHeart.setBuffer(bufferHeart);


	/*// Sound Effects for getting the dream catcher*/

	sf::SoundBuffer bufferDream;
	if (!bufferDream.loadFromFile("dream.ogg"))
		return -1;
	sf::Sound soundDream;
	soundDream.setBuffer(bufferDream);

	//Sound Effects for colliding with the enemy
	sf::SoundBuffer bufferEnemycollision;
	if (!bufferEnemycollision.loadFromFile("Enemycollision.ogg"))
		return -1;
	sf::Sound soundEnemycollision;
	soundEnemycollision.setBuffer(bufferEnemycollision);

	//Sound Effects for game over
	sf::SoundBuffer bufferGameover;
	if (!bufferGameover.loadFromFile("GameOver.ogg"))
		return -1;
	sf::Sound soundGameover;
	soundGameover.setBuffer(bufferGameover);

	//Sound Effects for Success
	sf::SoundBuffer bufferSuccess;
	if (!bufferSuccess.loadFromFile("success.ogg"))
		return -1;
	sf::Sound soundSuccess;
	soundSuccess.setBuffer(bufferSuccess);



	//Class Object
	class player Player1;
	Player1.sprite.setTexture(texturePlayer);

	//Projectile Vector Array
	vector<projectile>::const_iterator iter;
	vector<projectile> projectileArray;

	//Projectile Object
	class projectile projectile1;
	projectile1.sprite.setTexture(textureMagicBall);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Enemy Vector Array
	vector<enemy>::const_iterator iter4;
	vector<enemy> enemyArray;

	//Enemy Object
	class enemy enemy1;
	enemy1.sprite.setTexture(textureEnemy);
	enemy1.text.setFont(font);
	enemy1.text.setCharacterSize(15);
	enemy1.text.setFillColor(sf::Color::Red);

	enemy1.rect.setPosition(600, 200);

	//Enemy2
	vector<enemy>::const_iterator iter5;
	vector<enemy> enemy2Array;

	//Enemy Object
	class enemy enemy2;
	enemy2.sprite2.setTexture(textureEnemy2);
	enemy2.text.setFont(font);
	enemy2.text.setCharacterSize(16);
	enemy2.text.setFillColor(sf::Color::Red);

	enemy2.rect.setPosition(100, 400);

	//Enemy3
	vector<enemy>::const_iterator iter6;
	vector<enemy> enemy3Array;

	//Enemy Object
	class enemy enemy3;
	enemy3.sprite3.setTexture(textureEnemy3);
	enemy3.text.setFont(font);
	enemy3.text.setCharacterSize(16);
	enemy3.text.setFillColor(sf::Color::Red);

	enemy3.rect.setPosition(500, 200);

	//Enemy4
	vector<enemy>::const_iterator iter7;
	vector<enemy> enemy4Array;

	//Enemy Object
	class enemy enemy4;
	enemy4.sprite4.setTexture(textureEnemy4);
	enemy4.text.setFont(font);
	enemy4.text.setCharacterSize(16);
	enemy4.text.setFillColor(sf::Color::Red);

	enemy4.rect.setPosition(200, 200);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Dream Vector Array
	vector<pickup>::const_iterator iter11;
	vector<pickup> pickupArray;

	//Dream object
	class pickup pickup1;
	pickup1.sprite.setTexture(textureDream);

	//Heart Vector Array
	vector<pickup>::const_iterator iter12;
	vector<pickup> pickup2Array;

	//Heart object
	class pickup pickup2;
	pickup2.sprite.setTexture(textureHeart);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Wall verctor Array
	vector<wall>::const_iterator iter15;
	vector<wall> wallArray;

	//wall Object
	class wall wall1;
	wall1.sprite.setTexture(textureWall);

	//crate verctor Array
	vector<wall>::const_iterator iter20;
	vector<wall> crateArray;

	//crate Object
	class wall crate1;
	crate1.sprite.setTexture(textureCrate);

	//Tree1 verctor Array
	vector<wall>::const_iterator iter30;
	vector<wall> tree1Array;

	//Tree1 Object
	class wall tree1;
	tree1.sprite.setTexture(textureTree1);

	//Tree2 verctor Array
	vector<wall>::const_iterator iter31;
	vector<wall> tree2Array;

	//Tree2 Object
	class wall tree2;
	tree2.sprite.setTexture(textureTree2);

	//Rock1 verctor Array
	vector<wall>::const_iterator iter32;
	vector<wall> rock1Array;

	//Rock1 Object
	class wall rock1;
	rock1.sprite.setTexture(textureRock1);

	//Rock2 verctor Array
	vector<wall>::const_iterator iter33;
	vector<wall> rock2Array;

	//Rock2 Object
	class wall rock2;
	rock2.sprite.setTexture(textureRock2);

	//Rock3 verctor Array
	vector<wall>::const_iterator iter34;
	vector<wall> rock3Array;

	//Rock3 Object
	class wall rock3;
	rock3.sprite.setTexture(textureRock3);

	//grass verctor Array
	vector<wall>::const_iterator iter35;
	vector<wall> grassArray;

	//grass Object
	class wall grass1;
	grass1.sprite.setTexture(textureGrass);

	//floor verctor Array
	vector<wall>::const_iterator iter25;
	vector<wall> floorArray;

	//floor Object
	class wall floor1;
	floor1.sprite.setTexture(textureFloor);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	int roomSize = generateRandom(10) + 3;
	int verticalDoorLocationRight = 0;
	int verticalDoorLocationLeft = 0;
	int horizontalDoorLocationUp = 0;
	int horizontalDoorLocationDown = 0;
	int roomStartX = 0;
	int roomStartY = 0;


	//Custom Room1
	roomSize = 10;
	verticalDoorLocationRight = 3;
	verticalDoorLocationLeft = 100;
	horizontalDoorLocationUp = 100;
	horizontalDoorLocationDown = 100;
	roomStartX = 0;
	roomStartY = 0;
	wall1.destructable = false; //can't be destroyed 
	wall1.sprite.setTexture(textureWall);

	//Lay Floor Tiles
	counter = 0;
	while (counter <= roomSize)
	{
		counter2 = 0;
		while (counter2 <= roomSize)
		{
			floor1.sprite.setPosition(50 * counter + roomStartX, 50 * counter2 + roomStartY);
			floorArray.push_back(floor1);

			counter2++;
		}

		counter++;
	}

	//Create horizontal Wall
	counter = 0;
	while (counter < roomSize)
	{
		if (counter != horizontalDoorLocationUp)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(50 * counter + roomStartX, roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}

		counter++;
	}

	//Create horizontal2 Wall
	counter = 0;
	while (counter < roomSize)
	{
		if (counter != horizontalDoorLocationDown)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(50 * counter + roomStartX, 50 * roomSize + roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}

		counter++;
	}

	//Create vertical Wall
	counter = 0;
	while (counter < roomSize)
	{
		if (counter != verticalDoorLocationLeft)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(0 + roomStartX, 50 * counter + roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}

		counter++;
	}

	//Create vertical2 Wall
	counter = 0;
	while (counter < roomSize + 1)
	{
		if (counter != verticalDoorLocationRight)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(50 * roomSize + roomStartX, 50 * counter + roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}

		counter++;
	}

	// Random Stuffs in the Room
	counter = 0;
	while (counter < (roomSize - 1))
	{
		counter2 = 0;

		while (counter2 < (roomSize - 1))
		{
			int tempRandom = generateRandom(30);
			if (tempRandom == 1)
			{
				//Destructable boxes
				crate1.destructable = true; //can be destroyed 
				crate1.sprite.setTexture(textureCrate);
				crate1.rect.setSize(sf::Vector2f(50, 50));
				crate1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				crateArray.push_back(crate1);
				crate1.destructable = false;
			}
			if (tempRandom == 2)
			{
				enemy1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemyArray.push_back(enemy1);
			}
			if (tempRandom == 3)
			{
				enemy2.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemy2Array.push_back(enemy2);
			}
			if (tempRandom == 4)
			{
				enemy3.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemy3Array.push_back(enemy3);
			}
			if (tempRandom == 5)
			{
				enemy4.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemy4Array.push_back(enemy4);
			}
			if (tempRandom == 6)
			{
				tree1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				tree1Array.push_back(tree1);
			}
			if (tempRandom == 7)
			{
				tree2.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				tree2Array.push_back(tree2);
			}
			if (tempRandom == 8)
			{
				rock1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				rock1Array.push_back(rock1);
			}
			if (tempRandom == 9)
			{
				rock2.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				rock2Array.push_back(rock2);
			}
			if (tempRandom == 10)
			{
				rock3.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				rock3Array.push_back(rock3);
			}
			if (tempRandom == 11 || tempRandom == 12 || tempRandom == 13 || tempRandom == 14)
			{
				grass1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				grassArray.push_back(grass1);
			}

			counter2++;
		}
		counter++;
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Custom Room 2nd
	roomSize = 15;
	verticalDoorLocationRight = 3;
	verticalDoorLocationLeft = 3;
	horizontalDoorLocationUp = 5;
	horizontalDoorLocationDown = 5;
	roomStartX = 10 * 50;
	roomStartY = 0;
	wall1.destructable = false; //can't be destroyed 

	//Lay Floor Tiles
	counter = 0;
	while (counter <= roomSize)
	{
		counter2 = 0;
		while (counter2 <= roomSize)
		{
			floor1.sprite.setPosition(50 * counter + roomStartX, 50 * counter2 + roomStartY);
			floorArray.push_back(floor1);

			counter2++;
		}

		counter++;
	}

	//Create horizontal Wall
	counter = 0;
	while (counter < roomSize)
	{
		if (counter != horizontalDoorLocationUp)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(50 * counter + roomStartX, roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}
		counter++;
	}

	//Create horizontal2 Wall
	counter = 0;
	while (counter < roomSize)
	{
		if (counter != horizontalDoorLocationDown)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(50 * counter + roomStartX, 50 * roomSize + roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}
		counter++;
	}

	//Create vertical Wall
	counter = 0;
	while (counter < roomSize)
	{
		if (counter != verticalDoorLocationLeft)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(0 + roomStartX, 50 * counter + roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}

		counter++;
	}

	//Create vertical2 Wall
	counter = 0;
	while (counter < roomSize + 1)
	{
		if (counter != verticalDoorLocationRight)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(50 * roomSize + roomStartX, 50 * counter + roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}

		counter++;
	}

	// Random Stuffs in the Room
	counter = 0;
	while (counter < (roomSize - 1))
	{
		counter2 = 0;

		while (counter2 < (roomSize - 1))
		{
			int tempRandom = generateRandom(35);
			if (tempRandom == 1)
			{
				//Destructable boxes
				crate1.destructable = true; //can be destroyed 
				crate1.sprite.setTexture(textureCrate);
				crate1.rect.setSize(sf::Vector2f(50, 50));
				crate1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				crateArray.push_back(crate1);
				crate1.destructable = false;
			}
			if (tempRandom == 2)
			{
				enemy1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemyArray.push_back(enemy1);
			}
			if (tempRandom == 3)
			{
				enemy2.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemy2Array.push_back(enemy2);
			}
			if (tempRandom == 4)
			{
				enemy3.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemy3Array.push_back(enemy3);
			}
			if (tempRandom == 5)
			{
				enemy4.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemy4Array.push_back(enemy4);
			}
			if (tempRandom == 6)
			{
				tree1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				tree1Array.push_back(tree1);
			}
			if (tempRandom == 7)
			{
				tree2.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				tree2Array.push_back(tree2);
			}
			if (tempRandom == 8)
			{
				rock1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				rock1Array.push_back(rock1);
			}
			if (tempRandom == 9)
			{
				rock2.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				rock2Array.push_back(rock2);
			}
			if (tempRandom == 10)
			{
				rock3.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				rock3Array.push_back(rock3);
			}
			if (tempRandom == 11 || tempRandom == 12 || tempRandom == 13 || tempRandom == 14)
			{
				grass1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				grassArray.push_back(grass1);
			}

			counter2++;
		}
		counter++;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Custom Room 3nd
	roomSize = 6;
	verticalDoorLocationRight = 100;
	verticalDoorLocationLeft = 100;
	horizontalDoorLocationUp = 5;
	horizontalDoorLocationDown = 100;
	roomStartX = 10 * 50;
	roomStartY = 15 * 50;
	wall1.destructable = false; //can't be destroyed 

	//Lay Floor Tiles
	counter = 0;
	while (counter <= roomSize)
	{
		counter2 = 0;
		while (counter2 <= roomSize)
		{
			floor1.sprite.setPosition(50 * counter + roomStartX, 50 * counter2 + roomStartY);
			floorArray.push_back(floor1);

			counter2++;
		}

		counter++;
	}

	//Create horizontal Wall
	counter = 0;
	while (counter < roomSize)
	{
		if (counter != horizontalDoorLocationUp)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(50 * counter + roomStartX, roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}
		counter++;
	}

	//Create horizontal2 Wall
	counter = 0;
	while (counter < roomSize)
	{
		if (counter != horizontalDoorLocationDown)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(50 * counter + roomStartX, 50 * roomSize + roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}
		counter++;
	}

	//Create vertical Wall
	counter = 0;
	while (counter < roomSize)
	{
		if (counter != verticalDoorLocationLeft)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(0 + roomStartX, 50 * counter + roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}

		counter++;
	}

	//Create vertical2 Wall
	counter = 0;
	while (counter < roomSize + 1)
	{
		if (counter != verticalDoorLocationRight)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(50 * roomSize + roomStartX, 50 * counter + roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}

		counter++;
	}

	// Random Stuffs in the Room
	counter = 0;
	while (counter < (roomSize - 1))
	{
		counter2 = 0;

		while (counter2 < (roomSize - 1))
		{
			int tempRandom = generateRandom(35);
			if (tempRandom == 1)
			{
				//Destructable boxes
				crate1.destructable = true; //can be destroyed 
				crate1.sprite.setTexture(textureCrate);
				crate1.rect.setSize(sf::Vector2f(50, 50));
				crate1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				crateArray.push_back(crate1);
				crate1.destructable = false;
			}
			if (tempRandom == 2)
			{
				enemy1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemyArray.push_back(enemy1);
			}
			if (tempRandom == 3)
			{
				enemy2.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemy2Array.push_back(enemy2);
			}
			if (tempRandom == 4)
			{
				enemy3.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemy3Array.push_back(enemy3);
			}
			if (tempRandom == 5)
			{
				enemy4.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemy4Array.push_back(enemy4);
			}
			if (tempRandom == 6)
			{
				tree1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				tree1Array.push_back(tree1);
			}
			if (tempRandom == 7)
			{
				tree2.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				tree2Array.push_back(tree2);
			}
			if (tempRandom == 8)
			{
				rock1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				rock1Array.push_back(rock1);
			}
			if (tempRandom == 9)
			{
				rock2.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				rock2Array.push_back(rock2);
			}
			if (tempRandom == 10)
			{
				rock3.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				rock3Array.push_back(rock3);
			}
			if (tempRandom == 11 || tempRandom == 12 || tempRandom == 13 || tempRandom == 14)
			{
				grass1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				grassArray.push_back(grass1);
			}
			counter2++;
		}
		counter++;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Custom Room 4th
	roomSize = 10;
	verticalDoorLocationRight = 100;
	verticalDoorLocationLeft = 100;
	horizontalDoorLocationUp = 5;
	horizontalDoorLocationDown = 5;
	roomStartX = 10 * 50;
	roomStartY = -1 * (10 * 50);
	wall1.destructable = false; //can't be destroyed 

	//Lay Floor Tiles
	counter = 0;
	while (counter <= roomSize)
	{
		counter2 = 0;
		while (counter2 <= roomSize)
		{
			floor1.sprite.setPosition(50 * counter + roomStartX, 50 * counter2 + roomStartY);
			floorArray.push_back(floor1);

			counter2++;
		}

		counter++;
	}

	//Create horizontal Wall
	counter = 0;
	while (counter < roomSize)
	{
		if (counter != horizontalDoorLocationUp)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(50 * counter + roomStartX, roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}
		counter++;
	}

	//Create horizontal2 Wall
	counter = 0;
	while (counter < roomSize)
	{
		if (counter != horizontalDoorLocationDown)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(50 * counter + roomStartX, 50 * roomSize + roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}
		counter++;
	}

	//Create vertical Wall
	counter = 0;
	while (counter < roomSize)
	{
		if (counter != verticalDoorLocationLeft)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(0 + roomStartX, 50 * counter + roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}

		counter++;
	}

	//Create vertical2 Wall
	counter = 0;
	while (counter < roomSize + 1)
	{
		if (counter != verticalDoorLocationRight)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(50 * roomSize + roomStartX, 50 * counter + roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}

		counter++;
	}

	// Random Stuffs in the Room
	counter = 0;
	while (counter < (roomSize - 1))
	{
		counter2 = 0;

		while (counter2 < (roomSize - 1))
		{
			int tempRandom = generateRandom(40);
			if (tempRandom == 1)
			{
				//Destructable boxes
				crate1.destructable = true; //can be destroyed 
				crate1.sprite.setTexture(textureCrate);
				crate1.rect.setSize(sf::Vector2f(50, 50));
				crate1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				crateArray.push_back(crate1);
				crate1.destructable = false;
			}
			if (tempRandom == 2)
			{
				enemy1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemyArray.push_back(enemy1);
			}
			if (tempRandom == 3)
			{
				enemy2.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemy2Array.push_back(enemy2);
			}
			if (tempRandom == 4)
			{
				enemy3.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemy3Array.push_back(enemy3);
			}
			if (tempRandom == 5)
			{
				enemy4.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemy4Array.push_back(enemy4);
			}
			if (tempRandom == 6)
			{
				tree1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				tree1Array.push_back(tree1);
			}
			if (tempRandom == 7)
			{
				tree2.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				tree2Array.push_back(tree2);
			}
			if (tempRandom == 8)
			{
				rock1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				rock1Array.push_back(rock1);
			}
			if (tempRandom == 9)
			{
				rock2.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				rock2Array.push_back(rock2);
			}
			if (tempRandom == 10)
			{
				rock3.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				rock3Array.push_back(rock3);
			}
			if (tempRandom == 11 || tempRandom == 12 || tempRandom == 13 || tempRandom == 14)
			{
				grass1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				grassArray.push_back(grass1);
			}

			counter2++;
		}
		counter++;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Custom Room 5th
	roomSize = 10;
	verticalDoorLocationRight = 100;
	verticalDoorLocationLeft = 3;
	horizontalDoorLocationUp = 100;
	horizontalDoorLocationDown = 100;
	roomStartX = 25 * 50;
	roomStartY = 0;
	wall1.destructable = false; //can't be destroyed 

	//Lay Floor Tiles
	counter = 0;
	while (counter <= roomSize)
	{
		counter2 = 0;
		while (counter2 <= roomSize)
		{
			floor1.sprite.setPosition(50 * counter + roomStartX, 50 * counter2 + roomStartY);
			floorArray.push_back(floor1);

			counter2++;
		}

		counter++;
	}

	//Create horizontal Wall
	counter = 0;
	while (counter < roomSize)
	{
		if (counter != horizontalDoorLocationUp)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(50 * counter + roomStartX, roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}
		counter++;
	}

	//Create horizontal2 Wall
	counter = 0;
	while (counter < roomSize)
	{
		if (counter != horizontalDoorLocationDown)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(50 * counter + roomStartX, 50 * roomSize + roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}
		counter++;
	}

	//Create vertical Wall
	counter = 0;
	while (counter < roomSize)
	{
		if (counter != verticalDoorLocationLeft)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(0 + roomStartX, 50 * counter + roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}

		counter++;
	}

	//Create vertical2 Wall
	counter = 0;
	while (counter < roomSize + 1)
	{
		if (counter != verticalDoorLocationRight)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(50 * roomSize + roomStartX, 50 * counter + roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}

		counter++;
	}

	// Random Stuffs in the Room
	counter = 0;
	while (counter < (roomSize - 1))
	{
		counter2 = 0;

		while (counter2 < (roomSize - 1))
		{
			int tempRandom = generateRandom(20);
			if (tempRandom == 1)
			{
				//Destructable boxes
				crate1.destructable = true; //can be destroyed 
				crate1.sprite.setTexture(textureCrate);
				crate1.rect.setSize(sf::Vector2f(50, 50));
				crate1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				crateArray.push_back(crate1);
				crate1.destructable = false;
			}
			if (tempRandom == 2)
			{
				enemy1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemyArray.push_back(enemy1);
			}
			if (tempRandom == 3)
			{
				enemy2.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemy2Array.push_back(enemy2);
			}
			if (tempRandom == 4)
			{
				enemy3.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemy3Array.push_back(enemy3);
			}
			if (tempRandom == 5)
			{
				enemy4.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemy4Array.push_back(enemy4);
			}
			if (tempRandom == 6)
			{
				tree1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				tree1Array.push_back(tree1);
			}
			if (tempRandom == 7)
			{
				tree2.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				tree2Array.push_back(tree2);
			}
			if (tempRandom == 8)
			{
				rock1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				rock1Array.push_back(rock1);
			}
			if (tempRandom == 9)
			{
				rock2.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				rock2Array.push_back(rock2);
			}
			if (tempRandom == 10)
			{
				rock3.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				rock3Array.push_back(rock3);
			}
			if (tempRandom == 11 || tempRandom == 12 || tempRandom == 13 || tempRandom == 14)
			{
				grass1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				grassArray.push_back(grass1);
			}

			counter2++;
		}
		counter++;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Custom Room 6th
	roomSize = 20;
	verticalDoorLocationRight = 100;
	verticalDoorLocationLeft = 100;
	horizontalDoorLocationUp = 100;
	horizontalDoorLocationDown = 5;
	roomStartX = 10 * 50;
	roomStartY = -1 * (35 * 50);
	wall1.destructable = false; //can't be destroyed 

	//Lay Floor Tiles
	counter = 0;
	while (counter <= roomSize)
	{
		counter2 = 0;
		while (counter2 <= roomSize)
		{
			floor1.sprite.setPosition(50 * counter + roomStartX, 50 * counter2 + roomStartY);
			floorArray.push_back(floor1);

			counter2++;
		}

		counter++;
	}

	//Create horizontal Wall
	counter = 0;
	while (counter < roomSize)
	{
		if (counter != horizontalDoorLocationUp)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(50 * counter + roomStartX, roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}
		counter++;
	}

	//Create horizontal2 Wall
	counter = 0;
	while (counter < roomSize)
	{
		if (counter != horizontalDoorLocationDown)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(50 * counter + roomStartX, 50 * roomSize + roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}
		counter++;
	}

	//Create vertical Wall
	counter = 0;
	while (counter < roomSize)
	{
		if (counter != verticalDoorLocationLeft)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(0 + roomStartX, 50 * counter + roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}

		counter++;
	}

	//Create vertical2 Wall
	counter = 0;
	while (counter < roomSize + 1)
	{
		if (counter != verticalDoorLocationRight)
		{
			wall1.sprite.setTexture(textureWall);
			wall1.rect.setPosition(50 * roomSize + roomStartX, 50 * counter + roomStartY);
			wall1.rect.setSize(sf::Vector2f(50, 50));
			wallArray.push_back(wall1);
		}

		counter++;
	}

	// Random Stuffs in the Room
	counter = 0;
	while (counter < (roomSize - 1))
	{
		counter2 = 0;

		while (counter2 < (roomSize - 1))
		{
			int tempRandom = generateRandom(3);
			if (tempRandom == 1 || tempRandom == 12 || tempRandom == 13 || tempRandom == 14)
			{
				//Destructable boxes
				crate1.destructable = true; //can be destroyed 
				crate1.sprite.setTexture(textureCrate);
				crate1.rect.setSize(sf::Vector2f(50, 50));
				crate1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				crateArray.push_back(crate1);
				crate1.destructable = false;
			}
			if (tempRandom == 2)
			{
				enemy1.rect.setPosition((counter * 50) + 50 + roomStartX, (counter2 * 50) + 50 + roomStartY);
				enemyArray.push_back(enemy1);
			}
			counter2++;
		}
		counter++;
	}


	// BOSS ENEMY
	class enemy enemyBoss;
	enemyBoss.sprite.setTexture(textureEnemy);
	enemyBoss.boss = true;
	enemyBoss.text.setFont(font);
	enemyBoss.text.setCharacterSize(15);
	enemyBoss.text.setFillColor(sf::Color::Red);
	enemyBoss.attackDamage = 15;
	enemyBoss.pissed = true;
	enemyBoss.hp = 150;
	enemyBoss.maxhp = 150;
	enemyBoss.sprite.setColor(sf::Color::Red);
	enemyBoss.rect.setPosition((10 * 50) + 50 + roomStartX, (10 * 50) + 50 + roomStartY);
	enemyArray.push_back(enemyBoss);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//Start the game loop
	while (window.isOpen())
	{
		//Process events
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			//Close window exit
			if (evnt.type == sf::Event::Closed) {
				window.close();
			}

			//Escape pressed exit
			if (evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::Escape) {
				window.close();
			}
		}

		//Clear screen
		window.clear();


		//Clock
		sf::Time elapsed1 = clock.getElapsedTime();
		sf::Time elapsed2 = clock2.getElapsedTime();
		sf::Time elapsed3 = clock3.getElapsedTime();
		sf::Time elapsed4 = clock4.getElapsedTime();
		sf::Time elapsed5 = clock5.getElapsedTime();
		sf::Time elapsed6 = clock6.getElapsedTime();
		sf::Time elapsed7 = clock7.getElapsedTime();
		sf::Time elapsed8 = clock8.getElapsedTime();
		sf::Time elapsed9 = clock9.getElapsedTime();


		//Enemy1 collides with wall
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			counter2 = 0;
			for (iter15 = wallArray.begin(); iter15 != wallArray.end(); iter15++)
			{
				if (enemyArray[counter].rect.getGlobalBounds().intersects(wallArray[counter2].rect.getGlobalBounds()))
				{
					//Hit Wall
					if (enemyArray[counter].direction == 1)//up
					{
						enemyArray[counter].canMoveUp = false;
						enemyArray[counter].rect.move(0, 1);
					}
					else if (enemyArray[counter].direction == 2)//down
					{
						enemyArray[counter].canMoveDown = false;
						enemyArray[counter].rect.move(0, -1);
					}
					else if (enemyArray[counter].direction == 3)//left
					{
						enemyArray[counter].canMoveLeft = false;
						enemyArray[counter].rect.move(1, 0);
					}
					else if (enemyArray[counter].direction == 4)//right
					{
						enemyArray[counter].canMoveRight = false;
						enemyArray[counter].rect.move(-1, 0);
					}
					else
					{

					}
				}

				counter2++;
			}

			counter++;

		}

		//Enemy2 collides with wall
		counter = 0;
		for (iter5 = enemy2Array.begin(); iter5 != enemy2Array.end(); iter5++)
		{
			counter2 = 0;
			for (iter15 = wallArray.begin(); iter15 != wallArray.end(); iter15++)
			{
				if (enemy2Array[counter].rect.getGlobalBounds().intersects(wallArray[counter2].rect.getGlobalBounds()))
				{
					//Hit Wall
					if (enemy2Array[counter].direction == 1)//up
					{
						enemy2Array[counter].canMoveUp = false;
						enemy2Array[counter].rect.move(0, 1);
					}
					else if (enemy2Array[counter].direction == 2)//down
					{
						enemy2Array[counter].canMoveDown = false;
						enemy2Array[counter].rect.move(0, -1);
					}
					else if (enemy2Array[counter].direction == 3)//left
					{
						enemy2Array[counter].canMoveLeft = false;
						enemy2Array[counter].rect.move(1, 0);
					}
					else if (enemy2Array[counter].direction == 4)//right
					{
						enemy2Array[counter].canMoveRight = false;
						enemy2Array[counter].rect.move(-1, 0);
					}
					else
					{

					}
				}

				counter2++;
			}

			counter++;

		}

		//Enemy3 collides with wall
		counter = 0;
		for (iter6 = enemy3Array.begin(); iter6 != enemy3Array.end(); iter6++)
		{
			counter2 = 0;
			for (iter15 = wallArray.begin(); iter15 != wallArray.end(); iter15++)
			{
				if (enemy3Array[counter].rect.getGlobalBounds().intersects(wallArray[counter2].rect.getGlobalBounds()))
				{
					//Hit Wall
					if (enemy3Array[counter].direction == 1)//up
					{
						enemy3Array[counter].canMoveUp = false;
						enemy3Array[counter].rect.move(0, 1);
					}
					else if (enemy3Array[counter].direction == 2)//down
					{
						enemy3Array[counter].canMoveDown = false;
						enemy3Array[counter].rect.move(0, -1);
					}
					else if (enemy3Array[counter].direction == 3)//left
					{
						enemy3Array[counter].canMoveLeft = false;
						enemy3Array[counter].rect.move(1, 0);
					}
					else if (enemy3Array[counter].direction == 4)//right
					{
						enemy3Array[counter].canMoveRight = false;
						enemy3Array[counter].rect.move(-1, 0);
					}
					else
					{

					}
				}

				counter2++;
			}

			counter++;

		}

		//Enemy4 collides with wall
		counter = 0;
		for (iter7 = enemy4Array.begin(); iter7 != enemy4Array.end(); iter7++)
		{
			counter2 = 0;
			for (iter15 = wallArray.begin(); iter15 != wallArray.end(); iter15++)
			{
				if (enemy4Array[counter].rect.getGlobalBounds().intersects(wallArray[counter2].rect.getGlobalBounds()))
				{
					//Hit Wall
					if (enemy4Array[counter].direction == 1)//up
					{
						enemy4Array[counter].canMoveUp = false;
						enemy4Array[counter].rect.move(0, 1);
					}
					else if (enemy4Array[counter].direction == 2)//down
					{
						enemy4Array[counter].canMoveDown = false;
						enemy4Array[counter].rect.move(0, -1);
					}
					else if (enemy4Array[counter].direction == 3)//left
					{
						enemy4Array[counter].canMoveLeft = false;
						enemy4Array[counter].rect.move(1, 0);
					}
					else if (enemy4Array[counter].direction == 4)//right
					{
						enemy4Array[counter].canMoveRight = false;
						enemy4Array[counter].rect.move(-1, 0);
					}
					else
					{

					}
				}

				counter2++;
			}

			counter++;

		}

		//Enemy collides with crates
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			counter2 = 0;
			for (iter20 = crateArray.begin(); iter20 != crateArray.end(); iter20++)
			{
				if (enemyArray[counter].rect.getGlobalBounds().intersects(crateArray[counter2].rect.getGlobalBounds()))
				{
					//Hit Wall
					if (enemyArray[counter].direction == 1)//up
					{
						enemyArray[counter].canMoveUp = false;
						enemyArray[counter].rect.move(0, 1);
					}
					else if (enemyArray[counter].direction == 2)//down
					{
						enemyArray[counter].canMoveDown = false;
						enemyArray[counter].rect.move(0, -1);
					}
					else if (enemyArray[counter].direction == 3)//left
					{
						enemyArray[counter].canMoveLeft = false;
						enemyArray[counter].rect.move(1, 0);
					}
					else if (enemyArray[counter].direction == 4)//right
					{
						enemyArray[counter].canMoveRight = false;
						enemyArray[counter].rect.move(-1, 0);
					}
					else
					{

					}
				}

				counter2++;
			}

			counter++;
		}

		//Enemy2 collides with crates
		counter = 0;
		for (iter5 = enemy2Array.begin(); iter5 != enemy2Array.end(); iter5++)
		{
			counter2 = 0;
			for (iter20 = crateArray.begin(); iter20 != crateArray.end(); iter20++)
			{
				if (enemy2Array[counter].rect.getGlobalBounds().intersects(crateArray[counter2].rect.getGlobalBounds()))
				{
					//Hit Wall
					if (enemy2Array[counter].direction == 1)//up
					{
						enemy2Array[counter].canMoveUp = false;
						enemy2Array[counter].rect.move(0, 1);
					}
					else if (enemy2Array[counter].direction == 2)//down
					{
						enemy2Array[counter].canMoveDown = false;
						enemy2Array[counter].rect.move(0, -1);
					}
					else if (enemy2Array[counter].direction == 3)//left
					{
						enemy2Array[counter].canMoveLeft = false;
						enemy2Array[counter].rect.move(1, 0);
					}
					else if (enemy2Array[counter].direction == 4)//right
					{
						enemy2Array[counter].canMoveRight = false;
						enemy2Array[counter].rect.move(-1, 0);
					}
					else
					{

					}
				}

				counter2++;
			}

			counter++;
		}


		//Enemy3 collides with crates
		counter = 0;
		for (iter6 = enemy3Array.begin(); iter6 != enemy3Array.end(); iter6++)
		{
			counter2 = 0;
			for (iter20 = crateArray.begin(); iter20 != crateArray.end(); iter20++)
			{
				if (enemy3Array[counter].rect.getGlobalBounds().intersects(crateArray[counter2].rect.getGlobalBounds()))
				{
					//Hit Wall
					if (enemy3Array[counter].direction == 1)//up
					{
						enemy3Array[counter].canMoveUp = false;
						enemy3Array[counter].rect.move(0, 1);
					}
					else if (enemy3Array[counter].direction == 2)//down
					{
						enemy3Array[counter].canMoveDown = false;
						enemy3Array[counter].rect.move(0, -1);
					}
					else if (enemy3Array[counter].direction == 3)//left
					{
						enemy3Array[counter].canMoveLeft = false;
						enemy3Array[counter].rect.move(1, 0);
					}
					else if (enemy3Array[counter].direction == 4)//right
					{
						enemy3Array[counter].canMoveRight = false;
						enemy3Array[counter].rect.move(-1, 0);
					}
					else
					{

					}
				}

				counter2++;
			}

			counter++;
		}

		//Enemy4 collides with crates
		counter = 0;
		for (iter7 = enemy4Array.begin(); iter7 != enemy4Array.end(); iter7++)
		{
			counter2 = 0;
			for (iter20 = crateArray.begin(); iter20 != crateArray.end(); iter20++)
			{
				if (enemy4Array[counter].rect.getGlobalBounds().intersects(crateArray[counter2].rect.getGlobalBounds()))
				{
					//Hit Wall
					if (enemy4Array[counter].direction == 1)//up
					{
						enemy4Array[counter].canMoveUp = false;
						enemy4Array[counter].rect.move(0, 1);
					}
					else if (enemy4Array[counter].direction == 2)//down
					{
						enemy4Array[counter].canMoveDown = false;
						enemy4Array[counter].rect.move(0, -1);
					}
					else if (enemy4Array[counter].direction == 3)//left
					{
						enemy4Array[counter].canMoveLeft = false;
						enemy4Array[counter].rect.move(1, 0);
					}
					else if (enemy4Array[counter].direction == 4)//right
					{
						enemy4Array[counter].canMoveRight = false;
						enemy4Array[counter].rect.move(-1, 0);
					}
					else
					{

					}
				}

				counter2++;
			}

			counter++;
		}

		//Player collides with wall
		counter = 0;
		for (iter15 = wallArray.begin(); iter15 != wallArray.end(); iter15++)
		{
			if (Player1.rect.getGlobalBounds().intersects(wallArray[counter].rect.getGlobalBounds()))
			{

				//Hit Wall
				if (Player1.direction == 1)//up
				{
					Player1.canMoveUp = false;
					Player1.rect.move(0, 1);
				}
				else if (Player1.direction == 2)//down
				{
					Player1.canMoveDown = false;
					Player1.rect.move(0, -1);
				}
				else if (Player1.direction == 3)//left
				{
					Player1.canMoveLeft = false;
					Player1.rect.move(1, 0);
				}
				else if (Player1.direction == 4)//right
				{
					Player1.canMoveRight = false;
					Player1.rect.move(-1, 0);
				}
				else
				{
					//nothing happend
				}
			}
			counter++;
		}

		//Player collides with crates
		counter = 0;
		for (iter20 = crateArray.begin(); iter20 != crateArray.end(); iter20++)
		{
			if (Player1.rect.getGlobalBounds().intersects(crateArray[counter].rect.getGlobalBounds()))
			{
				//Hit Wall
				if (Player1.direction == 1)//up
				{
					Player1.canMoveUp = false;
					Player1.rect.move(0, 1);
				}
				else if (Player1.direction == 2)//down
				{
					Player1.canMoveDown = false;
					Player1.rect.move(0, -1);
				}
				else if (Player1.direction == 3)//left
				{
					Player1.canMoveLeft = false;
					Player1.rect.move(1, 0);
				}
				else if (Player1.direction == 4)//right
				{
					Player1.canMoveRight = false;
					Player1.rect.move(-1, 0);
				}
				else
				{
					//nothing happend
				}
			}
			counter++;
		}


		//Player collides with dreamcatcher
		counter = 0;
		for (iter11 = pickupArray.begin(); iter11 != pickupArray.end(); iter11++)
		{
			if (Player1.rect.getGlobalBounds().intersects(pickupArray[counter].rect.getGlobalBounds()))
			{
				soundDream.play();

				if (pickupArray[counter].isToken == true)
				{
					Player1.gil += pickupArray[counter].dreamValue; // gain dreamcatcher
				}
				pickupArray[counter].destroy = true;
			}
			counter++;
		}

		//Player collides with heart
		counter = 0;
		for (iter12 = pickup2Array.begin(); iter12 != pickup2Array.end(); iter12++)
		{
			if (Player1.rect.getGlobalBounds().intersects(pickup2Array[counter].rect.getGlobalBounds()))
			{
				soundHeart.play();

				if (pickup2Array[counter].isToken == true)
				{
					Player1.hp += pickup2Array[counter].heartValue; // gain hp
				}
				pickup2Array[counter].destroy = true;
			}
			counter++;
		}


		//Projectile collides with wall
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			counter2 = 0;
			for (iter15 = wallArray.begin(); iter15 != wallArray.end(); iter15++)
			{
				if (projectileArray[counter].rect.getGlobalBounds().intersects(wallArray[counter2].rect.getGlobalBounds()))
				{
					projectileArray[counter].destroy = true;

					if (wallArray[counter2].destructable == true)
					{
						wallArray[counter2].hp -= Player1.attackDamage;

						if (wallArray[counter2].hp <= 0)
						{
							wallArray[counter2].destroy = true;
						}
					}
				}
				counter2++;
			}
			counter++;
		}

		//Projectile collides with crates
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			counter2 = 0;
			for (iter20 = crateArray.begin(); iter20 != crateArray.end(); iter20++)
			{
				if (projectileArray[counter].rect.getGlobalBounds().intersects(crateArray[counter2].rect.getGlobalBounds()))
				{
					projectileArray[counter].destroy = true;

					if (crateArray[counter2].destructable == true)
					{
						crateArray[counter2].hp -= Player1.attackDamage;

						if (crateArray[counter2].hp <= 0)
						{
							crateArray[counter2].destroy = true;
						}
					}
				}
				counter2++;
			}
			counter++;
		}

		//Enemy Projectile Collides with Player
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			if (projectileArray[counter].enemyProjectile == true)
			{
				if (projectileArray[counter].rect.getGlobalBounds().intersects(Player1.rect.getGlobalBounds()))
				{
					Player1.hp -= projectileArray[counter].attackDamage;

					if (Player1.hp <= 0)
					{
						flag = true;
						textgameOver.setString("GAME OVER");
						textgameOver.setPosition(400, 300);
						textgameOver.setFillColor(sf::Color::Red);
					}

					projectileArray[counter].destroy = true;

				}
			}
			counter++;
		}

		//Enemy2 Projectile Collides with Player
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			if (projectileArray[counter].enemy2Projectile == true)
			{
				if (projectileArray[counter].rect.getGlobalBounds().intersects(Player1.rect.getGlobalBounds()))
				{
					Player1.hp -= projectileArray[counter].attackDamage;

					if (Player1.hp <= 0)
					{
						flag = true;
						textgameOver.setString("GAME OVER");
						textgameOver.setFillColor(sf::Color::Red);
					}

					projectileArray[counter].destroy = true;

				}
			}
			counter++;
		}

		//Enemy3 Projectile Collides with Player
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			if (projectileArray[counter].enemy3Projectile == true)
			{
				if (projectileArray[counter].rect.getGlobalBounds().intersects(Player1.rect.getGlobalBounds()))
				{
					Player1.hp -= projectileArray[counter].attackDamage;

					if (Player1.hp <= 0)
					{
						flag = true;
						textgameOver.setString("GAME OVER");
						textgameOver.setPosition(400, 300);
						textgameOver.setFillColor(sf::Color::Red);
					}

					projectileArray[counter].destroy = true;

				}
			}
			counter++;
		}

		//Enemy4 Projectile Collides with Player
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			if (projectileArray[counter].enemy4Projectile == true)
			{
				if (projectileArray[counter].rect.getGlobalBounds().intersects(Player1.rect.getGlobalBounds()))
				{
					Player1.hp -= projectileArray[counter].attackDamage;

					if (Player1.hp <= 0)
					{
						flag = true;
						textgameOver.setString("GAME OVER");
						textgameOver.setPosition(400, 300);
						textgameOver.setFillColor(sf::Color::Red);
					}

					projectileArray[counter].destroy = true;

				}
			}
			counter++;
		}

		//Enemy Aggro (AI)
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			if (enemyArray[counter].pissed == true)
			{
				if (elapsed2.asSeconds() >= 1)
				{
					clock2.restart();

					int tempRand = generateRandom(3);

					if (tempRand == 1) //Enemy fires and chases at Player
					{
						soundEnemy.play();

						projectile1.attackDamage = enemyArray[counter].attackDamage;

						//Player to right
						if ((Player1.rect.getPosition().x < enemyArray[counter].rect.getPosition().x)
							&& (abs(Player1.rect.getPosition().y - enemyArray[counter].rect.getPosition().y) <= 40))
						{


							projectile1.enemyProjectile = true;
							projectile1.direction = 3;
							projectile1.rect.setPosition(enemyArray[counter].rect.getPosition().x + enemyArray[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2
								, enemyArray[counter].rect.getPosition().y + enemyArray[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectileArray.push_back(projectile1);
							projectile1.enemyProjectile = false;

							enemyArray[counter].direction = 3;

						}

						soundEnemy.play();

						//Player to Left
						if ((Player1.rect.getPosition().x > enemyArray[counter].rect.getPosition().x)
							&& (abs(Player1.rect.getPosition().y - enemyArray[counter].rect.getPosition().y) <= 40))
						{

							projectile1.enemyProjectile = true;
							projectile1.direction = 4;
							projectile1.rect.setPosition(enemyArray[counter].rect.getPosition().x + enemyArray[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2
								, enemyArray[counter].rect.getPosition().y + enemyArray[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectileArray.push_back(projectile1);
							projectile1.enemyProjectile = false;

							enemyArray[counter].direction = 4;
						}
						soundEnemy.play();

						//Player to Top
						if ((Player1.rect.getPosition().y < enemyArray[counter].rect.getPosition().y)
							&& (abs(Player1.rect.getPosition().x - enemyArray[counter].rect.getPosition().x) <= 40))
						{


							projectile1.enemyProjectile = true;
							projectile1.direction = 1;
							projectile1.rect.setPosition(enemyArray[counter].rect.getPosition().x + enemyArray[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2
								, enemyArray[counter].rect.getPosition().y + enemyArray[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectileArray.push_back(projectile1);
							projectile1.enemyProjectile = false;

							enemyArray[counter].direction = 1;
						}
						soundEnemy.play();
						//Player to Bottom
						if ((Player1.rect.getPosition().y > enemyArray[counter].rect.getPosition().y)
							&& (abs(Player1.rect.getPosition().x - enemyArray[counter].rect.getPosition().x) <= 40))
						{


							projectile1.enemyProjectile = true;
							projectile1.direction = 2;
							projectile1.rect.setPosition(enemyArray[counter].rect.getPosition().x + enemyArray[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2
								, enemyArray[counter].rect.getPosition().y + enemyArray[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectileArray.push_back(projectile1);
							projectile1.enemyProjectile = false;

							enemyArray[counter].direction = 2;
						}
					}
					else if (tempRand == 2) //Enemy Chases Player
					{
						if (Player1.rect.getPosition().y < enemyArray[counter].rect.getPosition().y)
						{
							enemyArray[counter].direction = 1;
						}
						else if (Player1.rect.getPosition().y > enemyArray[counter].rect.getPosition().y)
						{
							enemyArray[counter].direction = 2;
						}
						else if (Player1.rect.getPosition().x < enemyArray[counter].rect.getPosition().x)
						{
							enemyArray[counter].direction = 3;
						}
						else if (Player1.rect.getPosition().x > enemyArray[counter].rect.getPosition().x)
						{
							enemyArray[counter].direction = 4;
						}
					}
					else // Enemy Chases player
					{
						if (Player1.rect.getPosition().x < enemyArray[counter].rect.getPosition().x)
						{
							enemyArray[counter].direction = 3;
						}
						else if (Player1.rect.getPosition().x > enemyArray[counter].rect.getPosition().x)
						{
							enemyArray[counter].direction = 4;
						}
						else if (Player1.rect.getPosition().y < enemyArray[counter].rect.getPosition().y)
						{
							enemyArray[counter].direction = 1;
						}
						else if (Player1.rect.getPosition().y > enemyArray[counter].rect.getPosition().y)
						{
							enemyArray[counter].direction = 2;
						}
					}
				}
			}
			counter++;
		}

		//Enemy2 Aggro (AI)
		counter = 0;
		for (iter5 = enemy2Array.begin(); iter5 != enemy2Array.end(); iter5++)
		{
			if (enemy2Array[counter].pissed == true)
			{
				if (elapsed3.asSeconds() >= 1)
				{
					clock3.restart();

					int tempRand = generateRandom(3);

					if (tempRand == 1) //Enemy fires and chases at Player
					{
						soundEnemy.play();
						projectile1.attackDamage = enemy2Array[counter].attackDamage;

						//Player to right
						if ((Player1.rect.getPosition().x < enemy2Array[counter].rect.getPosition().x)
							&& (abs(Player1.rect.getPosition().y - enemy2Array[counter].rect.getPosition().y) <= 40))
						{


							projectile1.enemy2Projectile = true;
							projectile1.direction = 3;
							projectile1.rect.setPosition(enemy2Array[counter].rect.getPosition().x + enemy2Array[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2
								, enemy2Array[counter].rect.getPosition().y + enemy2Array[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectileArray.push_back(projectile1);
							projectile1.enemy2Projectile = false;

							enemy2Array[counter].direction = 3;

						}
						soundEnemy.play();
						//Player to Left
						if ((Player1.rect.getPosition().x > enemy2Array[counter].rect.getPosition().x)
							&& (abs(Player1.rect.getPosition().y - enemy2Array[counter].rect.getPosition().y) <= 40))
						{


							projectile1.enemy2Projectile = true;
							projectile1.direction = 4;
							projectile1.rect.setPosition(enemy2Array[counter].rect.getPosition().x + enemy2Array[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2
								, enemy2Array[counter].rect.getPosition().y + enemy2Array[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectileArray.push_back(projectile1);
							projectile1.enemy2Projectile = false;

							enemyArray[counter].direction = 4;
						}
						soundEnemy.play();
						//Player to Top
						if ((Player1.rect.getPosition().y < enemy2Array[counter].rect.getPosition().y)
							&& (abs(Player1.rect.getPosition().x - enemy2Array[counter].rect.getPosition().x) <= 40))
						{


							projectile1.enemy2Projectile = true;
							projectile1.direction = 1;
							projectile1.rect.setPosition(enemy2Array[counter].rect.getPosition().x + enemy2Array[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2
								, enemy2Array[counter].rect.getPosition().y + enemy2Array[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectileArray.push_back(projectile1);
							projectile1.enemy2Projectile = false;

							enemyArray[counter].direction = 1;
						}
						soundEnemy.play();
						//Player to Bottom
						if ((Player1.rect.getPosition().y > enemy2Array[counter].rect.getPosition().y)
							&& (abs(Player1.rect.getPosition().x - enemy2Array[counter].rect.getPosition().x) <= 40))
						{


							projectile1.enemy2Projectile = true;
							projectile1.direction = 2;
							projectile1.rect.setPosition(enemy2Array[counter].rect.getPosition().x + enemy2Array[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2
								, enemy2Array[counter].rect.getPosition().y + enemy2Array[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectileArray.push_back(projectile1);
							projectile1.enemy2Projectile = false;

							enemyArray[counter].direction = 2;
						}
					}
					else if (tempRand == 2) //Enemy Chases Player
					{
						if (Player1.rect.getPosition().y < enemy2Array[counter].rect.getPosition().y)
						{
							enemy2Array[counter].direction = 1;
						}
						else if (Player1.rect.getPosition().y > enemy2Array[counter].rect.getPosition().y)
						{
							enemy2Array[counter].direction = 2;
						}
						else if (Player1.rect.getPosition().x < enemy2Array[counter].rect.getPosition().x)
						{
							enemy2Array[counter].direction = 3;
						}
						else if (Player1.rect.getPosition().x > enemy2Array[counter].rect.getPosition().x)
						{
							enemy2Array[counter].direction = 4;
						}
					}
					else // Enemy Chases player
					{
						if (Player1.rect.getPosition().x < enemy2Array[counter].rect.getPosition().x)
						{
							enemy2Array[counter].direction = 3;
						}
						else if (Player1.rect.getPosition().x > enemy2Array[counter].rect.getPosition().x)
						{
							enemy2Array[counter].direction = 4;
						}
						else if (Player1.rect.getPosition().y < enemy2Array[counter].rect.getPosition().y)
						{
							enemy2Array[counter].direction = 1;
						}
						else if (Player1.rect.getPosition().y > enemy2Array[counter].rect.getPosition().y)
						{
							enemy2Array[counter].direction = 2;
						}
					}
				}
			}
			counter++;
		}

		//Enemy3 Aggro (AI)
		counter = 0;
		for (iter6 = enemy3Array.begin(); iter6 != enemy3Array.end(); iter6++)
		{
			if (enemy3Array[counter].pissed == true)
			{
				if (elapsed4.asSeconds() >= 1)
				{
					clock4.restart();

					int tempRand = generateRandom(3);

					if (tempRand == 1) //Enemy fires and chases at Player
					{

						projectile1.attackDamage = enemy3Array[counter].attackDamage;
						soundEnemy.play();
						//Player to right
						if ((Player1.rect.getPosition().x < enemy3Array[counter].rect.getPosition().x)
							&& (abs(Player1.rect.getPosition().y - enemy3Array[counter].rect.getPosition().y) <= 40))
						{


							projectile1.enemy3Projectile = true;
							projectile1.direction = 3;
							projectile1.rect.setPosition(enemy3Array[counter].rect.getPosition().x + enemy3Array[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2
								, enemy3Array[counter].rect.getPosition().y + enemy3Array[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectileArray.push_back(projectile1);
							projectile1.enemy3Projectile = false;

							enemy3Array[counter].direction = 3;

						}
						soundEnemy.play();
						//Player to Left
						if ((Player1.rect.getPosition().x > enemy3Array[counter].rect.getPosition().x)
							&& (abs(Player1.rect.getPosition().y - enemy3Array[counter].rect.getPosition().y) <= 40))
						{


							projectile1.enemy3Projectile = true;
							projectile1.direction = 4;
							projectile1.rect.setPosition(enemy3Array[counter].rect.getPosition().x + enemy3Array[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2
								, enemy3Array[counter].rect.getPosition().y + enemy3Array[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectileArray.push_back(projectile1);
							projectile1.enemy3Projectile = false;

							enemy3Array[counter].direction = 4;
						}
						soundEnemy.play();
						//Player to Top
						if ((Player1.rect.getPosition().y < enemy3Array[counter].rect.getPosition().y)
							&& (abs(Player1.rect.getPosition().x - enemy3Array[counter].rect.getPosition().x) <= 40))
						{


							projectile1.enemy3Projectile = true;
							projectile1.direction = 1;
							projectile1.rect.setPosition(enemy3Array[counter].rect.getPosition().x + enemy3Array[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2
								, enemy3Array[counter].rect.getPosition().y + enemy3Array[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectileArray.push_back(projectile1);
							projectile1.enemy3Projectile = false;

							enemy3Array[counter].direction = 1;
						}
						soundEnemy.play();
						//Player to Bottom
						if ((Player1.rect.getPosition().y > enemy3Array[counter].rect.getPosition().y)
							&& (abs(Player1.rect.getPosition().x - enemy3Array[counter].rect.getPosition().x) <= 40))
						{


							projectile1.enemy3Projectile = true;
							projectile1.direction = 2;
							projectile1.rect.setPosition(enemy3Array[counter].rect.getPosition().x + enemy3Array[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2
								, enemy3Array[counter].rect.getPosition().y + enemy3Array[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectileArray.push_back(projectile1);
							projectile1.enemy3Projectile = false;

							enemy3Array[counter].direction = 2;
						}
					}
					else if (tempRand == 2) //Enemy Chases Player
					{
						if (Player1.rect.getPosition().y < enemy3Array[counter].rect.getPosition().y)
						{
							enemy3Array[counter].direction = 1;
						}
						else if (Player1.rect.getPosition().y > enemy3Array[counter].rect.getPosition().y)
						{
							enemy3Array[counter].direction = 2;
						}
						else if (Player1.rect.getPosition().x < enemy3Array[counter].rect.getPosition().x)
						{
							enemy3Array[counter].direction = 3;
						}
						else if (Player1.rect.getPosition().x > enemy3Array[counter].rect.getPosition().x)
						{
							enemy3Array[counter].direction = 4;
						}
					}
					else // Enemy Chases player
					{
						if (Player1.rect.getPosition().x < enemy3Array[counter].rect.getPosition().x)
						{
							enemy3Array[counter].direction = 3;
						}
						else if (Player1.rect.getPosition().x > enemy3Array[counter].rect.getPosition().x)
						{
							enemy3Array[counter].direction = 4;
						}
						else if (Player1.rect.getPosition().y < enemy3Array[counter].rect.getPosition().y)
						{
							enemy3Array[counter].direction = 1;
						}
						else if (Player1.rect.getPosition().y > enemy3Array[counter].rect.getPosition().y)
						{
							enemy3Array[counter].direction = 2;
						}
					}
				}
			}
			counter++;
		}

		//Enemy4 Aggro (AI)
		counter = 0;
		for (iter7 = enemy4Array.begin(); iter7 != enemy4Array.end(); iter7++)
		{
			if (enemy4Array[counter].pissed == true)
			{
				if (elapsed5.asSeconds() >= 1)
				{
					clock5.restart();

					int tempRand = generateRandom(3);

					if (tempRand == 1) //Enemy fires and chases at Player
					{
						soundEnemy.play();
						projectile1.attackDamage = enemy4Array[counter].attackDamage;

						//Player to right
						if ((Player1.rect.getPosition().x < enemy4Array[counter].rect.getPosition().x)
							&& (abs(Player1.rect.getPosition().y - enemy4Array[counter].rect.getPosition().y) <= 40))
						{


							projectile1.enemy4Projectile = true;
							projectile1.direction = 3;
							projectile1.rect.setPosition(enemy4Array[counter].rect.getPosition().x + enemy4Array[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2
								, enemy4Array[counter].rect.getPosition().y + enemy4Array[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectileArray.push_back(projectile1);
							projectile1.enemy4Projectile = false;

							enemy4Array[counter].direction = 3;

						}
						soundEnemy.play();
						//Player to Left
						if ((Player1.rect.getPosition().x > enemy4Array[counter].rect.getPosition().x)
							&& (abs(Player1.rect.getPosition().y - enemy4Array[counter].rect.getPosition().y) <= 40))
						{

							projectile1.enemy4Projectile = true;
							projectile1.direction = 4;
							projectile1.rect.setPosition(enemy4Array[counter].rect.getPosition().x + enemy4Array[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2
								, enemy4Array[counter].rect.getPosition().y + enemy4Array[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectileArray.push_back(projectile1);
							projectile1.enemy4Projectile = false;

							enemy4Array[counter].direction = 4;
						}
						soundEnemy.play();
						//Player to Top
						if ((Player1.rect.getPosition().y < enemy4Array[counter].rect.getPosition().y)
							&& (abs(Player1.rect.getPosition().x - enemy4Array[counter].rect.getPosition().x) <= 40))
						{


							projectile1.enemy4Projectile = true;
							projectile1.direction = 1;
							projectile1.rect.setPosition(enemy4Array[counter].rect.getPosition().x + enemy4Array[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2
								, enemy4Array[counter].rect.getPosition().y + enemy4Array[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectileArray.push_back(projectile1);
							projectile1.enemy4Projectile = false;

							enemy4Array[counter].direction = 1;
						}
						soundEnemy.play();
						//Player to Bottom
						if ((Player1.rect.getPosition().y > enemy4Array[counter].rect.getPosition().y)
							&& (abs(Player1.rect.getPosition().x - enemy4Array[counter].rect.getPosition().x) <= 40))
						{
							projectile1.enemy4Projectile = true;
							projectile1.direction = 2;
							projectile1.rect.setPosition(enemy4Array[counter].rect.getPosition().x + enemy4Array[counter].rect.getSize().x / 2 - projectile1.rect.getSize().x / 2
								, enemy4Array[counter].rect.getPosition().y + enemy4Array[counter].rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectileArray.push_back(projectile1);
							projectile1.enemy4Projectile = false;

							enemy4Array[counter].direction = 2;
						}
					}
					else if (tempRand == 2) //Enemy Chases Player
					{
						if (Player1.rect.getPosition().y < enemy4Array[counter].rect.getPosition().y)
						{
							enemy4Array[counter].direction = 1;
						}
						else if (Player1.rect.getPosition().y > enemy4Array[counter].rect.getPosition().y)
						{
							enemy4Array[counter].direction = 2;
						}
						else if (Player1.rect.getPosition().x < enemy4Array[counter].rect.getPosition().x)
						{
							enemy4Array[counter].direction = 3;
						}
						else if (Player1.rect.getPosition().x > enemy4Array[counter].rect.getPosition().x)
						{
							enemy4Array[counter].direction = 4;
						}
					}
					else // Enemy Chases player
					{
						if (Player1.rect.getPosition().x < enemy4Array[counter].rect.getPosition().x)
						{
							enemy4Array[counter].direction = 3;
						}
						else if (Player1.rect.getPosition().x > enemy4Array[counter].rect.getPosition().x)
						{
							enemy4Array[counter].direction = 4;
						}
						else if (Player1.rect.getPosition().y < enemy4Array[counter].rect.getPosition().y)
						{
							enemy4Array[counter].direction = 1;
						}
						else if (Player1.rect.getPosition().y > enemy4Array[counter].rect.getPosition().y)
						{
							enemy4Array[counter].direction = 2;
						}
					}
				}
			}
			counter++;
		}


		//Enemy collides with Player (Player takes damage)
		if (elapsed6.asSeconds() >= 1)
		{
			clock6.restart();

			counter = 0;

			for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
			{
				soundEnemycollision.play();

				if (Player1.rect.getGlobalBounds().intersects(enemyArray[counter].rect.getGlobalBounds()))
				{
					Player1.hp -= enemyArray[counter].attackDamage;
					if (Player1.hp <= 0)
					{
						flag = true;
						textgameOver.setString("GAME OVER");
						textgameOver.setPosition(400, 300);
						textgameOver.setFillColor(sf::Color::Red);
					}
				}
				counter++;
			}
		}

		//Enemy2 collides with Player (Player takes damage)
		if (elapsed7.asSeconds() >= 0.1)
		{
			clock7.restart();

			counter = 0;

			for (iter5 = enemy2Array.begin(); iter5 != enemy2Array.end(); iter5++)
			{
				soundEnemycollision.play();

				if (Player1.rect.getGlobalBounds().intersects(enemy2Array[counter].rect.getGlobalBounds()))
				{
					Player1.hp -= enemy2Array[counter].attackDamage;
					if (Player1.hp <= 0)
					{
						flag = true;
						textgameOver.setString("GAME OVER");
						textgameOver.setPosition(Player1.rect.getPosition().x - window.getSize().x / 2, Player1.rect.getPosition().y - window.getSize().y / 2 + 50);
						textgameOver.setFillColor(sf::Color::Red);
					}
				}
				counter++;
			}
		}

		//Enemy3 collides with Player (Player takes damage)
		if (elapsed8.asSeconds() >= 0.1)
		{
			clock8.restart();

			counter = 0;

			for (iter6 = enemy3Array.begin(); iter6 != enemy3Array.end(); iter6++)
			{
				soundEnemycollision.play();

				if (Player1.rect.getGlobalBounds().intersects(enemy3Array[counter].rect.getGlobalBounds()))
				{
					Player1.hp -= enemy3Array[counter].attackDamage;
					if (Player1.hp <= 0)
					{
						flag = true;
						textgameOver.setString("GAME OVER");
						textgameOver.setPosition(400, 300);
						textgameOver.setFillColor(sf::Color::Red);
					}
				}
				counter++;
			}
		}

		//Enemy4 collides with Player (Player takes damage)
		if (elapsed9.asSeconds() >= 0.1)
		{
			clock9.restart();

			counter = 0;

			for (iter7 = enemy4Array.begin(); iter7 != enemy4Array.end(); iter7++)
			{
				soundEnemycollision.play();

				if (Player1.rect.getGlobalBounds().intersects(enemy4Array[counter].rect.getGlobalBounds()))
				{
					Player1.hp -= enemy4Array[counter].attackDamage;
					if (Player1.hp <= 0)
					{
						flag = true;
						textgameOver.setString("GAME OVER");
						textgameOver.setPosition(400, 300);
						textgameOver.setFillColor(sf::Color::Red);
					}
				}
				counter++;
			}
		}

		//Projectile Collides with Enemy
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			counter2 = 0;
			for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
			{
				if (projectileArray[counter].rect.getGlobalBounds().intersects(enemyArray[counter2].rect.getGlobalBounds()))
				{
					if (projectileArray[counter].enemyProjectile == false)
					{
						soundCollision.play();

						projectileArray[counter].destroy = true;

						if (enemyArray[counter2].hp == enemyBoss.hp)
						{
							enemyBoss.hp -= Player1.attackDamage;
							if (enemyBoss.hp <= 0)
							{

								enemyArray[counter2].alive = false;
								flag = true;
								textyouWin.setString("YOU WIN!");
								textyouWin.setPosition(400, 300);
								textyouWin.setFillColor(sf::Color::Red);
							}
						}
						else
						{
							enemyArray[counter2].hp -= Player1.attackDamage;
							if (enemyArray[counter2].hp <= 0)
							{
								enemyArray[counter2].alive = false;
							}
						}
						//Aggro
						enemyArray[counter2].pissed = true;
					}
				}
				counter2++;
			}

			counter++;
		}

		//Projectile Collides with Enemy2
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			counter2 = 0;
			for (iter5 = enemy2Array.begin(); iter5 != enemy2Array.end(); iter5++)
			{
				if (projectileArray[counter].rect.getGlobalBounds().intersects(enemy2Array[counter2].rect.getGlobalBounds()))
				{
					if (projectileArray[counter].enemy2Projectile == false)
					{
						soundCollision.play();

						projectileArray[counter].destroy = true;

						enemy2Array[counter2].hp -= Player1.attackDamage;
						if (enemy2Array[counter2].hp <= 0)
						{
							enemy2Array[counter2].alive = false;
						}
						//Aggro
						enemy2Array[counter2].pissed = true;
					}
				}
				counter2++;
			}

			counter++;
		}

		//Projectile Collides with Enemy3
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			counter2 = 0;
			for (iter6 = enemy3Array.begin(); iter6 != enemy3Array.end(); iter6++)
			{
				if (projectileArray[counter].rect.getGlobalBounds().intersects(enemy3Array[counter2].rect.getGlobalBounds()))
				{
					if (projectileArray[counter].enemy3Projectile == false)
					{
						soundCollision.play();

						projectileArray[counter].destroy = true;

						enemy3Array[counter2].hp -= Player1.attackDamage;
						if (enemy3Array[counter2].hp <= 0)
						{
							enemy3Array[counter2].alive = false;
						}
						//Aggro
						enemy3Array[counter2].pissed = true;
					}
				}
				counter2++;
			}

			counter++;
		}

		//Projectile Collides with Enemy4
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			counter2 = 0;
			for (iter7 = enemy4Array.begin(); iter7 != enemy4Array.end(); iter7++)
			{
				if (projectileArray[counter].rect.getGlobalBounds().intersects(enemy4Array[counter2].rect.getGlobalBounds()))
				{
					if (projectileArray[counter].enemy4Projectile == false)
					{
						soundCollision.play();

						projectileArray[counter].destroy = true;

						enemy4Array[counter2].hp -= Player1.attackDamage;
						if (enemy4Array[counter2].hp <= 0)
						{
							enemy4Array[counter2].alive = false;
						}
						//Aggro
						enemy4Array[counter2].pissed = true;
					}
				}
				counter2++;
			}

			counter++;
		}


		//Delete dead enemy
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			if (enemyArray[counter].alive == false)
			{
				//drop token
				if (generateRandom(4) == 1)
				{
					pickup1.rect.setPosition(enemyArray[counter].rect.getPosition());
					pickupArray.push_back(pickup1);
				}

				if (generateRandom(4) == 2)
				{
					pickup2.rect.setPosition(enemyArray[counter].rect.getPosition());
					pickup2Array.push_back(pickup2);
				}

				//BOSS LOOT
				if (enemyArray[counter].boss == true)
				{
					counter3 = 0;
					while (counter3 <= 20)
					{
						pickup1.rect.setPosition(enemyArray[counter].rect.getPosition().x - generateRandom(30)
							, enemyArray[counter].rect.getPosition().y - generateRandom(30));
						pickupArray.push_back(pickup1);
						pickup1.rect.setPosition(enemyArray[counter].rect.getPosition().x + generateRandom(30)
							, enemyArray[counter].rect.getPosition().y + generateRandom(30));
						pickupArray.push_back(pickup1);
						pickup1.rect.setPosition(enemyArray[counter].rect.getPosition().x - generateRandom(30)
							, enemyArray[counter].rect.getPosition().y - generateRandom(30));
						pickupArray.push_back(pickup1);
						pickup1.rect.setPosition(enemyArray[counter].rect.getPosition().x + generateRandom(30)
							, enemyArray[counter].rect.getPosition().y + generateRandom(30));
						pickupArray.push_back(pickup1);

						counter3++;
					}
				}
				enemyArray.erase(iter4);
				break;
			}
			counter++;
		}

		//Delete dead enemy2
		counter = 0;
		for (iter5 = enemy2Array.begin(); iter5 != enemy2Array.end(); iter5++)
		{
			if (enemy2Array[counter].alive == false)
			{
				//drop token
				if (generateRandom(4) == 1)
				{
					pickup1.rect.setPosition(enemy2Array[counter].rect.getPosition());
					pickupArray.push_back(pickup1);
				}

				if (generateRandom(4) == 2)
				{
					pickup2.rect.setPosition(enemyArray[counter].rect.getPosition());
					pickup2Array.push_back(pickup2);
				}
				enemy2Array.erase(iter5);
				break;
			}
			counter++;
		}

		//Delete dead enemy3
		counter = 0;
		for (iter6 = enemy3Array.begin(); iter6 != enemy3Array.end(); iter6++)
		{
			if (enemy3Array[counter].alive == false)
			{
				//drop token
				if (generateRandom(4) == 1)
				{
					pickup1.rect.setPosition(enemy3Array[counter].rect.getPosition());
					pickupArray.push_back(pickup1);
				}

				if (generateRandom(4) == 2)
				{
					pickup2.rect.setPosition(enemyArray[counter].rect.getPosition());
					pickup2Array.push_back(pickup2);
				}
				enemy3Array.erase(iter6);
				break;
			}
			counter++;
		}

		//Delete dead enemy4
		counter = 0;
		for (iter7 = enemy4Array.begin(); iter7 != enemy4Array.end(); iter7++)
		{
			if (enemy4Array[counter].alive == false)
			{
				//drop token
				if (generateRandom(4) == 1)
				{
					pickup1.rect.setPosition(enemy4Array[counter].rect.getPosition());
					pickupArray.push_back(pickup1);
				}

				if (generateRandom(4) == 2)
				{
					pickup2.rect.setPosition(enemyArray[counter].rect.getPosition());
					pickup2Array.push_back(pickup2);
				}
				enemy4Array.erase(iter7);
				break;
			}
			counter++;
		}

		//Delete Projectile
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			if (projectileArray[counter].destroy == true)
			{
				projectileArray.erase(iter);
				break;
			}

			counter++;
		}

		//Delete Dreamcatcher items
		counter = 0;
		for (iter11 = pickupArray.begin(); iter11 != pickupArray.end(); iter11++)
		{
			if (pickupArray[counter].destroy == true)
			{
				pickupArray.erase(iter11);
				break;
			}

			counter++;
		}

		//Delete Heart items
		counter = 0;
		for (iter12 = pickup2Array.begin(); iter12 != pickup2Array.end(); iter12++)
		{
			if (pickup2Array[counter].destroy == true)
			{
				pickup2Array.erase(iter12);
				break;
			}

			counter++;
		}

		//Delete crate
		counter = 0;
		for (iter20 = crateArray.begin(); iter20 != crateArray.end(); iter20++)
		{
			if (crateArray[counter].destroy == true)
			{
				//drop token
				if (generateRandom(4) == 1)
				{
					pickup1.rect.setPosition(crateArray[counter].rect.getPosition());
					pickupArray.push_back(pickup1);
				}

				if (generateRandom(4) == 2)
				{
					pickup2.rect.setPosition(crateArray[counter].rect.getPosition());
					pickup2Array.push_back(pickup2);
				}
				crateArray.erase(iter20);
				break;
			}
			counter++;
		}

		//Fire Missle (Space Bar)
		if (elapsed1.asSeconds() >= 0.1)
		{
			clock.restart();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{

				soundPlayershot.play();

				projectile1.rect.setPosition(Player1.rect.getPosition().x + Player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2
					, Player1.rect.getPosition().y + Player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
				projectile1.direction = Player1.direction;
				projectileArray.push_back(projectile1);
			}
		}

		//Draw Floor
		counter = 0;
		for (iter25 = floorArray.begin(); iter25 != floorArray.end(); iter25++)
		{
			window.draw(floorArray[counter].sprite);

			counter++;
		}


		//Draw Wall
		counter = 0;
		for (iter15 = wallArray.begin(); iter15 != wallArray.end(); iter15++)
		{
			wallArray[counter].update();
			//window.draw(wallArray[counter].rect);
			window.draw(wallArray[counter].sprite);

			counter++;
		}

		//Draw Crate
		counter = 0;
		for (iter20 = crateArray.begin(); iter20 != crateArray.end(); iter20++)
		{
			crateArray[counter].update();
			//window.draw(wallArray[counter].rect);
			window.draw(crateArray[counter].sprite);

			counter++;
		}

		//Draw Dream
		counter = 0;
		for (iter11 = pickupArray.begin(); iter11 != pickupArray.end(); iter11++)
		{
			pickupArray[counter].update();
			//window.draw(pickupArray[counter].rect);
			window.draw(pickupArray[counter].sprite);

			counter++;
		}

		//Draw Heart
		counter = 0;
		for (iter12 = pickup2Array.begin(); iter12 != pickup2Array.end(); iter12++)
		{
			pickup2Array[counter].update();
			//window.draw(pickupArray[counter].rect);
			window.draw(pickup2Array[counter].sprite);

			counter++;
		}

		//Draw tree1
		counter = 0;
		for (iter30 = tree1Array.begin(); iter30 != tree1Array.end(); iter30++)
		{
			tree1Array[counter].update();
			//window.draw(pickupArray[counter].rect);
			window.draw(tree1Array[counter].sprite);

			counter++;
		}

		//Draw tree2
		counter = 0;
		for (iter31 = tree2Array.begin(); iter31 != tree2Array.end(); iter31++)
		{
			tree2Array[counter].update();
			//window.draw(pickupArray[counter].rect);
			window.draw(tree2Array[counter].sprite);

			counter++;
		}

		//Draw rock1
		counter = 0;
		for (iter32 = rock1Array.begin(); iter32 != rock1Array.end(); iter32++)
		{
			rock1Array[counter].update();
			//window.draw(pickupArray[counter].rect);
			window.draw(rock1Array[counter].sprite);

			counter++;
		}

		//Draw rock2
		counter = 0;
		for (iter33 = rock2Array.begin(); iter33 != rock2Array.end(); iter33++)
		{
			rock2Array[counter].update();
			//window.draw(pickupArray[counter].rect);
			window.draw(rock2Array[counter].sprite);

			counter++;
		}

		//Draw rock3
		counter = 0;
		for (iter34 = rock3Array.begin(); iter34 != rock3Array.end(); iter34++)
		{
			rock3Array[counter].update();
			//window.draw(pickupArray[counter].rect);
			window.draw(rock3Array[counter].sprite);

			counter++;
		}

		//Draw grass
		counter = 0;
		for (iter35 = grassArray.begin(); iter35 != grassArray.end(); iter35++)
		{
			grassArray[counter].update();
			//window.draw(pickupArray[counter].rect);
			window.draw(grassArray[counter].sprite);

			counter++;
		}

		//Draw Projectile
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			projectileArray[counter].update();
			window.draw(projectileArray[counter].sprite);

			counter++;
		}

		//Draw Enemy
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			enemyArray[counter].update();
			enemyArray[counter].updateMovement();
			//window.draw(enemyArray[counter].rect);
			window.draw(enemyArray[counter].sprite);

			counter++;
		}

		//Draw Enemy
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			enemyArray[counter].text.setString("HP " + to_string(enemyArray[counter].hp) + "/" + to_string(enemyArray[counter].maxhp));
			window.draw(enemyArray[counter].text);

			counter++;
		}

		//Draw Enemy2
		counter = 0;
		for (iter5 = enemy2Array.begin(); iter5 != enemy2Array.end(); iter5++)
		{
			enemy2Array[counter].update();
			enemy2Array[counter].updateMovement();
			//window.draw(enemyArray[counter].rect);
			window.draw(enemy2Array[counter].sprite2);

			counter++;
		}

		//Draw Enemy2
		counter = 0;
		for (iter5 = enemy2Array.begin(); iter5 != enemy2Array.end(); iter5++)
		{
			enemy2Array[counter].text.setString("HP " + to_string(enemy2Array[counter].hp) + "/" + to_string(enemy2Array[counter].maxhp));
			window.draw(enemy2Array[counter].text);

			counter++;
		}

		//Draw Enemy3
		counter = 0;
		for (iter6 = enemy3Array.begin(); iter6 != enemy3Array.end(); iter6++)
		{
			enemy3Array[counter].update();
			enemy3Array[counter].updateMovement();
			//window.draw(enemyArray[counter].rect);
			window.draw(enemy3Array[counter].sprite3);

			counter++;
		}

		//Draw Enemy3
		counter = 0;
		for (iter6 = enemy3Array.begin(); iter6 != enemy3Array.end(); iter6++)
		{
			enemy3Array[counter].text.setString("HP " + to_string(enemy3Array[counter].hp) + "/" + to_string(enemy3Array[counter].maxhp));
			window.draw(enemy3Array[counter].text);

			counter++;
		}

		//Draw Enemy4
		counter = 0;
		for (iter7 = enemy4Array.begin(); iter7 != enemy4Array.end(); iter7++)
		{
			enemy4Array[counter].update();
			enemy4Array[counter].updateMovement();
			//window.draw(enemyArray[counter].rect);
			window.draw(enemy4Array[counter].sprite4);

			counter++;
		}

		//Draw Enemy4
		counter = 0;
		for (iter7 = enemy4Array.begin(); iter7 != enemy4Array.end(); iter7++)
		{
			enemy4Array[counter].text.setString("HP " + to_string(enemy4Array[counter].hp) + "/" + to_string(enemy4Array[counter].maxhp));
			window.draw(enemy4Array[counter].text);

			counter++;
		}

		//Update Player
		Player1.update();
		Player1.updateMovement();

		//Player view
		window.setView(view1);
		view1.setCenter(Player1.rect.getPosition());

		//Draw Player
		window.draw(Player1.sprite);
		//window.draw(Player1.rect);

		//Player HP TEXT
		string out_string1, out_string2;
		stringstream ss1, ss2;
		ss1 << Player1.hp;
		ss2 << Player1.maxhp;
		out_string1 = ss1.str();
		out_string2 = ss2.str();
		textHP.setString("HP : " + out_string1 + "/" + out_string2);
		window.draw(textHP);
		textHP.setPosition(Player1.rect.getPosition().x - window.getSize().x / 2, Player1.rect.getPosition().y - window.getSize().y / 2);

		//Player Score TEXT
		string out_string;
		stringstream ss;
		ss << Player1.gil;
		out_string = ss.str();
		text.setString("SCORE : " + out_string);
		window.draw(text);
		text.setPosition(Player1.rect.getPosition().x - window.getSize().x / 2, Player1.rect.getPosition().y - window.getSize().y / 2 + 25);

		//Game Over
		if (Player1.hp <= 0)
		{
			music.stop();
			soundEnemy.stop();
			soundEnemycollision.stop();
			soundCollision.stop();
			soundPlayershot.stop();
			soundHeart.stop();
			soundDream.stop();
			window.clear();

			soundGameover.play();
			textgameOver.setPosition(Player1.rect.getPosition().x - window.getSize().x / 2 + 175, Player1.rect.getPosition().y - window.getSize().y / 2 + 175);
			window.draw(textgameOver);
		}

		if (enemyBoss.hp == 0)
		{
			music.stop();
			soundEnemy.stop();
			soundEnemycollision.stop();
			soundCollision.stop();
			soundPlayershot.stop();
			soundHeart.stop();
			soundDream.stop();
			window.clear();

			soundSuccess.play();
			textyouWin.setPosition(Player1.rect.getPosition().x - window.getSize().x / 2 + 175, Player1.rect.getPosition().y - window.getSize().y / 2 + 175);
			window.draw(textyouWin);
		}

		//Update the window
		window.display();

		if (flag)
		{
			Sleep(3000);
		}

	}

	return EXIT_SUCCESS;

}
