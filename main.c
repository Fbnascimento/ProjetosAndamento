#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

//INICIALIZA��O DE TELA E MENU
int main(int argc, char *argv[])
{
    SDL_Surface *tela = NULL;
    SDL_Surface *menu = NULL;
    SDL_Surface *mensagem = NULL;

    SDL_Rect posicao_menu;
    SDL_Rect posicao_mensagem;

    TTF_Font *fonte = NULL;
    SDL_Color cor_texto = {0, 0, 0}, cor = {0, 0, 0};

    SDL_Event evento;

    int continuar = 3;
    char texto_mensagem[30] = "";

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("Bomberman.bmp"), NULL);

    tela = SDL_SetVideoMode(520,470,32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    SDL_WM_SetCaption("Bomberman", NULL);

    menu = IMG_Load("menu.png");

    TTF_Init();
    fonte = TTF_OpenFont("fonte.ttf", 36);

    sprintf(texto_mensagem, "APERTE 1");
    mensagem = TTF_RenderText_Blended(fonte, texto_mensagem, cor);

//MUSICA DO MENU
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_Music *musica_menu;
    musica_menu = Mix_LoadMUS("Menu.mp3");

//POSI��O DO MENU NA TELA
    posicao_menu.x=0;
    posicao_menu.y=0;

    posicao_mensagem.x = 0;
    posicao_mensagem.y = 0;

//EVENTO PARA ENTRAR OU N�O NO JOGO
    while(continuar)
    {
        Mix_PlayMusic(musica_menu, -1);

        SDL_WaitEvent(&evento);
        switch(evento.type)
        {
            case SDL_QUIT:
            continuar = 0;
            break;

            case SDL_KEYDOWN:

            switch(evento.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                continuar = 0;
                break;

                case SDLK_1:
                jogar(tela);
                break;
            }

            break;
        }

        SDL_BlitSurface(menu, NULL, tela, &posicao_menu);
        SDL_BlitSurface(mensagem, NULL, tela, &posicao_mensagem);
        SDL_Flip(tela);
    }

//   Mix_CloseAudio();
    SDL_FreeSurface(menu);
    SDL_FreeSurface(mensagem);
    SDL_Quit();

    return EXIT_SUCCESS;
}
