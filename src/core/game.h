#ifndef GAME_H
#define GAME_H

#include "tipos.h"

void game_inicializar(EstadoJogo *g);
void game_atualizar(EstadoJogo *g);
void game_desenhar(const EstadoJogo *g);
void game_finalizar(EstadoJogo *g);

#endif
