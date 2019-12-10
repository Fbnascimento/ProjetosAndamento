#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

typedef struct
{
   int key[SDLK_LAST];
}
Teclas;

void *GerenciamentoBombaJ1(void*arg);
void *GerenciamentoBombaJ2(void*arg);

void CriacaoBombaJ1(int **mapa, SDL_Surface* ecran);
void CriacaoBombaJ2(int **mapa, SDL_Surface* ecran);

void TecladoAtualizado(Teclas* estado_teclado);
void Jogar(SDL_Surface* ecran);
void movimentojogador(int **mapa, SDL_Rect *pos, int direcao);

#endif // JOGO_H_INCLUDED
