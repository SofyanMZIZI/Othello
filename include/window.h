#ifndef window_H_
#define window_H_

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>

#define 	iconPATH			"../imgSound/OthelloIcon.bmp"
#define		FondEcranPATH		"../imgSound/FondEcran.bmp"
#define 	EmptyCasePATH		"../imgSound/EmptyCase.bmp"
#define 	PlayableCasePATH 	"../imgSound/PlayableCase.bmp"
#define 	WhiteCasePATH		"../imgSound/WhiteCase.bmp"
#define 	BlackCasePATH		"../imgSound/BlackCase.bmp"

#undef main

SDL_Window *window=NULL;
SDL_Renderer *renderer=NULL;
SDL_Surface *surface=NULL;
SDL_Texture *texture=NULL;

void FreeMemoryWindow(const char *mssg)
{
	if(mssg!=NULL)
		SDL_Log("%s%s",mssg,SDL_GetError());

	if(texture!=NULL)
		SDL_DestroyTexture(texture);
	if(renderer!=NULL)
		SDL_DestroyRenderer(renderer);
	if(window!=NULL)
		SDL_DestroyWindow(window);
	
	SDL_Quit();

	exit(EXIT_FAILURE);
}

void AllocateMemoryWindow(int WindowWidth,int WindowHeight)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        FreeMemoryWindow("SDL_Init.\n");

	window = SDL_CreateWindow(	"Othello",
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								WindowWidth,
								WindowHeight,
								SDL_WINDOW_SHOWN);
	if (!window)
        FreeMemoryWindow("SDL_CreateWindow.\n");

	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	if (!renderer)
        FreeMemoryWindow("SDL_CreateRenderer.\n");

	surface=SDL_LoadBMP(iconPATH);
	if(!surface)
		FreeMemoryWindow("SDL_LoadBMP.\n");
	SDL_SetWindowIcon(window,surface);
	SDL_FreeSurface(surface);
}

SDL_bool ZoneCliked(SDL_Event event,SDL_Rect rect)
{
	if(event.button.button == SDL_BUTTON_LEFT)
		if((rect.x<event.motion.x && event.motion.x<rect.x+rect.w)
		&& (rect.y<event.motion.y && event.motion.y<rect.y+rect.h))
			return SDL_TRUE;

	return SDL_FALSE;
}

void LoadAndDrawImage(SDL_Rect rect,const char *imgPATH)
{
	surface=SDL_LoadBMP(imgPATH);
	if(!surface)
        FreeMemoryWindow("SDL_LoadBMP");

	texture=SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	if(!texture)
        FreeMemoryWindow("SDL_CreateTextureFromSurface");

	if(SDL_QueryTexture(texture,NULL,NULL,&(rect.w),&(rect.h)) != 0)
        FreeMemoryWindow("SDL_QueryTexture");

	if(SDL_RenderCopy(renderer,texture,NULL,&rect) != 0)
        FreeMemoryWindow("SDL_RenderCopy");

    SDL_RenderPresent(renderer);
}

void PrintTextInWindow(SDL_Rect rect,char *txt,int size,Uint8 r,Uint8 g,Uint8 b)
{
	SDL_Color color={r,g,b,0};

	if(TTF_Init() != 0)
		FreeMemoryWindow("TTF_Init");

	TTF_Font *font=NULL;
	font=TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf",size);
	if(!font)
		FreeMemoryWindow("TTF_OpenFont");

	surface=TTF_RenderText_Blended(font,txt,color);
	if(!surface)
		FreeMemoryWindow("TTF_RenderText_Blended");

	SDL_Rect txtPosion;
	txtPosion.w=(rect.w-surface->w)/2;
	txtPosion.h=(rect.h-surface->h)/2;

	texture=SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	if(!texture)
		FreeMemoryWindow("SDL_CreateTextureFromSurface");

	if(SDL_QueryTexture(texture,NULL,NULL,&(txtPosion.w),&(txtPosion.h)) != 0)
		FreeMemoryWindow("SDL_QueryTexture");

	if(SDL_RenderCopy(renderer,texture,NULL,&rect) != 0)
		FreeMemoryWindow("SDL_RenderCopy");

    SDL_RenderPresent(renderer);

	TTF_CloseFont(font);

	TTF_Quit();
}





#endif