#ifndef GameWindow_H_
#define GameWindow_H_

#include "window.h"


#define		GameWindowWidth				800
#define		GameWindowHeight			550

#define		WidthCase					50
#define		HeightCase					50
#define		X_Board						((GameWindowWidth-400)/2)
#define		Y_Borad						75

#define 	BlackPlayer					0
#define 	WhitePlayer					1

#define  	DrawCaseImg(board,path);	board.imgPATH=path;\
										LoadAndDrawImage(board.rect,board.imgPATH);\
										

typedef struct IndexCase
{
	int i,j;
}IndexCase;

typedef struct BoardCase
{
	SDL_Rect rect;
	const char *imgPATH;
}BoardCase;


int i,j,ind=0;
int current_player=BlackPlayer;
int scores[2];

BoardCase BOARD[8][8];

IndexCase TabPlayableCase[64];

SDL_Rect 	rectWhiteHistoy={650,50,150,500},
			rectBlackHistoy={0,50,150,500},

			rectWhitePlayer={650,0,150,50},
			rectBlackPlayer={0,0,150,50},

			rectBlackIndex={50,50,50,50},
			rectWhiteIndex={700,50,50,50},

			rectReplay={450,495,150,35},
			rectBack={200,495,150,35},

			rectBlackScore={150,0,80,50},
			rectWhiteScore={570,0,80,50},

			rectGameWindow={0,0,GameWindowWidth,GameWindowHeight};


void InitGameDrawBoard()
{
	SDL_SetRenderDrawColor(renderer,10,200,200,0);//rgb(127,255,212)
	SDL_RenderFillRect(renderer,&rectWhiteHistoy);
	SDL_RenderFillRect(renderer,&rectBlackHistoy);

	rectBlackIndex.x=50;
	rectBlackIndex.y=rectWhiteIndex.y=50;
	rectWhiteIndex.x=700;


	scores[BlackPlayer]=2;
	scores[WhitePlayer]=2;

	SDL_SetRenderDrawColor(renderer,128,255,128,0);
	SDL_RenderFillRect(renderer,&rectWhiteScore);
	SDL_RenderFillRect(renderer,&rectBlackScore);

	PrintTextInWindow(rectBlackScore,"  2",50,0,0,0);
	PrintTextInWindow(rectWhiteScore,"2  ",50,255,255,255);

	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
			BOARD[i][j].rect.h=HeightCase;
			BOARD[i][j].rect.w=WidthCase;
			BOARD[i][j].rect.x=X_Board+WidthCase*j;
			BOARD[i][j].rect.y=Y_Borad+HeightCase*i;

			if((i==3 && j==3) || (i==4 && j==4))
				{DrawCaseImg(BOARD[i][j],WhiteCasePATH)}
			else
				if((i==3 && j==4) || (i==4 && j==3))
					{DrawCaseImg(BOARD[i][j],BlackCasePATH)}
				else
					{DrawCaseImg(BOARD[i][j],EmptyCasePATH)}
		}
}

void DrawIndexBoard()
{
	SDL_Rect rect={200-30,75+(20/2),30,30};
	char *txt;
	for(int i=49 ; i<57 ; i++)
	{
		sprintf(txt,"%c",i);
		PrintTextInWindow(rect,txt,50,255,255,0);
		rect.y+=50;
	}
}

void MakeGameWindow()
{
	SDL_SetRenderDrawColor(renderer,0,255,190,0);
	SDL_RenderFillRect(renderer,&rectGameWindow);
	SDL_RenderPresent(renderer);

	SDL_SetRenderDrawColor(renderer,128,255,128,0);
	SDL_RenderFillRect(renderer,&rectWhiteScore);
	SDL_RenderFillRect(renderer,&rectBlackScore);
	SDL_RenderFillRect(renderer,&rectBlackPlayer);
	SDL_RenderFillRect(renderer,&rectWhitePlayer);

	PrintTextInWindow(rectBlackPlayer,"Black",100,0,0,0);
	PrintTextInWindow(rectWhitePlayer,"White",100,255,255,255);

	SDL_SetRenderDrawColor(renderer,0,0,255,0);
	SDL_RenderFillRect(renderer,&rectBack);
	SDL_RenderFillRect(renderer,&rectReplay);
	SDL_RenderPresent(renderer);

	PrintTextInWindow(rectBack," QUIT ",200,0,0,0);
	PrintTextInWindow(rectReplay,"REPLAY",200,0,0,0);
}

