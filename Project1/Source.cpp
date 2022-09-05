#include "Game.h"


int main() {

	begin:
	//init game engine
	Game game;

	while (game.running()) 
	{
			game.update();
	}
	

}