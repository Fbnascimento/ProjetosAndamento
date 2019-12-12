#ifndef GELO_H_INCLUDED
#define GELO_H_INCLUDED

typedef struct
{
   int key[SDLK_LAST];
}
teclas;

void *gerenciamento_bomba_j1_gelo(void*arg);
void *gerenciamento_bomba_j2_gelo(void*arg);

void criacao_bomba_j1_gelo(int **mapa, SDL_Surface* tela3);
void criacao_bomba_j2_gelo(int **mapa, SDL_Surface* tela3);

void teclado_atualizado_gelo(teclas* estado_teclado);
void jogar_gelo(SDL_Surface* tela3);
void movimento_jogador_gelo(int **mapa, SDL_Rect *pos, int direcao);

#endif // GELO_H_INCLUDED
