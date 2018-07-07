#include "stdafx.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

void alireza_getch() {
	SDL_Event e;
	while(SDL_WaitEvent(&e) && e.type != SDL_KEYDOWN);
}

/* Start coding here! */

void UI() {

	// create new window
	SDL_Window *screen = SDL_CreateWindow("SDL Application", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,500,500,0);
	
	// create a surface pointing to the window
	SDL_Surface *screenField = SDL_GetWindowSurface(screen);
	
	// fill surface with BLUE color 
	SDL_FillRect(screenField, NULL, SDL_MapRGB(screenField->format, 0, 0, 255));
	
	// update surface
	SDL_UpdateWindowSurface(screen);

	// getch implementation for SDL
	alireza_getch();

}

int _tmain(int argc, _TCHAR* argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
		return 1;
	}
	UI();
	SDL_Quit();
	return 0;
}


