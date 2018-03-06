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
	
	SDL_Rect greenRect;
	greenRect.x = redRect.x + (250 / 2);
	greenRect.y = redRect.y + (150 / 2);
	greenRect.w = 100;
	greenRect.h = 50;
	
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

		int xspeed = 0, yspeed = 0, shotSpeed = 1;
		bool exitLoop = false;
		bool renderShot = false;

		while (exitLoop!=true)
		{
			//Set new position for the square
			while (SDL_PollEvent(&checkEvents) != 0)
			{
				if (checkEvents.type == SDL_KEYUP)
				{
					switch (checkEvents.key.keysym.sym)
					{
					case SDLK_LEFT:
						xspeed = 0;
						break;
					case SDLK_RIGHT:
						xspeed = 0;
						break;
					case SDLK_DOWN:
						yspeed = 0;
						break;
					case SDLK_UP:
						yspeed = 0;
						break;
					}
				}
				else if (checkEvents.type == SDL_KEYDOWN)
				{
					switch (checkEvents.key.keysym.sym) 
					{
					case SDLK_ESCAPE:
						exitLoop = true;
						break;
					case SDLK_LEFT:
						xspeed = -1;
						break;
					case SDLK_RIGHT:
						xspeed = 1;
						break;
					case SDLK_DOWN:
						yspeed = 1;
						break;
					case SDLK_UP:
						yspeed = -1;
						break;
						//Shoot a green laser
					case SDLK_SPACE:
						renderShot = true;
						greenRect.x = redRect.x+200;
						greenRect.y = redRect.y + 50;
						break;

					}
				}
			}
			//Sum the determined velocity to the player's character 
			redRect.x += xspeed;
			redRect.y += yspeed;

			SDL_SetRenderDrawColor(renderer, 65, 105, 255, 255);
			SDL_RenderClear(renderer);
			
			//SET the Draw color for the rectangle
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer,&redRect);

			if (renderShot == true)
			{
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				SDL_RenderFillRect(renderer, &greenRect);
				greenRect.x += shotSpeed;
				if (greenRect.x > 1300)
				{
					renderShot = false;
				}
				
			}
			//Update the Render
			SDL_RenderPresent(renderer);
			//Delay 5 milliseconds
			//SDL_Delay(5);
		}
		
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
		SDL_DestroyWindow(window);
		window = NULL;
	return 0;
	}




