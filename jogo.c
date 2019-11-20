#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <pthread.h>

#include "jogo.h"
#include "constante.h"

//ESTRUTURAS PARA AS BOMBAS NA TELA
typedef struct
{
int **MapaBombaJ1;
    SDL_Surface* TelaBombaJ1;
}BombaJ1;

BombaJ1 J1;

typedef struct
{
int **MapaBombaJ2;
    SDL_Surface* TelaBombaJ1;
}BombaJ2;

BombaJ2 J2;

//CRIAÇÃO DAS BOMBAS NA TELA
SDL_Rect PosicaoBomba;
SDL_Rect PosicaoExplosaoD;
SDL_Rect PosicaoExplosaoE;
SDL_Rect PosicaoExplosaoB;
SDL_Rect PosicaoExplosaoC;
SDL_Rect PosicaoExplosaoM;

//TECLADO PARA OS 2 PLAYERS SEM CONFLITO
void TecladoAtualizado(Teclas* Estado_Teclado)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
            Estado_Teclado -> key[event.key.keysym.sym] = 1;
            break;

            case SDL_KEYUP:
            Estado_Teclado -> key[event.key.keysym.sym] = 0;
            break;

            default:
            break;
        }
    }
}

//CRICAÇÃO DAS POSIÇÕES DOS PLAYERS
SDL_Rect Posicao, PosicaoJogador1;
SDL_Rect Posicao2, PosicaoJogador2;

