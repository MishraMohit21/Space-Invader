#include "Game.h"

void Game::initSpaceship()
{
	if (!this->spaceship.loadFromFile("Texture/spaceship.png"))
	{
		std::cout << "Error::initSpaceship::Texture Failed to Load.\n";
		return;
	}
	this->spaceship.setSmooth(true);
	this->spaceship.setRepeated(false);
}

void Game::initShip()
{
	this->Ship.setTexture(this->spaceship);
	this->Ship.setPosition(this->windowSize.width / 2, this->windowSize.height);
	this->Ship.setScale(0.2, 0.2);
	this->Ship.setRotation(-90.0f);
}

void Game::updateShip()
{
	this->Ship.setPosition(this->Ship.getPosition() + speed);
	if (this->Ship.getPosition().x < 0)
	{
		this->Ship.setPosition(this->windowSize.width, this->windowSize.height);
	}
	else if (this->Ship.getPosition().x > this->windowSize.width)
	{
		this->Ship.setPosition(0, this->windowSize.height);
	}
}



void Game::initastroid_Tex()
{
	if (!this->astroid_Tex.loadFromFile("Texture/enemy.png"))
	{
		std::cout << "Error::initSpaceship::Texture Failed to Load.\n";
		return;
	}
	this->astroid_Tex.setSmooth(true);
	this->astroid_Tex.setRepeated(true);
}


void Game::spawnAstroid()
{
	sf::Sprite astroid;
	astroid.setTexture(this->astroid_Tex);
	astroid.setScale(0.4, 0.4);
	if (this->Astrtoid_Array.size() != this->MaxAstroid)
	{
		astroid.setPosition(rand() % this->windowSize.width - 70, 0);
		this->Astrtoid_Array.push_back(astroid);
	}
	
}

void Game::updateAstroid()
{
	tick++;
	if (this->Astrtoid_Array.size() != this->MaxAstroid)
	{
		if (this->SpawnTimer <= 0)
		{
			this->spawnAstroid();
			//this->SpawnTimerMax -= 500;
			this->SpawnTimer = this->SpawnTimerMax;
		}
		else
		{
			this->SpawnTimer -= 50.0f;
		}
	}

	for (int i = 0; i < this->Astrtoid_Array.size(); i++)
	{
		this->Astrtoid_Array[i].setPosition(this->Astrtoid_Array[i].getPosition() + sf::Vector2f(0, 1.25 * this->scl));
		//std::cout << "The Position of Astroid : : " << this->Astrtoid_Array[i].getGlobalBounds().getPosition().x << ", " << this->Astrtoid_Array[i].getGlobalBounds().getPosition().y << "\n";

		if (this->Astrtoid_Array[i].getPosition().y > this->windowSize.height - 130)
		{
			this->Astrtoid_Array.erase(this->Astrtoid_Array.begin() + i);
			this->Health -= 5;
		}

		/*for (int j = 0; j < this->Laser_Array.size(); j++)
		{
			if (this->Astrtoid_Array[i].getLocalBounds().contains(this->Laser_Array[j].getPosition()))
			{
				this->Laser_Array.erase(this->Laser_Array.begin() + j);
				this->Astrtoid_Array.erase(this->Astrtoid_Array.begin() + i);
			}
		}*/
	}
}

void Game::RenderAstroid()
{
	for (auto& ast : Astrtoid_Array)
	{
		this->window->draw(ast);
	}
}

void Game::initLasetTex()
{
	if (!this->Laser_Tex.loadFromFile("Texture/shot.png"))
	{
		std::cout << "Error::initSpaceship::Texture Failed to Load.\n";
		return;
	}
	this->Laser_Tex.setSmooth(true);
	this->Laser_Tex.setRepeated(true);
}

void Game::SpawnLaser()
{
	sf::Sprite laser;
	laser.setTexture(this->Laser_Tex);
	laser.setScale(0.5, 0.5);
	if (this->Laser_Array.size() <= MaxLaser)
	{
		laser.setPosition(this->Ship.getPosition().x + 20.0f, this->Ship.getPosition().y - 125.0f);
		this->Laser_Array.push_back(laser);
	}
}

