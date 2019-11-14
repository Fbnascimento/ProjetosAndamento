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

    SDL_Surface *BLOCO = NULL;

    SDL_Surface *PAREDE = NULL;

    SDL_Surface *MAPA1 = NULL;

    SDL_Event event;

    int continuar = 1;
    int i = 0, j = 0;

    int mapa [13][15];

    //PAREDE ESQUERDA

    mapa[0][0] = 1;
    mapa[1][0] = 1;
    mapa[2][0] = 1;
    mapa[3][0] = 1;
    mapa[4][0] = 1;
    mapa[5][0] = 1;
    mapa[6][0] = 1;
    mapa[7][0] = 1;
    mapa[8][0] = 1;
    mapa[9][0] = 1;
    mapa[10][0] = 1;
    mapa[11][0] = 1;
    mapa[12][0] = 1;

    //PAREDE DIREITA

    mapa[0][14] = 1;
    mapa[1][14] = 1;
    mapa[2][14] = 1;
    mapa[3][14] = 1;
    mapa[4][14] = 1;
    mapa[5][14] = 1;
    mapa[6][14] = 1;
    mapa[7][14] = 1;
    mapa[8][14] = 1;
    mapa[9][14] = 1;
    mapa[10][14] = 1;
    mapa[11][14] = 1;
    mapa[12][14] = 1;

    //PARADE CIMA

    mapa[0][1] = 1;
    mapa[0][2] = 1;
    mapa[0][3] = 1;
    mapa[0][4] = 1;
    mapa[0][5] = 1;
    mapa[0][6] = 1;
    mapa[0][7] = 1;
    mapa[0][8] = 1;
    mapa[0][9] = 1;
    mapa[0][10] = 1;
    mapa[0][11] = 1;
    mapa[0][12] = 1;
    mapa[0][13] = 1;
    mapa[0][14] = 1;

    //PAREDE BAIXO

    mapa[12][1] = 1;
    mapa[12][2] = 1;
    mapa[12][3] = 1;
    mapa[12][4] = 1;
    mapa[12][5] = 1;
    mapa[12][6] = 1;
    mapa[12][7] = 1;
    mapa[12][8] = 1;
    mapa[12][9] = 1;
    mapa[12][10] = 1;
    mapa[12][11] = 1;
    mapa[12][12] = 1;
    mapa[12][13] = 1;
    mapa[12][14] = 1;
    mapa[2][2] = 1;

    //LINHA DE PAREDE INTERNA 1

    mapa[2][4] = 1;
    mapa[2][6] = 1;
    mapa[2][8] = 1;
    mapa[2][10] = 1;
    mapa[2][12] = 1;

    //LINHA DE PAREDE INTERNA 2

    mapa[4][2] = 1;
    mapa[4][4] = 1;
    mapa[4][6] = 1;
    mapa[4][8] = 1;
    mapa[4][10] = 1;
    mapa[4][12] = 1;

    //LINHA DE PAREDE INTERNA 3

    mapa[6][2] = 1;
    mapa[6][4] = 1;
    mapa[6][6] = 1;
    mapa[6][8] = 1;
    mapa[6][10] = 1;
    mapa[6][12] = 1;

    //LINHA DE PAREDE INTERNA 4

    mapa[8][2] = 1;
    mapa[8][4] = 1;
    mapa[8][6] = 1;
    mapa[8][8] = 1;
    mapa[8][10] = 1;
    mapa[8][12] = 1;

    //LINHA DE PAREDE INTERNA 5

    mapa[10][2] = 1;
    mapa[10][4] = 1;
    mapa[10][6] = 1;
    mapa[10][8] = 1;
    mapa[10][10] = 1;
    mapa[10][12] = 1;

    //LADO INICIAL PLAYER 1

    mapa[1][1] = 0;
    mapa[1][2] = 0;
    mapa[2][1] = 0;

    //LADO INICIAL PLAYER 2

    mapa[11][13] = 0;
    mapa[11][12] = 0;
    mapa[10][13] = 0;

    //BLOCOS DESTRUÍVES

    mapa[1][3] = 2;
    mapa[1][4] = 2;
    mapa[1][5] = 2;
    mapa[1][6] = 2;
    mapa[1][6] = 2;
    mapa[1][8] = 2;
    mapa[1][9] = 2;
    mapa[1][10] = 2;
    mapa[1][11] = 2;
    mapa[1][12] = 2;
    mapa[1][13] = 2;
    mapa[2][3] = 2;
    mapa[2][5] = 2;
    mapa[2][7] = 2;
    mapa[2][9] = 2;
    mapa[2][11] = 2;
    mapa[2][13] = 2;
    mapa[3][1] = 2;
    mapa[3][2] = 2;
    mapa[3][3] = 2;
    mapa[3][4] = 2;
    mapa[3][5] = 2;
    mapa[3][6] = 2;
    mapa[3][6] = 2;
    mapa[3][8] = 2;
    mapa[3][9] = 2;
    mapa[3][10] = 2;
    mapa[3][11] = 2;
    mapa[3][12] = 2;
    mapa[3][13] = 2;
    mapa[4][1] = 2;
    mapa[4][3] = 2;
    mapa[4][5] = 2;
    mapa[4][7] = 2;
    mapa[4][9] = 2;
    mapa[4][11] = 2;
    mapa[4][13] = 2;

    mapa[5][1] = 2;
    mapa[5][2] = 2;
    mapa[5][3] = 2;
    mapa[5][4] = 2;
    mapa[5][5] = 2;
    mapa[5][6] = 2;
    mapa[5][6] = 2;
    mapa[5][8] = 2;
    mapa[5][9] = 2;
    mapa[5][10] = 2;
    mapa[5][11] = 2;
    mapa[5][12] = 2;
    mapa[5][13] = 2;
    mapa[6][1] = 2;
    mapa[6][3] = 2;
    mapa[6][5] = 2;
    mapa[6][7] = 2;
    mapa[6][9] = 2;
    mapa[6][11] = 2;
    mapa[6][13] = 2;

    mapa[7][1] = 2;
    mapa[7][2] = 2;
    mapa[7][3] = 2;
    mapa[7][4] = 2;
    mapa[7][5] = 2;
    mapa[7][6] = 2;
    mapa[7][6] = 2;
    mapa[7][8] = 2;
    mapa[7][9] = 2;
    mapa[7][10] = 2;
    mapa[7][11] = 2;
    mapa[7][12] = 2;
    mapa[7][13] = 2;

    mapa[8][1] = 2;
    mapa[8][3] = 2;
    mapa[8][5] = 2;
    mapa[8][7] = 2;
    mapa[8][9] = 2;
    mapa[8][11] = 2;
    mapa[8][13] = 2;

    mapa[9][1] = 2;
    mapa[9][2] = 2;
    mapa[9][3] = 2;
    mapa[9][4] = 2;
    mapa[9][5] = 2;
    mapa[9][6] = 2;
    mapa[9][6] = 2;
    mapa[9][8] = 2;
    mapa[9][9] = 2;
    mapa[9][10] = 2;
    mapa[9][11] = 2;
    mapa[9][12] = 2;
    mapa[9][13] = 2;

    mapa[10][1] = 2;
    mapa[10][3] = 2;
    mapa[10][5] = 2;
    mapa[10][7] = 2;
    mapa[10][9] = 2;
    mapa[10][11] = 2;

    mapa[11][1] = 2;
    mapa[11][2] = 2;
    mapa[11][3] = 2;
    mapa[11][4] = 2;
    mapa[11][5] = 2;
    mapa[11][6] = 2;
    mapa[11][6] = 2;
    mapa[11][8] = 2;
    mapa[11][9] = 2;
    mapa[11][10] = 2;
    mapa[11][11] = 2;

    //POSIÇÃO PLAYER 1

    mapa[1][1] = 3;

    BLOCO = IMG_Load("Bloco.bmp");

    MAPA1 = IMG_Load("Mapa1.bmp");

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
                JOGADOR1Atual = JOGADOR1[CIMA];
                movimentoJogador1(mapa, &positionPlayer1, CIMA);
                break;

                case SDLK_DOWN:
                JOGADOR1Atual = JOGADOR1[BAIXO];
                movimentoJogador1(mapa, &positionPlayer1, BAIXO);
                break;

                case SDLK_RIGHT:
                JOGADOR1Atual = JOGADOR1[DIREITA];
                movimentoJogador1(mapa, &positionPlayer1, DIREITA);
                break;

                case SDLK_LEFT:
                JOGADOR1Atual = JOGADOR1[ESQUERDA];
                movimentoJogador1(mapa, &positionPlayer1, ESQUERDA);
                break;
            }

        break;
        }

        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran -> format,255,255,255));

        for (i = 0; i < 13; i++)
        {
            for (j = 0; j < 15; j++)
            {
                position.x = j*TAMANHO_BLOCO;
                position.y = i*TAMANHO_BLOCO;

                if(mapa[i][j]== PAREDE)
                {
                    SDL_BlitSurface(PAREDE, NULL, ecran, &position);
                    break;

                }
            }
        }

        position.x = positionPlayer1.x*TAMANHO_BLOCO;
        position.y = positionPlayer1.y*TAMANHO_BLOCO;

        SDL_BlitSurface(JOGADOR1Atual,NULL,ecran,&position);

        SDL_Flip(ecran);

    }

    SDL_EnableKeyRepeat(0,0);

    SDL_FreeSurface(PAREDE);

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

        if (mapa[pos -> y - 1][pos -> x]== PAREDE)
            {
                break;
            }

        pos-> y--;
        break;

        case BAIXO:

        if (mapa[pos -> y + 1][pos -> x]== PAREDE)
            {
                break;
            }

        pos-> y++;
        break;

        case ESQUERDA:

        if (mapa[pos -> y][pos -> x - 1]== PAREDE)
            {
                break;
            }

        pos-> x--;
        break;

        case DIREITA:

        if (mapa[pos -> y][pos -> x + 1]== PAREDE)
            {
                break;
            }

        pos-> x++;
        break;
    }
}
