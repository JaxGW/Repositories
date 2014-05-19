#include <SDL.h>
#include "SDL_opengl.h"
#include <stdlib.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
using namespace std;

#include "postac.h"
CPostac ludek1;

SDL_Surface * ekran = NULL;
SDL_Surface * ludek = NULL;
SDL_Surface * tlo = NULL;
SDL_Surface * butelka = NULL;
SDL_Surface * butelka1 = NULL;
SDL_Surface * ogien = NULL;
SDL_Surface * przycisk = NULL;
SDL_Surface * kursor = NULL;

SDL_Event zdarzenie;

SDL_Rect LudekDestination;
SDL_Rect butelkaDestination;
SDL_Rect butelka1Destination;
SDL_Rect ogienDestination;
SDL_Rect przyciskDane;
SDL_Rect przyciskCel;
SDL_Rect kursorDane;
SDL_Rect butelkaDane;

Uint8 * keystate = SDL_GetKeyState( NULL );

int x, y, xBottle, yBottle, xBottle1, yBottle1, myszkaX, myszkaY;
int kursorX, kursorY;
int bulletx, bullety;
int bulletvx, bulletvy;

bool wyjscie = false;
bool CzyStrzelono = 1;
bool CzyStrzelonoMyszka = 1;


Uint32 start=0, startStrzaluMyszka=0;

double delta=0, delta1;
double bulletdx, bulletdy;
double deltaX,deltaY;
double dlugosc;



 
int main (int argc, char *argv[])
{
	
	//cout<<SDL_GetTicks();
	

SDL_Init( SDL_INIT_EVERYTHING );
    ekran = SDL_SetVideoMode( 800, 600, 32, SDL_SWSURFACE | SDL_DOUBLEBUF );
	tlo = SDL_LoadBMP( "tlo.bmp" );
    przycisk = SDL_LoadBMP( "przycisk.bmp" );
    kursor = SDL_LoadBMP( "kursor.bmp" );
	butelka = SDL_LoadBMP( "butelka.bmp" );
	butelka1 = SDL_LoadBMP( "butelka.bmp" );
	ogien = SDL_LoadBMP( "ogien.bmp" );
    przyciskDane.w = 50;
    przyciskDane.h = 50;
	przyciskCel.x = 750;
    przyciskCel.y = 0;
    kursorDane.x = 0;
    kursorDane.y = 0;
	ludek = SDL_LoadBMP( "ludek.bmp" );
	

 while( !wyjscie )
    {
       
		
		SDL_FillRect( ekran, NULL, 0 );
		SDL_BlitSurface( tlo, NULL, ekran, NULL );
        SDL_ShowCursor( SDL_DISABLE );
        SDL_BlitSurface( przycisk, & przyciskDane, ekran, & przyciskCel );
        SDL_BlitSurface( kursor, NULL, ekran, & kursorDane );
        SDL_Flip( ekran );
		
		
		while( SDL_PollEvent( & zdarzenie ) )
        {
            if( zdarzenie.type == SDL_QUIT )
            {
                wyjscie = true;
            }

			 if( zdarzenie.type == SDL_MOUSEMOTION )
            {
                kursorDane.x = zdarzenie.motion.x;
                kursorDane.y = zdarzenie.motion.y;
				
            }
            if( zdarzenie.type == SDL_MOUSEBUTTONDOWN )
            {
                if( zdarzenie.button.button == SDL_BUTTON_LEFT &&
                ( kursorDane.x >= przyciskCel.x && kursorDane.x <= przyciskCel.x + przyciskDane.w ) &&
				( kursorDane.y >= przyciskCel.y && kursorDane.y <= przyciskCel.y + przyciskDane.h ) )
                {
                    wyjscie = true;
                }
				
				CzyStrzelonoMyszka=0;
				startStrzaluMyszka=SDL_GetTicks(); 

				xBottle1=xBottle;
                yBottle1=yBottle;
				bulletx=xBottle;
				bullety=yBottle;
                kursorX=kursorDane.x;
				kursorY=kursorDane.y;
            }
            if( zdarzenie.key.keysym.sym == SDLK_ESCAPE ) 
			{
				wyjscie = true;
			}
        }
        if( keystate[ SDLK_d ] )
        {
            if(x<700)
			{
			x=x+5;
			}
        }
		if( keystate[ SDLK_a ] )
        {
			if(x>0)
			{
            x=x-5;
			}
        }
		if( keystate[ SDLK_w ] )
        {
           if(y>0)
		   {
			y=y-5;
		   }
        }
		if( keystate[ SDLK_s ] )
        {
            if(y<500)
			{
			y=y+5;
			}
        }
		if( keystate[ SDLK_SPACE] )
        {
			xBottle=x+70;
			yBottle=y+25;
			CzyStrzelono=0;
			start=SDL_GetTicks(); 
        }
        
		
		//Strzelanie space
		if(CzyStrzelono==1)
		{
		xBottle=x+70;
		yBottle=y+25;
		butelkaDestination.x = xBottle;
		butelkaDestination.y = yBottle;
		}
		if(CzyStrzelono==0)
		{
			delta=(SDL_GetTicks()-start)/2;
			xBottle=xBottle+delta/5;
			yBottle=yBottle-20*sin(45*3.14/180)+delta/5;
			if(yBottle>(y+50))
			{
				CzyStrzelono=1;
				ogienDestination.x = xBottle;
				ogienDestination.y = yBottle;
				SDL_BlitSurface( ogien, NULL, ekran, & ogienDestination );	
			}
			butelkaDestination.x = xBottle;
			butelkaDestination.y = yBottle;
		}

		//Strzelanie myszka
		if(CzyStrzelonoMyszka==1)
		{
			bulletx=x+70;
			bullety=y+25;
			butelka1Destination.x = bulletx;
			butelka1Destination.y = bullety;
		}
		if(CzyStrzelonoMyszka==0)
		{
		delta1=(SDL_GetTicks()-startStrzaluMyszka)/5;
		deltaX = kursorX - xBottle1; // delta to wektor w kierunku od punktu startowego do celu
		deltaY = kursorY - yBottle1;
		dlugosc = sqrt(deltaX * deltaX + deltaY * deltaY); // obliczamy d�ugo�� wektora
		deltaX /= dlugosc; // normalizujemy wektor delta, tzn jego d�ugo�� b�dzie teraz r�wna 1
		deltaY /= dlugosc;
		bulletx += deltaX*delta1;
		bullety += deltaY*delta1;
        butelka1Destination.x = bulletx;
		butelka1Destination.y = bullety;
		}
		
		
		LudekDestination.x = x;
		LudekDestination.y = y;
        SDL_BlitSurface( ludek, NULL, ekran, & LudekDestination );
        SDL_BlitSurface( butelka, NULL, ekran, & butelkaDestination );
        SDL_BlitSurface( butelka1, NULL, ekran, & butelka1Destination );
		SDL_Flip( ekran );
    }
	SDL_FreeSurface( ludek );
	SDL_FreeSurface( przycisk );
    SDL_FreeSurface( kursor );
	SDL_FreeSurface( tlo );
    SDL_Quit();
    return 0;
return 0;
}