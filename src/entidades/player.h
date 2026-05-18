#ifndef PLAYER_H
#define PLAYER_H

#include "tipos.h"

void player_inicializar(Jogador *j, Vector2 pos);
void player_atualizar(Jogador *j, const Fase *fase, float dt);
void player_desenhar(const Jogador *j);

#endif