SDL_bool Is_End_Game()
{
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
			if(BOARD[i][j].imgPATH==EmptyCasePATH || BOARD[i][j].imgPATH==PlayableCasePATH)
				return SDL_FALSE;

	return SDL_TRUE;
}

void StoreAndDrawPlayableCase(int x,int y)
{
	TabPlayableCase[ind].i=x;
	TabPlayableCase[ind].j=y;
	DrawCaseImg(BOARD[x][y],PlayableCasePATH)
	ind++;
}

int PlayableCase(int x,int y)
{
	int nbrP=0;
	//parc horiz 
    //right
	if(BOARD[x][y].imgPATH == BlackCasePATH)
		for(j=y+1 ; j<8 && BOARD[x][j].imgPATH == WhiteCasePATH ; j++);

	if(BOARD[x][y].imgPATH == WhiteCasePATH)
    	for(j=y+1 ; j<8 && BOARD[x][j].imgPATH == BlackCasePATH ; j++);

	if((BOARD[x][j].imgPATH==EmptyCasePATH || BOARD[i][j].imgPATH==PlayableCasePATH) && y!=j-1)
		{StoreAndDrawPlayableCase(x,j);nbrP++;}
	//
	//left
	if(BOARD[x][y].imgPATH == BlackCasePATH)
		for(j=y-1 ; j>=0 && BOARD[x][j].imgPATH == WhiteCasePATH ; j--);

	if(BOARD[x][y].imgPATH == WhiteCasePATH)
    	for(j=y-1 ; j>=0 && BOARD[x][j].imgPATH == BlackCasePATH ; j--);

	if((BOARD[x][j].imgPATH==EmptyCasePATH || BOARD[x][j].imgPATH==PlayableCasePATH) && y!=j+1)
		{StoreAndDrawPlayableCase(x,j);nbrP++;}
	//
	//parc vertic
    //DOWN
	if(BOARD[x][y].imgPATH == BlackCasePATH)
		for(i=x+1 ; i<8 && BOARD[i][y].imgPATH == WhiteCasePATH ; i++);

	if(BOARD[x][y].imgPATH == WhiteCasePATH)
    	for(i=x+1 ; i<8 && BOARD[i][y].imgPATH == BlackCasePATH ; i++);

	if((BOARD[i][y].imgPATH==EmptyCasePATH || BOARD[i][y].imgPATH==PlayableCasePATH) && x!=i-1)
		{StoreAndDrawPlayableCase(i,y);nbrP++;}
	//
	//UP
	if(BOARD[x][y].imgPATH == BlackCasePATH)
		for(i=x-1 ; i>=0 && BOARD[i][y].imgPATH == WhiteCasePATH ; i--);

	if(BOARD[x][y].imgPATH == WhiteCasePATH)
    	for(i=x-1 ; i>=0 && BOARD[i][y].imgPATH == BlackCasePATH ; i--);

	if((BOARD[i][y].imgPATH==EmptyCasePATH || BOARD[i][y].imgPATH==PlayableCasePATH) && x!=i+1)
		{StoreAndDrawPlayableCase(i,y);nbrP++;}
	//
	//parc diagonal droite
    //UP
	if(BOARD[x][y].imgPATH == BlackCasePATH)
		for(i=x-1,j=y+1 ;i>=0 && j<8 && BOARD[i][j].imgPATH == WhiteCasePATH ; i--,j++);

	if(BOARD[x][y].imgPATH == WhiteCasePATH)
    	for(i=x-1,j=y+1 ;i>=0 && j<8 && BOARD[i][j].imgPATH == BlackCasePATH ; i--,j++);

	if((BOARD[i][j].imgPATH==EmptyCasePATH || BOARD[i][j].imgPATH==PlayableCasePATH) && i+1 != x && j-1 != y)
		{StoreAndDrawPlayableCase(i,j);nbrP++;}
	//
	//Down
	if(BOARD[x][y].imgPATH == BlackCasePATH)
		for(i=x+1,j=y-1 ; i<8 && j>=0 && BOARD[i][j].imgPATH == WhiteCasePATH ; i++,j--);

	if(BOARD[x][y].imgPATH == WhiteCasePATH)
		for(i=x+1,j=y-1 ; i<8 && j>=0 && BOARD[i][j].imgPATH == BlackCasePATH ; i++,j--);

	if((BOARD[i][j].imgPATH==EmptyCasePATH || BOARD[i][j].imgPATH==PlayableCasePATH) && i-1 != x && j+1 != y)
		{StoreAndDrawPlayableCase(i,j);nbrP++;}
	//
	//parc diagonal LEFT
    //UP
	if(BOARD[x][y].imgPATH == BlackCasePATH)
		for(i=x-1,j=y-1; i>=0 && j>=0 && BOARD[i][j].imgPATH == WhiteCasePATH ; i--,j--);

	if(BOARD[x][y].imgPATH == WhiteCasePATH)
		for(i=x-1,j=y-1 ; i>=0 && j<8 && BOARD[i][j].imgPATH == BlackCasePATH ; i--,j--);

	if((BOARD[i][j].imgPATH==EmptyCasePATH || BOARD[i][j].imgPATH==PlayableCasePATH) && i+1 != x && j+1 != y)
		{StoreAndDrawPlayableCase(i,j);nbrP++;}
	//
	//Down
	if(BOARD[x][y].imgPATH == BlackCasePATH)
		for(i=x+1,j=y+1 ; i<8 && j<8 && BOARD[i][j].imgPATH == WhiteCasePATH ; i++,j++);

	if(BOARD[x][y].imgPATH == WhiteCasePATH)
		for(i=x+1,j=y+1 ; i<8 && j<8 && BOARD[i][j].imgPATH == BlackCasePATH ; i++,j++);

	if((BOARD[i][j].imgPATH==EmptyCasePATH || BOARD[i][j].imgPATH==PlayableCasePATH) && i-1 != x && j-1 != y)
		{StoreAndDrawPlayableCase(i,j);nbrP++;}
	//
}

