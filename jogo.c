#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <pthread.h>

#include "jogo.h"
#include "constante.h"

typedef struct
{
    int **mapa1;
    SDL_Surface* ecran1;
}listearg;

listearg liste;

void TecladoAtualizado(Teclas* estado_teclado)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
            estado_teclado -> key[event.key.keysym.sym] = 1;
            break;

            case SDL_KEYUP:
            estado_teclado -> key[event.key.keysym.sym] = 0;
            break;

            default:
            break;
        }
    }
}

SDL_Rect position, positionPlayer1;
SDL_Rect position2, positionPlayer2;

void jogar(SDL_Surface* ecran)
{
    Teclas estado_teclado;
    memset(&estado_teclado, 0, sizeof(estado_teclado));

    SDL_Surface *JOGADOR1[4] = {NULL};
    SDL_Surface *JOGADOR2[4] = {NULL};

    SDL_Surface *JOGADOR1Atual = NULL;
    SDL_Surface *JOGADOR2Atual = NULL;

    SDL_Surface *BLOCO = NULL;

    SDL_Rect positionCENARIO1;
    SDL_Surface *CENARIO1 = NULL;

    SDL_Event event;

    int continuar = 1;
    int i = 0, j = 0;

    int **mapa = (int**)malloc(13*sizeof(int*));

    for(i = 0; i < 13; i++)
    {
        mapa[i] = (int*)malloc((15*sizeof(int)));
    }

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

    /*BLOCOS DESTRUÍVES

    mapa[1][3] = 2;
    mapa[1][4] = 2;
    mapa[1][5] = 2;
    mapa[1][6] = 2;
    mapa[1][6] = 2;
    mapa[1][7] = 2;
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
    mapa[3][7] = 2;
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
    mapa[5][7] = 2;
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
    mapa[7][7] = 2;
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
    mapa[9][7] = 2;
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
    mapa[11][7] = 2;
    mapa[11][8] = 2;
    mapa[11][9] = 2;
    mapa[11][10] = 2;
    mapa[11][11] = 2;*/

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_Music *musicabatalha;
    musicabatalha = Mix_LoadMUS("Batalha.mp3");

    JOGADOR1[BAIXO] = IMG_Load("BombermanF.bmp");
    JOGADOR1[ESQUERDA] = IMG_Load("BombermanE.bmp");
    JOGADOR1[DIREITA] = IMG_Load("BombermanD.bmp");
    JOGADOR1[CIMA] = IMG_Load("BombermanC.bmp");

    JOGADOR2[BAIXO] = IMG_Load("BombermanBF.bmp");
    JOGADOR2[ESQUERDA] = IMG_Load("BombermanBE.bmp");
    JOGADOR2[DIREITA] = IMG_Load("BombermanBD.bmp");
    JOGADOR2[CIMA] = IMG_Load("BombermanBC.bmp");

    BLOCO = IMG_Load("Bloco.bmp");
    CENARIO1 = IMG_Load("Cenario1.bmp");

    JOGADOR1Atual = JOGADOR1[BAIXO];
    JOGADOR2Atual = JOGADOR2[BAIXO];

    positionPlayer1.x = 1;
    positionPlayer1.y = 1;

    positionPlayer2.x = 13;
    positionPlayer2.y = 11;

    //POSIÇÃO PLAYERS

    mapa[1][1] = JOGADOR1;
    mapa[11][13] = JOGADOR2;

    Mix_PlayMusic(musicabatalha, -1);

    while(continuar)
    {
        TecladoAtualizado(&estado_teclado);

        if (estado_teclado.key[SDLK_UP])
        {
            JOGADOR1Atual = JOGADOR1[CIMA];
            movimentoJogador(mapa, &positionPlayer1, CIMA);
        }
        if (estado_teclado.key[SDLK_DOWN])
        {
            JOGADOR1Atual = JOGADOR1[BAIXO];
            movimentoJogador(mapa, &positionPlayer1, BAIXO);
        }
        if (estado_teclado.key[SDLK_RIGHT])
        {
            JOGADOR1Atual = JOGADOR1[DIREITA];
            movimentoJogador(mapa, &positionPlayer1, DIREITA);
        }
        if (estado_teclado.key[SDLK_LEFT])
        {
            JOGADOR1Atual = JOGADOR1[ESQUERDA];
            movimentoJogador(mapa, &positionPlayer1, ESQUERDA);
        }
        if (estado_teclado.key[SDLK_m])
        {
            criacao_bomba (mapa, ecran);
;       }


        if (estado_teclado.key[SDLK_w])
        {
            JOGADOR2Atual = JOGADOR2[CIMA];
            movimentoJogador(mapa, &positionPlayer2, CIMA);
        }
        if (estado_teclado.key[SDLK_s])
        {
            JOGADOR2Atual = JOGADOR2[BAIXO];
            movimentoJogador(mapa, &positionPlayer2, BAIXO);
        }
        if (estado_teclado.key[SDLK_d])
        {
            JOGADOR2Atual = JOGADOR2[DIREITA];
            movimentoJogador(mapa, &positionPlayer2, DIREITA);
        }
        if (estado_teclado.key[SDLK_a])
        {
            JOGADOR2Atual = JOGADOR2[ESQUERDA];
            movimentoJogador(mapa, &positionPlayer2, ESQUERDA);
        }

        if (estado_teclado.key[SDLK_ESCAPE])
        {
            continuar = 0;
        }

        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran -> format,255,255,255));

        positionCENARIO1.x = 0;
        positionCENARIO1.y = 18;

        SDL_BlitSurface(CENARIO1, NULL, ecran, &positionCENARIO1);

