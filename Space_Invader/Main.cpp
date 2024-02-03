#include "Game.h"

int main()
{ 
	std::cout << "Hello"; 

	Game game;

	while (game.runnning())
	{

		game.Update();

		game.Render();
	}

	return 0;
}