//FUNÇÃO DO JOGO
void Jogar(SDL_Surface* tela)
{
    Teclas Estado_Teclado;
    memset(&Estado_Teclado, 0, sizeof(Estado_Teclado));

//CRICAÇÃO DAS IMAGENS
    SDL_Surface *Jogador1[4] = {NULL};
    SDL_Surface *Jogador2[4] = {NULL};

    SDL_Surface *Jogador1Atual = NULL;
    SDL_Surface *Jogador2Atual = NULL;

    SDL_Surface *Bloco = NULL;

//CRIAÇÃO DA POSIÇÃO DO CENÁRIO E DA SUA IMAGEM
    SDL_Rect PosicaoCenario;
    SDL_Surface *Cenario = NULL;

//CRIAÇÃO DAS IMAGENS DE BOMBAS E EXPLOSÃO
    SDL_Surface *BOMBA = NULL;
    SDL_Surface *EXPLOSAOB = NULL;
    SDL_Surface *EXPLOSAOC = NULL;
    SDL_Surface *EXPLOSAOD = NULL;
    SDL_Surface *EXPLOSAOE = NULL;
    SDL_Surface *EXPLOSAOM = NULL;

//CRIAÇÃO DO MAPA
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
/*    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_Music *musicabatalha;
    musicabatalha = Mix_LoadMUS("Batalha.mp3");

    Mix_PlayMusic(musicabatalha, -1);*/

//CARREGAMENTO DAS IMAGENS
    BOMBA = IMG_Load("Bomba2.bmp");
    EXPLOSAOB = IMG_Load("ExplosaoB.bmp");
    EXPLOSAOC = IMG_Load("ExplosaoC.bmp");
    EXPLOSAOD = IMG_Load("ExplosaoD.bmp");
    EXPLOSAOE = IMG_Load("ExplosaoE.bmp");
    EXPLOSAOM = IMG_Load("ExplosaoM.bmp");

    Jogador1[BAIXO] = IMG_Load("BombermanF.png");
    Jogador1[ESQUERDA] = IMG_Load("BombermanE.png");
    Jogador1[DIREITA] = IMG_Load("BombermanD.png");
    Jogador1[CIMA] = IMG_Load("BombermanC.png");

    Jogador2[BAIXO] = IMG_Load("BombermanBF.png");
    Jogador2[ESQUERDA] = IMG_Load("BombermanBE.png");
    Jogador2[DIREITA] = IMG_Load("BombermanBD.png");
    Jogador2[CIMA] = IMG_Load("BombermanBC.png");

    Bloco = IMG_Load("Bloco.png");
    Cenario = IMG_Load("Cenario.bmp");

    Jogador1Atual = Jogador1[BAIXO];
    Jogador2Atual = Jogador2[BAIXO];

//POSIÇÃO DOS JOGADORES NA TELA
    PosicaoJogador1.x = 1;
    PosicaoJogador1.y = 1;

    PosicaoJogador2.x = 13;
    PosicaoJogador2.y = 11;

//POSIÇÃO DOS JOGADORES NA MATRIZ
    mapa[1][1] = Jogador1;
    mapa[11][13] = Jogador2;

//MOVIMENTAÇÃO DOS JOGADORES
    while(continuar)
    {
        TecladoAtualizado(&Estado_Teclado);

        if (Estado_Teclado.key[SDLK_UP])
        {
            Jogador1Atual = Jogador1[CIMA];
            MovimentoJogador(mapa, &PosicaoJogador1, CIMA);
        }
        if (Estado_Teclado.key[SDLK_DOWN])
        {
            Jogador1Atual = Jogador1[BAIXO];
            MovimentoJogador(mapa, &PosicaoJogador1, BAIXO);
        }
        if (Estado_Teclado.key[SDLK_RIGHT])
        {
            Jogador1Atual = Jogador1[DIREITA];
            MovimentoJogador(mapa, &PosicaoJogador1, DIREITA);
        }
        if (Estado_Teclado.key[SDLK_LEFT])
        {
            Jogador1Atual = Jogador1[ESQUERDA];
            MovimentoJogador(mapa, &PosicaoJogador1, ESQUERDA);
        }
        if (Estado_Teclado.key[SDLK_m])
        {
            CriacaoBombaJ1 (mapa, tela);
        }


        if (Estado_Teclado.key[SDLK_w])
        {
            Jogador2Atual = Jogador2[CIMA];
            MovimentoJogador(mapa, &PosicaoJogador2, CIMA);
        }
        if (Estado_Teclado.key[SDLK_s])
        {
            Jogador2Atual = Jogador2[BAIXO];
            MovimentoJogador(mapa, &PosicaoJogador2, BAIXO);
        }
        if (Estado_Teclado.key[SDLK_d])
        {
            Jogador2Atual = Jogador2[DIREITA];
            MovimentoJogador(mapa, &PosicaoJogador2, DIREITA);
        }
        if (Estado_Teclado.key[SDLK_a])
        {
            Jogador2Atual = Jogador2[ESQUERDA];
            MovimentoJogador(mapa, &PosicaoJogador2, ESQUERDA);
        }
        if (Estado_Teclado.key[SDLK_p])
        {
            CriacaoBombaJ2(mapa, tela);
        }

        if (Estado_Teclado.key[SDLK_ESCAPE])
        {
            continuar = 0;
        }

        SDL_FillRect(tela,NULL,SDL_MapRGB(tela -> format,0,0,0));

//POSIÇÃO DO CENARIO NA TELA
        PosicaoCenario.x = 0;
        PosicaoCenario.y = 23;

        SDL_BlitSurface(Cenario, NULL, tela, &PosicaoCenario);

//CRIAÇÃO ANIMAÇÃO DOS BLOCOS E EFEITOS DE EXPLOSÃO
        for (i = 1; i < 13; i++)
        {
            for (j = 1; j < 15; j++)
            {
               Posicao.x = j*Tamanho_Bloco;
               Posicao.y = i*Tamanho_Bloco+24;

                switch(mapa[i][j])
                {
                    case 2:
                    SDL_BlitSurface(Bloco, NULL, tela, &Posicao);
                    break;

                    case 5:
                    SDL_BlitSurface(BOMBA, NULL, tela, &Posicao);
                    break;

                    case 10:
                    SDL_BlitSurface(EXPLOSAOM, NULL, tela, &Posicao);
                    break;

                    case 6:
                    SDL_BlitSurface(EXPLOSAOB, NULL, tela, &Posicao);
                    break;

                    case 7:
                    SDL_BlitSurface(EXPLOSAOC, NULL, tela, &Posicao);
                    break;

                    case 8:
                    SDL_BlitSurface(EXPLOSAOD, NULL, tela, &Posicao);
                    break;

                    case 9:
                    SDL_BlitSurface(EXPLOSAOE, NULL, tela, &Posicao);
                    break;
                }
            }
        }

        Posicao.x = PosicaoJogador1.x*Tamanho_Bloco;
        Posicao.y = PosicaoJogador1.y*Tamanho_Bloco;

        SDL_BlitSurface(Jogador1Atual,NULL,tela,&Posicao);

        Posicao2.x = PosicaoJogador2.x*Tamanho_Bloco;
        Posicao2.y = PosicaoJogador2.y*Tamanho_Bloco;

        SDL_BlitSurface(Jogador2Atual,NULL,tela,&Posicao2);

//VELOCIDADE DE MOVIMENTO DOS JOGADORES
        usleep(150000);

        SDL_Flip(tela);
    }

//LIBERAÇÃO DAS IMAGENS NA TELA
    SDL_FreeSurface(Bloco);

    for(i = 0; i < 4; i++)
    {
        SDL_FreeSurface(Jogador1[i]);
    }

    for(i = 0; i < 4; i++)
    {
        SDL_FreeSurface(Jogador2[i]);
    }

    SDL_FreeSurface(BOMBA);
    SDL_FreeSurface(EXPLOSAOB);
    SDL_FreeSurface(EXPLOSAOC);
    SDL_FreeSurface(EXPLOSAOD);
    SDL_FreeSurface(EXPLOSAOE);
    SDL_FreeSurface(EXPLOSAOM);

}

