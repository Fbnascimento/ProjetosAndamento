#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

//INICIALIZAÇÃO DE TELA E MENU
int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL;
    SDL_Surface *menu = NULL;

    SDL_Rect positionMenu;
    SDL_Event event;

    int continuar = 3;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("Bomberman.bmp"), NULL);

    ecran = SDL_SetVideoMode(550,500,32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    SDL_WM_SetCaption("Bomberman", NULL);

    menu = IMG_Load("menu.png");

//MUSICA DO MENU
/*    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_Music *musicamenu;
    musicamenu = Mix_LoadMUS("Menu.mp3");*/

//POSIÇÃO DO MENU NA TELA
    positionMenu.x=0;
    positionMenu.y=0;

//    Mix_PlayMusic(musicamenu, -1);

//EVENTO PARA ENTRAR OU NÃO NO JOGO
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

                case SDLK_1:
                jogar(ecran);
                break;
            }

            break;
        }

        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        SDL_Flip(ecran);
    }

//    Mix_CloseAudio();
    SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCCESS;
}