SDL_bool ChoosePlayableCase(SDL_Event event)
{
	for (i=0 ; i<8 ; i++)
		for (j=0 ; j<8; j++)
			if(ZoneCliked(event,BOARD[i][j].rect)==SDL_TRUE && BOARD[i][j].imgPATH==PlayableCasePATH)
				return SDL_TRUE;
			
	return SDL_FALSE;
}

void MakeChange(int x,int y)
{
    //this function will make the necessary changes if the current player has chosen the right case

	//parc horiz **********************************************************************************
    //right
	if(BOARD[x][y].imgPATH == BlackCasePATH)
	{
		for(j=y+1 ; j<8 && BOARD[x][j].imgPATH == WhiteCasePATH ; j++);
		if(BOARD[x][j].imgPATH == BlackCasePATH && y!=j-1)
			for(j--; j>y ;j--)
				{DrawCaseImg(BOARD[x][j],BlackCasePATH) scores[BlackPlayer]++;scores[WhitePlayer]--;}
	}
	if(BOARD[x][y].imgPATH == WhiteCasePATH)
	{
		for(j=y+1 ; j<8 && BOARD[x][j].imgPATH == BlackCasePATH ; j++);
		if(BOARD[x][j].imgPATH == WhiteCasePATH && y!=j-1)
			for(j--; j>y ;j--)
				{DrawCaseImg(BOARD[x][j],WhiteCasePATH) scores[WhitePlayer]++;scores[BlackPlayer]--;}
	}
	//
	//left
	if(BOARD[x][y].imgPATH == BlackCasePATH)
	{
		for(j=y-1 ; j>=0 && BOARD[x][j].imgPATH == WhiteCasePATH ; j--);
		if(BOARD[x][j].imgPATH==BlackCasePATH && y!=j+1)
			for(j++; j<y ;j++)
				{DrawCaseImg(BOARD[x][j],BlackCasePATH) scores[BlackPlayer]++;scores[WhitePlayer]--;}
	}
	if(BOARD[x][y].imgPATH == WhiteCasePATH)
	{
		for(j=y-1 ; j>=0 && BOARD[x][j].imgPATH == BlackCasePATH ; j--);
		if(BOARD[x][j].imgPATH==WhiteCasePATH && y!=j+1)
			for(j++; j<y ;j++)
				{DrawCaseImg(BOARD[x][j],WhiteCasePATH) scores[WhitePlayer]++;scores[BlackPlayer]--;}
	}
	//*********************************************************************************************

	//parc vertc **********************************************************************************
	//UP
	if(BOARD[x][y].imgPATH == BlackCasePATH)
	{
		for (i = x - 1; i >= 0 && BOARD[i][y].imgPATH == WhiteCasePATH; i--);
		if (BOARD[i][y].imgPATH == BlackCasePATH && x != i + 1)
			for(i++; i<x ;i++)
				{DrawCaseImg(BOARD[i][y],BlackCasePATH) scores[BlackPlayer]++;scores[WhitePlayer]--;}
	}
	if(BOARD[x][y].imgPATH == WhiteCasePATH)
	{
		for (i = x - 1; i >= 0 && BOARD[i][y].imgPATH == BlackCasePATH; i--);
		if (BOARD[i][y].imgPATH == WhiteCasePATH && x != i + 1)
			for(i++; i<x ;i++)
				{DrawCaseImg(BOARD[i][y],WhiteCasePATH) scores[WhitePlayer]++;scores[BlackPlayer]--;}
	}
	//DOWN
	if(BOARD[x][y].imgPATH == BlackCasePATH)
	{
		for (i = x + 1; i < 8 && BOARD[i][y].imgPATH == WhiteCasePATH; i++);
		if (BOARD[i][y].imgPATH == BlackCasePATH && x != i - 1)
			for(i--; i>x ;i--)
				{DrawCaseImg(BOARD[i][y],BlackCasePATH) scores[BlackPlayer]++;scores[WhitePlayer]--;}
	}
	if(BOARD[x][y].imgPATH == WhiteCasePATH)
	{
		for (i = x + 1; i < 8 && BOARD[i][y].imgPATH == BlackCasePATH; i++);
		if (BOARD[i][y].imgPATH == WhiteCasePATH && x != i - 1)
			for(i--; i>x ;i--)
				{DrawCaseImg(BOARD[i][y],WhiteCasePATH) scores[WhitePlayer]++;scores[BlackPlayer]--;}
	}
	//
	//*********************************************************************************************

	//dgnl right **********************************************************************************
	//UP
	if(BOARD[x][y].imgPATH == BlackCasePATH)
	{
		for (i = x - 1, j = y + 1; i >= 0 && j < 8 && BOARD[i][j].imgPATH == WhiteCasePATH; i--, j++);
		if (BOARD[i][j].imgPATH == BlackCasePATH && i + 1 != x && j - 1 != y)
			for(i++,j-- ; i<x && j>y ; i++,j--)
				{DrawCaseImg(BOARD[i][j],BlackCasePATH) scores[BlackPlayer]++;scores[WhitePlayer]--;}
	}
	if(BOARD[x][y].imgPATH == WhiteCasePATH)
	{
		for (i = x - 1, j = y + 1; i >= 0 && j < 8 && BOARD[i][j].imgPATH == BlackCasePATH; i--, j++);
		if (BOARD[i][j].imgPATH == WhiteCasePATH && i + 1 != x && j - 1 != y)
			for(i++,j-- ; i<x && j>y ; i++,j--)
				{DrawCaseImg(BOARD[i][j],WhiteCasePATH) scores[WhitePlayer]++;scores[BlackPlayer]--;}
	}
	//DOWN
	if(BOARD[x][y].imgPATH == BlackCasePATH)
	{
		for(i=x+1,j=y-1 ; i<8 && j>=0 && BOARD[i][j].imgPATH == WhiteCasePATH ; i++,j--);
		if (BOARD[i][j].imgPATH == BlackCasePATH && i-1 != x && j+1 != y)
			for(i--,j++ ; i>x && j<y ; i--,j++)
				{DrawCaseImg(BOARD[i][j],BlackCasePATH) scores[BlackPlayer]++;scores[WhitePlayer]--;}
	}
	if(BOARD[x][y].imgPATH == WhiteCasePATH)
	{
		for(i=x+1,j=y-1 ; i<8 && j>=0 && BOARD[i][j].imgPATH == BlackCasePATH ; i++,j--);
		if (BOARD[i][j].imgPATH == WhiteCasePATH && i-1 != x && j+1 != y)
			for(i--,j++ ; i>x && j<y ; i--,j++)
				{DrawCaseImg(BOARD[i][j],WhiteCasePATH) scores[WhitePlayer]++;scores[BlackPlayer]--;}
	}
	//*********************************************************************************************

	//dgnl left ************************************************************************************
	//UP
	if(BOARD[x][y].imgPATH == BlackCasePATH)
	{
		for(i=x-1,j=y-1; i>=0 && j>=0 && BOARD[i][j].imgPATH == WhiteCasePATH ; i--,j--);
		if (BOARD[i][j].imgPATH == BlackCasePATH && i+1 != x && j+1 != y)
			for(i++,j++ ; i<x && j<y ; i++,j++)
				{DrawCaseImg(BOARD[i][j],BlackCasePATH) scores[BlackPlayer]++;scores[WhitePlayer]--;}
	}
	if(BOARD[x][y].imgPATH == WhiteCasePATH)
	{
		for(i=x-1,j=y-1; i>=0 && j>=0 && BOARD[i][j].imgPATH == BlackCasePATH ; i--,j--);
		if (BOARD[i][j].imgPATH == WhiteCasePATH && i+1 != x && j+1 != y)
			for(i++,j++ ; i<x && j<y ; i++,j++)
				{DrawCaseImg(BOARD[i][j],WhiteCasePATH) scores[WhitePlayer]++;scores[BlackPlayer]--;}
	}
	//DOWN
	if(BOARD[x][y].imgPATH == BlackCasePATH)
	{
		for(i=x+1,j=y+1 ; i<8 && j<8 && BOARD[i][j].imgPATH == WhiteCasePATH ; i++,j++);
		if (BOARD[i][j].imgPATH == BlackCasePATH && i-1 != x && j-1 != y)
			for(i--,j-- ; i>x && j>y ; i--,j--)
				{DrawCaseImg(BOARD[i][j],BlackCasePATH) scores[BlackPlayer]++;scores[WhitePlayer]--;}
	}
	if(BOARD[x][y].imgPATH == WhiteCasePATH)
	{
		for(i=x+1,j=y+1 ; i<8 && j<8 && BOARD[i][j].imgPATH == BlackCasePATH ; i++,j++);
		if (BOARD[i][j].imgPATH == WhiteCasePATH && i-1 != x && j-1 != y)
			for(i--,j-- ; i>x && j>y ; i--,j--)
				{DrawCaseImg(BOARD[i][j],WhiteCasePATH) scores[WhitePlayer]++;scores[BlackPlayer]--;}
	}
	//*********************************************************************************************
}

