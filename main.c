#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

//INICIALIZAÇÃO DE TELA E MENU
int main(int argc, char *argv[])
{
    SDL_Surface *tela = NULL;
    SDL_Surface *tela2 = NULL;
    SDL_Surface *tela3 = NULL;
    SDL_Surface *tela4 = NULL;

    SDL_Surface *menu = NULL;
    SDL_Surface *novo_jogo = NULL;
    SDL_Surface *mapa_gelo = NULL;
    SDL_Surface *mapa_pista = NULL;
    SDL_Surface *msg_sair = NULL;

    SDL_Rect posicao_menu;
    SDL_Rect posicao_novo_jogo;
    SDL_Rect posicao_mapa_gelo;
    SDL_Rect posicao_mapa_pista;
    SDL_Rect posicao_msg_sair;

    TTF_Font *fonte = NULL;
    SDL_Color cor_texto = {0, 0, 0}, cor = {255, 255, 255};

    SDL_Event evento;

    int continuar = 3;
    char texto_novo_jogo[30] = "";
    char texto_mapa_gelo[30] = "";
    char texto_mapa_pista[30] = "";
    char texto_msg_sair[30] = "";

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("Bomberman.bmp"), NULL);

    tela = SDL_SetVideoMode(520,470,32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    SDL_WM_SetCaption("Bomberman", NULL);

    menu = IMG_Load("menu.png");

    TTF_Init();
    fonte = TTF_OpenFont("fonte.ttf", 36);

    sprintf(texto_novo_jogo, "(1) Mapa Clássico");
    novo_jogo = TTF_RenderText_Blended(fonte, texto_novo_jogo, cor);

    sprintf(texto_mapa_gelo, "(2) Mapa de Gelo");
    mapa_gelo = TTF_RenderText_Blended(fonte, texto_mapa_gelo, cor);

    sprintf(texto_mapa_pista, "(3) Mapa de Corrida");
    mapa_pista = TTF_RenderText_Blended(fonte, texto_mapa_pista, cor);

    sprintf(texto_msg_sair, "(4) Sair");
    msg_sair = TTF_RenderText_Blended(fonte, texto_msg_sair, cor);

//MUSICA DO MENU
    SDL_Delay(100);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_Music *musica_menu;
    musica_menu = Mix_LoadMUS("Menu.mp3");

//POSIÇÃO DO MENU NA TELA
    posicao_menu.x=0;
    posicao_menu.y=0;

    posicao_novo_jogo.x = 6;
    posicao_novo_jogo.y = 0;

    posicao_mapa_gelo.x = 5;
    posicao_mapa_gelo.y = 30;

    posicao_mapa_pista.x = 5;
    posicao_mapa_pista.y = 60;

    posicao_msg_sair.x = 5;
    posicao_msg_sair.y = 90;

//EVENTO PARA ENTRAR OU NÃO NO JOGO
    while(continuar)
    {
        Mix_PlayMusic(musica_menu, 5);

        SDL_WaitEvent(&evento);
        switch(evento.type)
        {
            case SDL_QUIT:
            continuar = 0;
            break;

            case SDL_KEYDOWN:

            switch(evento.key.keysym.sym)
            {
                case SDLK_4:
                continuar = 0;
                break;

                case SDLK_1:
                tela = SDL_SetVideoMode(520,470,32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                jogar(tela);
                break;

                case SDLK_2:
                tela3 = SDL_SetVideoMode(520,470,32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                jogar_gelo(tela3);
                break;

                case SDLK_3:
                tela4 = SDL_SetVideoMode(520,470,32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                jogar_pista(tela4);
                break;
            }

            break;
        }

        SDL_BlitSurface(menu, NULL, tela, &posicao_menu);
        SDL_BlitSurface(novo_jogo, NULL, tela, &posicao_novo_jogo);
        SDL_BlitSurface(mapa_gelo, NULL, tela, &posicao_mapa_gelo);
        SDL_BlitSurface(mapa_pista, NULL, tela, &posicao_mapa_pista);
        SDL_BlitSurface(msg_sair, NULL, tela, &posicao_msg_sair);
        SDL_Flip(tela);
    }

//   Mix_CloseAudio();
    SDL_FreeSurface(menu);
    SDL_FreeSurface(novo_jogo);
    SDL_FreeSurface(mapa_gelo);
    SDL_FreeSurface(mapa_pista);
    SDL_FreeSurface(msg_sair);
    SDL_Quit();

    return EXIT_SUCCESS;
}
