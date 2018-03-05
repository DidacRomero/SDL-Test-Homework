#include "SDL/include/SDL.h"

#pragma comment(lib,"SDL/libx86/SDL2.lib")
#pragma comment(lib,"SDL/libx86/SDL2main.lib")

int main(int argc,char* argv[])
{
	SDL_Window *window=NULL;
	SDL_Renderer* renderer=NULL;
	SDL_Event checkEvents;

	SDL_Init(SDL_INIT_VIDEO);

	//Declare the Red Rectangle Dimensions and Position
	SDL_Rect redRect;
	redRect.x = 1280/4;
	redRect.y = 720/4;
	redRect.w = 250;
	redRect.h = 150;
	
	//Set the Window
		window = SDL_CreateWindow(
			"Best Game EVER!",                   // window title
			SDL_WINDOWPOS_CENTERED,             // initial x position
			SDL_WINDOWPOS_CENTERED,            // initial y position
			1280,                             // width, in pixels
			720,                             // height, in pixels
			0								// flags 
		);
		//Set the Renderer
		renderer = SDL_CreateRenderer(window, -1, 0);

		int xspeed = 0, yspeed = 0;
		bool exitLoop = false;
	
		while (exitLoop!=true)
		{
			//Set new position for the square
			if (SDL_PollEvent(&checkEvents)!=0)
			{
				if (checkEvents.type == SDL_KEYDOWN)
				{
					exitLoop = true;
				}
			
			}

			redRect.x += xspeed;
			redRect.y += yspeed;

			SDL_SetRenderDrawColor(renderer, 65, 105, 255, 255);
			SDL_RenderClear(renderer);
			//SET the Draw color for the rectangle
			
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer,&redRect);
			//Update the 
			SDL_RenderPresent(renderer);
			//Delay 5 milliseconds
			SDL_Delay(5);
		}
		
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
		SDL_DestroyWindow(window);
		window = NULL;
	return 0;
}




/*
if (redRect.x <= 0)
xspeed = 1;
else if(redRect.x >= 880)
xspeed = -1;
else if(redRect.y <= 0)
yspeed = 1;
else if (redRect.y >= 420)
yspeed = -1;
*/