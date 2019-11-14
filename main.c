#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char *argv[])
{

    SDL_Surface *ecran = NULL;
    SDL_Surface *menu = NULL;

    SDL_Rect positionMenu;
    SDL_Event event;

    int continuar = 3;

    SDL_Init(SDL_INIT_VIDEO);

        SDL_WM_SetIcon(IMG_Load("Bomberman.bmp"), NULL);
        ecran = SDL_SetVideoMode(800,600,32, SDL_HWSURFACE | SDL_DOUBLEBUF);
        SDL_WM_SetCaption("Bomberman", NULL);

    menu = IMG_Load("menu.png");
    positionMenu.x=0;
    positionMenu.y=0;

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

        SDL_FreeSurface(menu);
        SDL_Quit();

    return EXIT_SUCCESS;
}