//COLISÃO DOS JOGADORES COM CENÁRIO,  BLOCOS E BOMBAS
void MovimentoJogador(int **mapa, SDL_Rect *pos, int direcao)
{
    switch(direcao)
    {
        case CIMA:

        if (mapa[pos -> y - 1][pos -> x] == PAREDE)
        {
            break;
        }
        if (mapa[pos -> y - 1][pos -> x] == Bloco)
        {
            break;
        }
        if (mapa[pos -> y - 1][pos -> x] == BOMBA)
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
        if (mapa[pos -> y + 1][pos -> x] == Bloco)
        {
            break;
        }
        if (mapa[pos -> y + 1][pos -> x] == BOMBA)
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
        if (mapa[pos -> y][pos -> x - 1] == Bloco)
        {
            break;
        }
        if (mapa[pos -> y][pos -> x - 1] == BOMBA)
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
        if (mapa[pos -> y][pos -> x + 1] == Bloco)
        {
            break;
        }
        if (mapa[pos -> y][pos -> x + 1] == BOMBA)
        {
            break;
        }

        pos-> x++;
        break;
    }
}

//CRIAÇÃO DA AREA DE AMEAÇA DA BOMBA DO JOGADOR 1
void CriacaoBombaJ1 (int **mapa, SDL_Surface* tela)
{
    pthread_t AmeacaJ1;

    J1.MapaBombaJ1 = mapa;
    J1.TelaBombaJ1 = tela;

    pthread_create(&AmeacaJ1, NULL, GerenciamentoBombaJ1, (void*)&J1);
}

//CRIAÇÃO DA AREA DE AMEAÇA DA BOMBA DO JOGADOR 2
void CriacaoBombaJ2 (int **mapa, SDL_Surface* tela)
{
    pthread_t AmeacaJ2;

    J2.MapaBombaJ2 = mapa;
    J2.TelaBombaJ1 = tela;

    pthread_create(&AmeacaJ2, NULL, GerenciamentoBombaJ2, (void*)&J2);
}

