#include "GameWindow.h"

int main(int argc, char* argv[])
{
	AllocateMemoryWindow(GameWindowWidth,GameWindowHeight);
    //**********************************************************************************************
	MakeGameWindow();

	SDL_Event event;
	SDL_bool launched = SDL_TRUE;

	replay:
	InitGameDrawBoard();
	EveryPlayableCases();
	while(launched)
	{
		
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_MOUSEBUTTONDOWN:
					PlayTheMove(event);

					if(ZoneCliked(event,rectReplay)==SDL_TRUE)
						goto replay;
					
					if(ZoneCliked(event,rectBack)==SDL_TRUE)
						launched = SDL_FALSE;
						break;

					continue;

				case SDL_QUIT:
					launched = SDL_FALSE;
					break;
			
				default:
					continue;
			}
		}
		SDL_Delay(10);
	}
    //**********************************************************************************************
	FreeMemoryWindow(NULL);

    return EXIT_SUCCESS;
}