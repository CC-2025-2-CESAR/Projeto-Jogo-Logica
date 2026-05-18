#ifndef LOGICA_H
#define LOGICA_H

#include "tipos.h"
#include <stdbool.h>

/* Avalia a proposicao da fase com os valores atuais das variaveis */
bool logica_avaliar(const Fase *fase);

/* Retorna string descritiva da avaliacao passo-a-passo */
void logica_descricao(const Fase *fase, char *out_linha1, char *out_linha2, char *out_linha3);

#endif
