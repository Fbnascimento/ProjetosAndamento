#ifndef PISTA_H_INCLUDED
#define PISTA_H_INCLUDED

typedef struct
{
   int key[SDLK_LAST];
}
teclas;

void *gerenciamento_bomba_j1_pista(void*arg);
void *gerenciamento_bomba_j2_pista(void*arg);

void criacao_bomba_j1_pista(int **mapa, SDL_Surface* tela4);
void criacao_bomba_j2_pista(int **mapa, SDL_Surface* tela4);

void teclado_atualizado__pista(teclas* estado_teclado);
void jogar_gelo(SDL_Surface* tela4);
void movimento_jogador__pista(int **mapa, SDL_Rect *pos, int direcao);

#endif // PISTA_H_INCLUDED
