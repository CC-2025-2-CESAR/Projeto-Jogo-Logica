#ifndef UI_H
#define UI_H

#include "tipos.h"

void ui_desenhar_menu(int opcao_selecionada);
void ui_desenhar_creditos(void);
void ui_desenhar_hud(const Fase *fase);
void ui_desenhar_painel_logico(const Fase *fase);
void ui_desenhar_timer(float tempo);
void ui_desenhar_fase_completa(int num_fase);
void ui_desenhar_game_over(MotivoGameOver motivo);
void ui_desenhar_vitoria(void);

#endif
