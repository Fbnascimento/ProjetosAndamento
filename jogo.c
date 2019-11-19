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

//CRIAÇÃO BOMBAS NA TELA
SDL_Rect positionBomba;
SDL_Rect positionExplosaoD;
SDL_Rect positionExplosaoE;
SDL_Rect positionExplosaoB;
SDL_Rect positionExplosaoC;
SDL_Rect positionExplosaoM;

//TECLADO PARA OS 2 PLAYERS SEM CONFLITO
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

//CRICAÇÃO DAS POSIÇÕES DOS PLAYERS
SDL_Rect position, positionPlayer1;
SDL_Rect position2, positionPlayer2;

//FUNÇÃO DO JOGO
void jogar(SDL_Surface* ecran)
{
    Teclas estado_teclado;
    memset(&estado_teclado, 0, sizeof(estado_teclado));

//CRICAÇÃO DAS IMAGENS
    SDL_Surface *JOGADOR1[4] = {NULL};
    SDL_Surface *JOGADOR2[4] = {NULL};

    SDL_Surface *JOGADOR1Atual = NULL;
    SDL_Surface *JOGADOR2Atual = NULL;

    SDL_Surface *BLOCO = NULL;

//CRIAÇÃO DA POSIÇÃO DO CENÁRIO E DA SUA IMAGEM
    SDL_Rect positionCENARIO;
    SDL_Surface *CENARIO = NULL;

    SDL_Event event;

//CRIAÇÃO DAS IMAGENS DE BOMBAS E EXPLOSÃO
    SDL_Surface *BOMBA = NULL;
    SDL_Surface *EXPLOSAOB = NULL;
    SDL_Surface *EXPLOSAOC = NULL;
    SDL_Surface *EXPLOSAOD = NULL;
    SDL_Surface *EXPLOSAOE = NULL;
    SDL_Surface *EXPLOSAOM = NULL;

    int continuar = 1;
    int i = 0, j = 0;

//CRIAÇÃO DO MAPA
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

//BLOCOS DESTRUÍVES
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
    mapa[11][11] = 2;

//CRIAÇÃO DA MÚSICA DE BATALHA
/*  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_Music *musicabatalha;
    musicabatalha = Mix_LoadMUS("Batalha.mp3");*/

//CARREGAMENTO DAS IMAGENS
    BOMBA = IMG_Load("Bomba2.bmp");
    EXPLOSAOB = IMG_Load("ExplosaoB.bmp");
    EXPLOSAOC = IMG_Load("ExplosaoC.bmp");
    EXPLOSAOD = IMG_Load("ExplosaoD.bmp");
    EXPLOSAOE = IMG_Load("ExplosaoE.bmp");
    EXPLOSAOM = IMG_Load("ExplosaoM.bmp");

    JOGADOR1[BAIXO] = IMG_Load("BombermanF.png");
    JOGADOR1[ESQUERDA] = IMG_Load("BombermanE.png");
    JOGADOR1[DIREITA] = IMG_Load("BombermanD.png");
    JOGADOR1[CIMA] = IMG_Load("BombermanC.png");

    JOGADOR2[BAIXO] = IMG_Load("BombermanBF.png");
    JOGADOR2[ESQUERDA] = IMG_Load("BombermanBE.png");
    JOGADOR2[DIREITA] = IMG_Load("BombermanBD.png");
    JOGADOR2[CIMA] = IMG_Load("BombermanBC.png");

    BLOCO = IMG_Load("Bloco.png");
    CENARIO = IMG_Load("Cenario.bmp");

    JOGADOR1Atual = JOGADOR1[BAIXO];
    JOGADOR2Atual = JOGADOR2[BAIXO];

//POSIÇÃO DOS JOGADORES NA TELA
    positionPlayer1.x = 1;
    positionPlayer1.y = 1;

    positionPlayer2.x = 13;
    positionPlayer2.y = 11;

//POSIÇÃO DOS JOGADORES NA MATRIX

    mapa[1][1] = JOGADOR1;
    mapa[11][13] = JOGADOR2;

//    Mix_PlayMusic(musicabatalha, -1);

//MOVIMENTAÇÃO DOS JOGADORES
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
        }


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
        if (estado_teclado.key[SDLK_p])
        {
            criacao_bomba (mapa, ecran);
        }

        if (estado_teclado.key[SDLK_ESCAPE])
        {
            continuar = 0;
        }

        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran -> format,0,0,0));

//POSIÇÃO DO CENARIO NA TELA
        positionCENARIO.x = 0;
        positionCENARIO.y = 23;

        SDL_BlitSurface(CENARIO, NULL, ecran, &positionCENARIO);

