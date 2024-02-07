#pragma once
#include "Header.h"


class Game
{

	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode windowSize;

	float scl = 1;
	float Point, Health;

	bool EndGame;
	

	// SpaceShip
	sf::Texture spaceship;
	void initSpaceship();
	sf::Sprite Ship;
	void initShip();
	sf::Vector2f speed;


	void updateShip();

	// Astroid
	float SpawnTimer;
	float SpawnTimerMax;
	float MaxAstroid;
	long long tick;

	sf::Texture astroid_Tex;
	void initastroid_Tex();
	std::vector<sf::Sprite> Astrtoid_Array;
	void spawnAstroid();
	void updateAstroid();
	void RenderAstroid();


	// Shooting laser;
	int MaxLaser;
	sf::Vector2f LaserMove;

	sf::Texture Laser_Tex;
	void initLasetTex();

	std::vector<sf::Sprite> Laser_Array;
	void SpawnLaser();
	void updateLaser();
	void RenderLaser();


	// Text Stuff
	sf::Font uiFont;
	void initFont();

	sf::Text uiText;
	void initText();
	void updateText();
	void RenderText();

	// Basic Initializers
	void initVariable();
	void initWindow();
	
	void pollEvent();

public:

	Game();
	~Game();


	const bool runnning() const;
	const bool getEndGame() const;

	void Update();
	


	void Render();
	void RenderShip();
	

};

