#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"


#pragma comment(lib,"SDL/libx86/SDL2.lib")
#pragma comment(lib,"SDL/libx86/SDL2main.lib")
#pragma comment(lib,"SDL_Image/libx86/SDL2_image.lib")

int main(int argc, char* argv[])
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event checkEvents;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	//Declare the Red Rectangle Dimensions and Position
	SDL_Rect redRect;
	redRect.x = 1280 / 4;
	redRect.y = 720 / 4;
	redRect.w = 250;
	redRect.h = 150;

	SDL_Rect greenRect[1000];

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

	int xspeed = 1, yspeed = 1, bulletSpeed = 1;
	int bulletArrPos = 0;
	bool exitLoop = false;
	bool renderShot = false;
	bool leftPressed = false, rightPressed = false, upPressed = false, downPressed = false;

	//Set the PNG Background
	SDL_Texture *back= nullptr;
	SDL_Texture *ShipTexture = nullptr;
	SDL_Surface *Background = IMG_Load("background.png");
	SDL_Surface *Ship = IMG_Load("ae86.png");
	back = SDL_CreateTextureFromSurface(renderer,Background);
	ShipTexture = SDL_CreateTextureFromSurface(renderer,Ship);
	if (back==nullptr || ShipTexture==nullptr)
	{
		return -1;
	}
	else
	{

		while (exitLoop != true)
		{

			//Set the inputs into the KeyPressed variables
			while (SDL_PollEvent(&checkEvents) != 0)
			{
				if (checkEvents.type == SDL_KEYUP)
				{
					switch (checkEvents.key.keysym.sym)
					{
					case SDLK_LEFT:
						leftPressed = false;
						break;
					case SDLK_RIGHT:
						rightPressed = false;
						break;
					case SDLK_DOWN:
						downPressed = false;
						break;
					case SDLK_UP:
						upPressed = false;
						break;
					}
				}
				if (checkEvents.type == SDL_KEYDOWN)
				{
					switch (checkEvents.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						exitLoop = true;
						break;
					case SDLK_LEFT:
						leftPressed = true;
						break;
					case SDLK_RIGHT:
						rightPressed = true;
						break;
					case SDLK_DOWN:
						downPressed = true;
						break;
					case SDLK_UP:
						upPressed = true;
						break;
						//Shoot a green laser
					case SDLK_SPACE:
						greenRect[bulletArrPos].x = redRect.x + 200;
						greenRect[bulletArrPos].y = redRect.y + 50;
						bulletArrPos++;
						break;

					}
				}
			}

			// Using the KeyPressed variables to change speed, thus position
			if (leftPressed == true)
			{
				redRect.x -= xspeed;
			}
			if (rightPressed == true)
			{
				redRect.x += xspeed;
			}
			if (upPressed == true)
			{
				redRect.y -= xspeed;
			}
			if (downPressed == true)
			{
				redRect.y += xspeed;
			}

			//SDL_SetRenderDrawColor(renderer, 65, 105, 255, 255);
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, back, NULL, NULL);



			//SET the Draw color for the rectangle
			//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderCopy(renderer,ShipTexture, NULL, &redRect);
		//	SDL_RenderFillRect(renderer, &redRect);


			//Update the bullets status and render
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			for (int i = 0; i <= bulletArrPos; ++i)
			{
				greenRect[i].w = 100;
				greenRect[i].h = 25;
				greenRect[i].x += bulletSpeed;
				SDL_RenderFillRect(renderer, &greenRect[i]);
				if (greenRect[i].x < 1300)
				{
					SDL_RenderFillRect(renderer, &greenRect[i]);
				}
			}
			//Update the Render
			SDL_RenderPresent(renderer);
			//Delay 5 milliseconds
			//SDL_Delay(5);
		}


		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
		SDL_DestroyWindow(window);
		window = nullptr;
		SDL_FreeSurface(Background);
		IMG_Quit();
		return 0;
	}
}




