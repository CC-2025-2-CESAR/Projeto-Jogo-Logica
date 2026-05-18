#ifndef FASES_H
#define FASES_H

#include "tipos.h"

#define NUM_FASES 3

/* Preenche a struct Fase com os dados da fase indicada (0-based) */
void fase_carregar(Fase *fase, int num);

/* Retorna o total de fases */
int fase_total(void);

#endif
