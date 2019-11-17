#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

typedef struct
{
   int key[SDLK_LAST];
}
Teclas;

void *gestion_bomba(void*arg);
void criacao_bomba(int **mapa, SDL_Surface* ecran);

void TecladoAtualizado(Teclas* estado_teclado);
void jogar(SDL_Surface* ecran);
void movimentojogador(int **mapa, SDL_Rect *pos, int direcao);

#endif // JOGO_H_INCLUDED