//        for (i = 1; i < 13; i++)
//        {
//            for (j = 1; j < 15; j++)
//            {
//               position.x = j*TAMANHO_BLOCO;
//               position.y = i*TAMANHO_BLOCO+16;
//
//                if(mapa[i][j] == 2)
//                {
//                    SDL_BlitSurface(BLOCO, NULL, ecran, &position);
//                }
//            }
//        }

        position.x = positionPlayer1.x*TAMANHO_BLOCO;
        position.y = positionPlayer1.y*TAMANHO_BLOCO;

        SDL_BlitSurface(JOGADOR1Atual,NULL,ecran,&position);

        position2.x = positionPlayer2.x*TAMANHO_BLOCO;
        position2.y = positionPlayer2.y*TAMANHO_BLOCO;

        SDL_BlitSurface(JOGADOR2Atual,NULL,ecran,&position2);

        usleep(200000);

        SDL_Flip(ecran);
    }

    SDL_FreeSurface(BLOCO);

    for(i = 0; i < 4; i++)
    {
        SDL_FreeSurface(JOGADOR1[i]);
    }

    for(i = 0; i < 4; i++)
    {
        SDL_FreeSurface(JOGADOR2[i]);
    }
}

void movimentoJogador(int **mapa, SDL_Rect *pos, int direcao)
{
    switch(direcao)
    {
        case CIMA:

        if (mapa[pos -> y - 1][pos -> x] == PAREDE)
        {
            break;
        }
        if (mapa[pos -> y - 1][pos -> x] == BLOCO)
        {
            break;
        }

        pos-> y--;
        break;

        case BAIXO:

        if (mapa[pos -> y + 1][pos -> x] == PAREDE)
        {
            break;
        }
        if (mapa[pos -> y + 1][pos -> x] == BLOCO)
        {
            break;
        }
        pos-> y++;
        break;

        case ESQUERDA:

        if (mapa[pos -> y][pos -> x - 1] == PAREDE)
        {
            break;
        }
        if (mapa[pos -> y][pos -> x - 1] == BLOCO)
        {
            break;
        }

        pos-> x--;
        break;

        case DIREITA:

        if (mapa[pos -> y][pos -> x + 1] == PAREDE)
        {
            break;
        }
        if (mapa[pos -> y][pos -> x + 1] == BLOCO)
        {
            break;
        }

        pos-> x++;
        break;
    }
}

void criacao_bomba (int **mapa, SDL_Surface* ecran)
{
    pthread_t thread1;

    liste.mapa1 = mapa;
    liste.ecran1 = ecran;

    pthread_create(&thread1, NULL, gestion_bomba, (void*)&liste);

}

void *gestion_bomba(void*arg)
{
    listearg *args = (listearg*)arg;
    int **mapa1 = args -> mapa1;

    {

    }

    pthread_exit(NULL);
}