// INTERAÇÃO DA BOMBA, JOGADOR 1, COM O CENÁRIO
void *GerenciamentoBombaJ1(void*arg)
{
    BombaJ1 *args = (BombaJ1*)arg;
    int **MapaBombaJ1 = args -> MapaBombaJ1;

    MapaBombaJ1[PosicaoJogador1.y][PosicaoJogador1.x] = BOMBA;

    SDL_Delay(3000);

    int a, b = 0;

    for(a = 1; a < 13; a++)
    {
        for (b = 1; b < 15; b++)
        {
            if (MapaBombaJ1[a][b] == 5)
            {
                MapaBombaJ1[a][b] = 10;

                if (MapaBombaJ1[a+1][b] == 0)
                {
                    MapaBombaJ1[a+1][b] = 6;
                }
                if (MapaBombaJ1[a+1][b] == MapaBombaJ1[PosicaoJogador1.y][PosicaoJogador1.x])
                {
                    MapaBombaJ1[a+1][b] = 6;
                }
                if (MapaBombaJ1[a+1][b] == MapaBombaJ1[PosicaoJogador2.y][PosicaoJogador2.x])
                {
                    MapaBombaJ1[a+1][b] = 6;
                }
                if (MapaBombaJ1[a+1][b] == 2)
                {
                    MapaBombaJ1[a+1][b] = 6;
                }

                if (MapaBombaJ1[a-1][b] == 0)
                {
                    MapaBombaJ1[a-1][b] = 7;
                }
                if (MapaBombaJ1[a-1][b] == MapaBombaJ1[PosicaoJogador1.y][PosicaoJogador1.x])
                {
                    MapaBombaJ1[a-1][b] = 7;
                }
                if (MapaBombaJ1[a-1][b] == MapaBombaJ1[PosicaoJogador2.y][PosicaoJogador2.x])
                {
                    MapaBombaJ1[a-1][b] = 7;
                }
                if (MapaBombaJ1[a-1][b] == 2)
                {
                    MapaBombaJ1[a-1][b] = 7;
                }

                if (MapaBombaJ1[a][b+1] == 0)
                {
                    MapaBombaJ1[a][b+1] = 8;
                }
                if (MapaBombaJ1[a][b+1] == MapaBombaJ1[PosicaoJogador1.y][PosicaoJogador1.x])
                {
                    MapaBombaJ1[a][b+1] = 8;
                }
                if (MapaBombaJ1[a][b+1] == MapaBombaJ1[PosicaoJogador2.y][PosicaoJogador2.x])
                {
                    MapaBombaJ1[a][b+1] = 8;
                }
                if (MapaBombaJ1[a][b+1] == 2)
                {
                    MapaBombaJ1[a][b+1] = 8;
                }

                if (MapaBombaJ1[a][b-1] == 0)
                {
                    MapaBombaJ1[a][b-1] = 9;
                }
                if (MapaBombaJ1[a][b-1] == MapaBombaJ1[PosicaoJogador1.y][PosicaoJogador1.x])
                {
                    MapaBombaJ1[a][b-1] = 9;
                }
                if (MapaBombaJ1[a][b-1] == MapaBombaJ1[PosicaoJogador2.y][PosicaoJogador2.x])
                {
                    MapaBombaJ1[a][b-1] = 9;
                }
                if (MapaBombaJ1[a][b-1] == 2)
                {
                    MapaBombaJ1[a][b-1] = 9;
                }
            }
        }
    }
    SDL_Delay(150);

//ANIMAÇÃO DE EXPLOSÃO DA BOMBA
    for (a = 1; a < 13; a++)
    {
        for (b = 1; b < 15; b++)
        {
            if (MapaBombaJ1[a][b] == 10)
            {
                MapaBombaJ1[a][b] = 0;
            }
            if (MapaBombaJ1[a][b] == 6)
            {
                MapaBombaJ1[a][b] = 0;
            }
            if (MapaBombaJ1[a][b] == 7)
            {
                MapaBombaJ1[a][b] = 0;
            }
            if (MapaBombaJ1[a][b] == 8)
            {
                MapaBombaJ1[a][b] = 0;
            }
            if (MapaBombaJ1[a][b] == 9)
            {
                MapaBombaJ1[a][b] = 0;
            }
        }
    }
    pthread_exit(NULL);
}

