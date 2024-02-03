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

void Game::initVariable()
{
	this->windowSize = { 860, 640 };
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(this->windowSize, "Space Invader", sf::Style::Close | sf::Style::Titlebar);
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
				speed = { 0.1f, 0.0f };
			}
			else if (ev.key.code == sf::Keyboard::Left)
			{
				speed = { -0.1f, 0.0f };
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
	this->initSpaceship();
	this->initShip();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::runnning() const
{
	return this->window->isOpen();
}

void Game::Update()
{
	this->pollEvent();

	this->updateShip();
}

void Game::Render()
{

	this->window->clear();

	this->RenderShip();
	this->window->draw(this->Ship);

	this->window->display();
}

void Game::RenderShip()
{
	this->window->draw(this->Ship);
}
