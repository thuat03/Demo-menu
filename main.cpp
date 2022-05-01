#include<SDL.h>
#include<SDL_image.h>
#include<iostream>

using namespace std;
//The window and renderer
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;


#include"const.h"
#include"LButtonSprite.h"

//Mouse button sprites

SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];

#include"LButton.h"

//Button objects
LButton gButtons_1;
LButton gButtons_2;


#include"Render.h"

int main(int argc, char* args[]) {

	init();
	
	loadMedia();

	bool quit = false;
	SDL_Event e;
	while (!quit) {
		
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
				break;
			}
			gButtons_1.handleEvent(&e);
			gButtons_2.handleEvent(&e);
		}
		SDL_SetRenderDrawColor(gRenderer, YELLOW_COLOR.r, YELLOW_COLOR.g, YELLOW_COLOR.b, YELLOW_COLOR.a);
		SDL_RenderClear(gRenderer);

		gButtons_1.render();
		gButtons_2.render();

		//Ấn vào exit để thoát 
		if (gButtons_2.getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			quit = true;
			break;
		}

		SDL_RenderPresent(gRenderer);
	}

	close();
	return 0;
}