void Game::updateLaser()
{
	bool deleted = false;

	for (int i = 0; i < this->Laser_Array.size(); i++)
	{
		/*std::cout << "The Position of First laser is :: " << this->Laser_Array[0].getPosition().x << " " << this->Laser_Array[0].getPosition().y << "\n";
		std::cout << "The Position of First astroid is :: " << this->Astrtoid_Array[0].getPosition().x << " " << this->Astrtoid_Array[0].getPosition().y << "\n";*/

		this->Laser_Array[i].setPosition(this->Laser_Array[i].getPosition() + this->LaserMove);

		if (this->Laser_Array[i].getPosition().y < 0)
		{
			this->Laser_Array.erase(this->Laser_Array.begin() + i);
		}

	}
	for (int i = 0; i < this->Laser_Array.size(); i++)
	{
		for (int j = 0; j < this->Astrtoid_Array.size() && !deleted; j++)
		{
			//std::cout << "loop is running\n";
			float laser_x = this->Laser_Array[i].getPosition().x;
			float laser_y = this->Laser_Array[i].getPosition().y;
			float astroid_x = this->Astrtoid_Array[j].getPosition().x;
			float astroid_y = this->Astrtoid_Array[j].getPosition().y;

			if (laser_x > astroid_x - 20 && laser_y > astroid_y && laser_x < astroid_x + 70 && laser_y < astroid_y + 70 && !deleted)
			{
				//std::cout << "The Position of First laser is :: " << this->Laser_Array[i].getPosition().x << " " << this->Laser_Array[i].getPosition().y << "\n";
				//std::cout << "The Position of First astroid is :: " << this->Astrtoid_Array[j].getPosition().x << " " << this->Astrtoid_Array[j].getPosition().y << "\n";
				this->Astrtoid_Array.erase(this->Astrtoid_Array.begin() + j);
				this->Laser_Array.erase(this->Laser_Array.begin() + i);
				deleted = true;
				Point += 5;
			}
			else
			{
				deleted = false;
			}
		}

	}


}

void Game::RenderLaser()
{
	for (auto& laser : this->Laser_Array)
	{
		this->window->draw(laser);
	}
}

void Game::initFont()
{
	if (!this->uiFont.loadFromFile("Font/Orbitron/Orbitron-Bold.ttf"))
		std::cout << "ERROR::GAME::INITFONT::Failed to load font\n";
}

void Game::initText()
{
	this->uiText.setFont(this->uiFont);
	this->uiText.setCharacterSize(32);
	this->uiText.setFillColor(sf::Color(65, 105, 255));
	this->uiText.setPosition(10, 10);
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->Point << "\nHealth: " << this->Health;

	this->uiText.setString(ss.str());
}

void Game::RenderText()
{
	this->window->draw(this->uiText);
}


void Game::initVariable()
{
	this->windowSize = { 860, 640 };
	this->tick = 0;
	this->SpawnTimerMax = 4000.0f;
	this->SpawnTimer = this->SpawnTimerMax;
	this->MaxAstroid = 10;
	this->MaxLaser = 10;
	this->LaserMove = { 0.0f, -3.0f };
	this->Point = 0;
	this->Health = 100;
	this->EndGame = false;
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(this->windowSize, "Space Invader", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	this->window->setFramerateLimit(60);
}

void Game::pollEvent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();

		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape) {
				this->window->close();
			}
			else if (ev.key.code == sf::Keyboard::Right)
			{
				speed = { this -> scl * 2.1f, 0.0f };
			}
			else if (ev.key.code == sf::Keyboard::Left)
			{
				speed = { -2.1f * this->scl, 0.0f };
			}
			else if (ev.key.code == sf::Keyboard::Space)
			{
				this->SpawnLaser();
			}
			break;

		default:
			break;
		}
	}
}

Game::Game()
{
	this->initVariable();
	this->initWindow();
	 
	// Spaceship
	this->initSpaceship();
	this->initShip();

	// Astroid Level1 
	this->initastroid_Tex();

	// Laser
	this->initLasetTex();

	// Text
	this->initFont();
	this->initText();

	//std::cout << this->Ship.getPosition().y;
}

Game::~Game()
{
	delete this->window;
}

const bool Game::runnning() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->EndGame;
}

void Game::Update()
{
	this->pollEvent();

	if(!this->EndGame)
	{
		this->updateShip();

		this->updateAstroid();

		this->updateLaser();

		this->updateText();
	}

	if (this->Health <= 0)
	{
		this->EndGame = true;
	}
}

void Game::Render()
{

	this->window->clear();

	this->RenderShip();
	//this->window->draw(this->astroid);
	this->RenderAstroid();
	this->RenderText();
	this->RenderLaser();

	this->window->display();
}

void Game::RenderShip()
{
	this->window->draw(this->Ship);
}
