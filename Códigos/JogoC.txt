#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>

#include "jogo.h"
#include "constante.h"

SDL_Rect position, positionPlayer1;

void jogar(SDL_Surface* ecran)
{
   SDL_Surface *JOGADOR1[4] = {NULL};
   SDL_Surface *JOGADOR1Atual = NULL;

   SDL_Event event;

   int continuar = 1;
   int i = 0, j = 0;

   int mapa [13][15];

   JOGADOR1[BAIXO] = IMG_Load("Bomberman1.bmp");
   JOGADOR1[ESQUERDA] = IMG_Load("Bomberman2.bmp");
   JOGADOR1[DIREITA] = IMG_Load("Bomberman3.bmp");
   JOGADOR1[CIMA] = IMG_Load("Bomberman4.bmp");

   JOGADOR1Atual = JOGADOR1[BAIXO];

   positionPlayer1.x = 3;
   positionPlayer1.y = 3;

    SDL_EnableKeyRepeat(100,100);

   while(continuar)
   {
    SDL_WaitEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
        continuar = 0;
        break;

        case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
            continuar = 0;
            break;

            case SDLK_UP:
            movimentoJogador1(mapa, &positionPlayer1, CIMA);
            break;

            case SDLK_DOWN:
            movimentoJogador1(mapa, &positionPlayer1, BAIXO);
            break;

            case SDLK_RIGHT:
            movimentoJogador1(mapa, &positionPlayer1, DIREITA);
            break;

            case SDLK_LEFT:
            movimentoJogador1(mapa, &positionPlayer1, ESQUERDA);
            break;
        }
        break;
    }

   SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));

   position.x = positionPlayer1.x*TAMANHO_BLOCO;
   position.y = positionPlayer1.y*TAMANHO_BLOCO;

   SDL_BlitSurface(JOGADOR1Atual,NULL,ecran,&position);

   SDL_Flip(ecran);

   }

   SDL_EnableKeyRepeat(0,0);

   for(i = 0; i < 4; i++)
   {
        SDL_FreeSurface(JOGADOR1[i]);
   }

}

void movimentoJogador1(int mapa[][15], SDL_Rect *pos, int direcao)
{

    switch(direcao)
    {
        case CIMA:
        pos-> y--;
        break;

        case BAIXO:
        pos-> y++;
        break;

        case ESQUERDA:
        pos-> x--;
        break;

        case DIREITA:
        pos-> x++;
        break;
    }

}
