#include "Game.h"

int main()
{ 
	std::cout << "Hello"; 
	std::srand(static_cast<unsigned>(time(NULL)));

	Game game;

	while (game.runnning() && !game.getEndGame())
	{

		game.Update();

		game.Render();
	}

	return 0;
}