// INTERAÇÃO DA BOMBA, JOGADOR 2, COM O CENÁRIO
void *GerenciamentoBombaJ2(void*arg)
{
    BombaJ2 *args = (BombaJ2*)arg;
    int **MapaBombaJ2 = args -> MapaBombaJ2;

    MapaBombaJ2[PosicaoJogador2.y][PosicaoJogador2.x] = BOMBA;

    SDL_Delay(3000);

    int a, b = 0;

    for(a = 1; a < 13; a++)
    {
        for (b = 1; b < 15; b++)
        {
            if (MapaBombaJ2[a][b] == 5)
            {
                MapaBombaJ2[a][b] = 10;

                if (MapaBombaJ2[a+1][b] == 0)
                {
                    MapaBombaJ2[a+1][b] = 6;
                }
                if (MapaBombaJ2[a+1][b] == MapaBombaJ2[PosicaoJogador1.y][PosicaoJogador1.x])
                {
                    MapaBombaJ2[a+1][b] = 6;
                }
                if (MapaBombaJ2[a+1][b] == MapaBombaJ2[PosicaoJogador2.y][PosicaoJogador2.x])
                {
                    MapaBombaJ2[a+1][b] = 6;
                }
                if (MapaBombaJ2[a+1][b] == 2)
                {
                    MapaBombaJ2[a+1][b] = 6;
                }

                if (MapaBombaJ2[a-1][b] == 0)
                {
                    MapaBombaJ2[a-1][b] = 7;
                }
                if (MapaBombaJ2[a-1][b] == MapaBombaJ2[PosicaoJogador1.y][PosicaoJogador1.x])
                {
                    MapaBombaJ2[a-1][b] = 7;
                }
                if (MapaBombaJ2[a-1][b] == MapaBombaJ2[PosicaoJogador2.y][PosicaoJogador2.x])
                {
                    MapaBombaJ2[a-1][b] = 7;
                }
                if (MapaBombaJ2[a-1][b] == 2)
                {
                    MapaBombaJ2[a-1][b] = 7;
                }

                if (MapaBombaJ2[a][b+1] == 0)
                {
                    MapaBombaJ2[a][b+1] = 8;
                }
                if (MapaBombaJ2[a][b+1] == MapaBombaJ2[PosicaoJogador1.y][PosicaoJogador1.x])
                {
                    MapaBombaJ2[a][b+1] = 8;
                }
                if (MapaBombaJ2[a][b+1] == MapaBombaJ2[PosicaoJogador2.y][PosicaoJogador2.x])
                {
                    MapaBombaJ2[a][b+1] = 8;
                }
                if (MapaBombaJ2[a][b+1] == 2)
                {
                    MapaBombaJ2[a][b+1] = 8;
                }

                if (MapaBombaJ2[a][b-1] == 0)
                {
                    MapaBombaJ2[a][b-1] = 9;
                }
                if (MapaBombaJ2[a][b-1] == MapaBombaJ2[PosicaoJogador1.y][PosicaoJogador1.x])
                {
                    MapaBombaJ2[a][b-1] = 9;
                }
                if (MapaBombaJ2[a][b-1] == MapaBombaJ2[PosicaoJogador2.y][PosicaoJogador2.x])
                {
                    MapaBombaJ2[a][b-1] = 9;
                }
                if (MapaBombaJ2[a][b-1] == 2)
                {
                    MapaBombaJ2[a][b-1] = 9;
                }
            }
        }
    }
    SDL_Delay(150);

//ANIMAÇÃO DE EXPLOSÃO DA BOMBA
    for (a = 1; a < 13; a++)
    {
        for (b = 1; b < 15; b++)
        {
            if (MapaBombaJ2[a][b] == 10)
            {
                MapaBombaJ2[a][b] = 0;
            }
            if (MapaBombaJ2[a][b] == 6)
            {
                MapaBombaJ2[a][b] = 0;
            }
            if (MapaBombaJ2[a][b] == 7)
            {
                MapaBombaJ2[a][b] = 0;
            }
            if (MapaBombaJ2[a][b] == 8)
            {
                MapaBombaJ2[a][b] = 0;
            }
            if (MapaBombaJ2[a][b] == 9)
            {
                MapaBombaJ2[a][b] = 0;
            }
        }
    }
    pthread_exit(NULL);
}