//CRIAÇÃO DOS BLOCOS DESTRUÍVEIS100000
        for (i = 1; i < 13; i++)
        {
            for (j = 1; j < 15; j++)
            {
               position.x = j*TAMANHO_BLOCO;
               position.y = i*TAMANHO_BLOCO+24;

                switch(mapa[i][j])
                {
                    case 2:
                    SDL_BlitSurface(BLOCO, NULL, ecran, &position);
                    break;

                    case 5:
                    SDL_BlitSurface(BOMBA, NULL, ecran, &position);
                    break;

                    case 10:
                    SDL_BlitSurface(EXPLOSAOM, NULL, ecran, &position);
                    break;

                    case 6:
                    SDL_BlitSurface(EXPLOSAOB, NULL, ecran, &position);
                    break;

                    case 7:
                    SDL_BlitSurface(EXPLOSAOC, NULL, ecran, &position);
                    break;

                    case 8:
                    SDL_BlitSurface(EXPLOSAOD, NULL, ecran, &position);
                    break;

                    case 9:
                    SDL_BlitSurface(EXPLOSAOE, NULL, ecran, &position);
                    break;
                }
            }
        }

        position.x = positionPlayer1.x*TAMANHO_BLOCO;
        position.y = positionPlayer1.y*TAMANHO_BLOCO;

        SDL_BlitSurface(JOGADOR1Atual,NULL,ecran,&position);

        position2.x = positionPlayer2.x*TAMANHO_BLOCO;
        position2.y = positionPlayer2.y*TAMANHO_BLOCO;

        SDL_BlitSurface(JOGADOR2Atual,NULL,ecran,&position2);

//VELOCIDADE DE MOVIMENTO DOS JOGADORES
        usleep(150000);

        SDL_Flip(ecran);
    }

//LIBERAÇÃO DAS IMAGENS NA TELA
    SDL_FreeSurface(BLOCO);

    for(i = 0; i < 4; i++)
    {
        SDL_FreeSurface(JOGADOR1[i]);
    }

    for(i = 0; i < 4; i++)
    {
        SDL_FreeSurface(JOGADOR2[i]);
    }

    SDL_FreeSurface(BOMBA);
    SDL_FreeSurface(EXPLOSAOB);
    SDL_FreeSurface(EXPLOSAOC);
    SDL_FreeSurface(EXPLOSAOD);
    SDL_FreeSurface(EXPLOSAOE);
    SDL_FreeSurface(EXPLOSAOM);

}

//COLISÃO DOS JOGADORES COM CENÁRIO E BLOCOS
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

//CRIAÇÃO DA BOMBA
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

    mapa1[positionPlayer1.y][positionPlayer1.x] = BOMBA;

    SDL_Delay(3000);

    int a, b = 0;

    for(a = 1; a < 13; a++)//1551511515
    {
        for (b = 1; b < 15; b++)
        {
            if (mapa1[a][b] == 5)
            {
                mapa1[a][b] = 10;

                if (mapa1[a+1][b] != 2)
                {
                    mapa1[a+1][b] = 6;
                }
                if (mapa1[a+1][b] != mapa1[positionPlayer1.y][positionPlayer1.x])
                {
                    mapa1[a+1][b] = 6;
                }
                if (mapa1[a+1][b] != mapa1[positionPlayer2.y][positionPlayer2.x])
                {
                    mapa1[a+1][b] = 6;
                }
                if (mapa1[a+1][b] != 3)
                {
                    mapa1[a+1][b] = 6;
                }

                if (mapa1[a-1][b] != 2)
                {
                    mapa1[a-1][b] = 7;
                }
                if (mapa1[a-1][b] != mapa1[positionPlayer1.y][positionPlayer1.x])
                {
                    mapa1[a-1][b] = 7;
                }
                if (mapa1[a-1][b] != mapa1[positionPlayer2.y][positionPlayer2.x])
                {
                    mapa1[a-1][b] = 7;
                }
                if (mapa1[a-1][b] != 3)
                {
                    mapa1[a-1][b] = 7;
                }

                if (mapa1[a][b+1] != 2)
                {
                    mapa1[a][b+1] = 8;
                }
                if (mapa1[a][b+1] != mapa1[positionPlayer1.y][positionPlayer1.x])
                {
                    mapa1[a][b+1] = 8;
                }
                if (mapa1[a][b+1] != mapa1[positionPlayer2.y][positionPlayer2.x])
                {
                    mapa1[a][b+1] = 8;
                }
                if (mapa1[a][b+1] != 3)
                {
                    mapa1[a][b+1] = 8;
                }

                if (mapa1[a][b-1] != 2)
                {
                    mapa1[a][b-1] = 9;
                }
                if (mapa1[a][b-1] != mapa1[positionPlayer1.y][positionPlayer1.x])
                {
                    mapa1[a][b-1] = 9;
                }
                if (mapa1[a][b-1] != mapa1[positionPlayer2.y][positionPlayer2.x])
                {
                    mapa1[a][b-1] = 9;
                }
                if (mapa1[a][b-1] != 3)
                {
                    mapa1[a][b-1] = 9;
                }
            }
        }
    }
    SDL_Delay(150);

    for (a = 1; a < 13; a++)
    {
        for (b = 1; b < 15; b++)
        {
            if (mapa1[a][b] == 10)
            {
                mapa1[a][b] = 0;
            }
            if (mapa1[a][b] == 6)
            {
                mapa1[a][b] = 0;
            }
            if (mapa1[a][b] == 7)
            {
                mapa1[a][b] = 0;
            }
            if (mapa1[a][b] == 8)
            {
                mapa1[a][b] = 0;
            }
            if (mapa1[a][b] == 9)
            {
                mapa1[a][b] = 0;
            }
        }
    }
    pthread_exit(NULL);
}
