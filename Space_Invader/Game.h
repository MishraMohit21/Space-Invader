#pragma once
#include "Header.h"


class Game
{

	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode windowSize;


	// SpaceShip
	sf::Texture spaceship;
	void initSpaceship();
	sf::Sprite Ship;
	void initShip();
	sf::Vector2f speed;

	void updateShip();


	void initVariable();
	void initWindow();
	
	void pollEvent();

public:

	Game();
	~Game();


	const bool runnning() const;

	void Update();
	


	void Render();
	void RenderShip();
	

};

