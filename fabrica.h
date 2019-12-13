#ifndef FABRICA_H_INCLUDED
#define FABRICA_H_INCLUDED

typedef struct
{
   int key[SDLK_LAST];
}
teclas;

void *gerenciamento_bomba_j1_fabrica(void*arg);
void *gerenciamento_bomba_j2_fabrica(void*arg);

void criacao_bomba_j1_fabrica(int **mapa, SDL_Surface* tela5);
void criacao_bomba_j2_fabrica(int **mapa, SDL_Surface* tela5);

void teclado_atualizado__fabrica(teclas* estado_teclado);
void jogar_fabrica(SDL_Surface* tela5);
void movimento_jogador__fabrica(int **mapa, SDL_Rect *pos, int direcao);

#endif // FABRICA_H_INCLUDED