int EveryPlayableCases()
{
	int totalP=0;
	if(current_player==BlackPlayer)
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				if(BOARD[i][j].imgPATH==BlackCasePATH)
					totalP+=PlayableCase(i,j);
	if(current_player==WhitePlayer)
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				if(BOARD[i][j].imgPATH==WhiteCasePATH)
					totalP+=PlayableCase(i,j);

	return totalP;
}

int NbrCase(char *path)
{
	int som=0;
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			if(BOARD[i][j].imgPATH==path)
				som++;
	return som;
}

void PlayTheMove(SDL_Event event)
{
	if(Is_End_Game()==SDL_FALSE)
		if(ChoosePlayableCase(event)==SDL_TRUE)
		{
			if (current_player==BlackPlayer)
				{DrawCaseImg(BOARD[i][j],BlackCasePATH)}
			else
				{DrawCaseImg(BOARD[i][j],WhiteCasePATH)}
			//////////////////////////////////////////////////////////////
			char *coord,*scr;
			sprintf(coord,"%d,%d",i,j);
			
			if (current_player==BlackPlayer)
			{
				PrintTextInWindow(rectBlackIndex,coord,50,0,0,0);
				rectBlackIndex.y+=40;
			}
			else
			{
				PrintTextInWindow(rectWhiteIndex,coord,50,0,0,0);
				rectWhiteIndex.y+=40;
			}
			MakeChange(i,j);

			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)
					if(BOARD[i][j].imgPATH==PlayableCasePATH)
						{DrawCaseImg(BOARD[i][j],EmptyCasePATH)}

			SDL_SetRenderDrawColor(renderer,128,255,128,0);
			
			SDL_RenderFillRect(renderer,&rectBlackScore);
			sprintf(scr,"  %d",NbrCase(BlackCasePATH));
			PrintTextInWindow(rectBlackScore,scr,50,0,0,0);

			SDL_RenderFillRect(renderer,&rectWhiteScore);
			sprintf(scr,"%d  ",NbrCase(WhiteCasePATH));
			PrintTextInWindow(rectWhiteScore,scr,50,255,255,255);
			//////////////////////////////////////////////////////////////
			current_player=(current_player+1)%2;

			if(EveryPlayableCases()==0)
				current_player=(current_player+1)%2;
		}
}


#endif