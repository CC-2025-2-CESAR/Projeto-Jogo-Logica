#include "fases.h"
#include <string.h>

int fase_total(void) { return NUM_FASES; }

/* ============================================================================
 * FASE 1 — P /\ Q  (AND)
 * Dois botoes lado a lado. Jogador precisa ativar os dois.
 * Plataformas basicas, porta no lado direito.
 * ========================================================================== */
static void carregar_fase1(Fase *f) {
    memset(f, 0, sizeof(Fase));
    f->proposicao     = PROP_E;
    f->num_vars_usadas = 2;
    strncpy(f->titulo_prop, "P /\\ Q", sizeof(f->titulo_prop) - 1);
    strncpy(f->dica, "Ative P E Q para abrir a porta!", sizeof(f->dica) - 1);
    f->pos_inicial_jogador = (Vector2){ 80, 560 };

    /* Plataformas */
    f->qtd_plataformas = 4;
    /* Chao */
    f->plataformas[0].rect = (Rectangle){ 0, 620, 1280, 100 };
    f->plataformas[0].cor  = (Color){ 80, 60, 40, 255 };
    /* Plataforma media esquerda */
    f->plataformas[1].rect = (Rectangle){ 200, 480, 180, 20 };
    f->plataformas[1].cor  = (Color){ 100, 80, 50, 255 };
    /* Plataforma media direita */
    f->plataformas[2].rect = (Rectangle){ 600, 480, 180, 20 };
    f->plataformas[2].cor  = (Color){ 100, 80, 50, 255 };
    /* Plataforma alta */
    f->plataformas[3].rect = (Rectangle){ 900, 380, 200, 20 };
    f->plataformas[3].cor  = (Color){ 100, 80, 50, 255 };

    /* Botoes */
    f->qtd_botoes = 2;
    /* Botao P */
    f->botoes[0].rect         = (Rectangle){ 250, 590, 60, 30 };
    f->botoes[0].variavel_idx = 0; /* P */
    f->botoes[0].ativo        = false;
    f->botoes[0].cor_ativo    = (Color){ 50, 200, 50, 255 };
    f->botoes[0].cor_inativo  = (Color){ 150, 50, 50, 255 };
    strncpy(f->botoes[0].label, "P", sizeof(f->botoes[0].label) - 1);
    /* Botao Q */
    f->botoes[1].rect         = (Rectangle){ 650, 590, 60, 30 };
    f->botoes[1].variavel_idx = 1; /* Q */
    f->botoes[1].ativo        = false;
    f->botoes[1].cor_ativo    = (Color){ 50, 200, 50, 255 };
    f->botoes[1].cor_inativo  = (Color){ 150, 50, 50, 255 };
    strncpy(f->botoes[1].label, "Q", sizeof(f->botoes[1].label) - 1);

    /* Porta */
    f->porta.rect   = (Rectangle){ 1160, 490, 48, 130 };
    f->porta.aberta = false;
}

/* ============================================================================
 * FASE 2 — P \/ Q  (OR)
 * Dois botoes em plataformas separadas. Ativar qualquer um ja abre a porta.
 * ========================================================================== */
static void carregar_fase2(Fase *f) {
    memset(f, 0, sizeof(Fase));
    f->proposicao     = PROP_OU;
    f->num_vars_usadas = 2;
    strncpy(f->titulo_prop, "P \\/ Q", sizeof(f->titulo_prop) - 1);
    strncpy(f->dica, "Ative P OU Q (ou os dois) para abrir!", sizeof(f->dica) - 1);
    f->pos_inicial_jogador = (Vector2){ 80, 560 };

    f->qtd_plataformas = 5;
    /* Chao */
    f->plataformas[0].rect = (Rectangle){ 0, 620, 1280, 100 };
    f->plataformas[0].cor  = (Color){ 50, 50, 100, 255 };
    /* Plataformas em degraus */
    f->plataformas[1].rect = (Rectangle){ 150, 500, 160, 20 };
    f->plataformas[1].cor  = (Color){ 70, 70, 140, 255 };
    f->plataformas[2].rect = (Rectangle){ 380, 430, 160, 20 };
    f->plataformas[2].cor  = (Color){ 70, 70, 140, 255 };
    f->plataformas[3].rect = (Rectangle){ 620, 360, 160, 20 };
    f->plataformas[3].cor  = (Color){ 70, 70, 140, 255 };
    f->plataformas[4].rect = (Rectangle){ 900, 480, 220, 20 };
    f->plataformas[4].cor  = (Color){ 70, 70, 140, 255 };

    f->qtd_botoes = 2;
    f->botoes[0].rect         = (Rectangle){ 160, 470, 60, 30 };
    f->botoes[0].variavel_idx = 0;
    f->botoes[0].ativo        = false;
    f->botoes[0].cor_ativo    = (Color){ 50, 200, 200, 255 };
    f->botoes[0].cor_inativo  = (Color){ 80, 80, 160, 255 };
    strncpy(f->botoes[0].label, "P", sizeof(f->botoes[0].label) - 1);

    f->botoes[1].rect         = (Rectangle){ 630, 330, 60, 30 };
    f->botoes[1].variavel_idx = 1;
    f->botoes[1].ativo        = false;
    f->botoes[1].cor_ativo    = (Color){ 50, 200, 200, 255 };
    f->botoes[1].cor_inativo  = (Color){ 80, 80, 160, 255 };
    strncpy(f->botoes[1].label, "Q", sizeof(f->botoes[1].label) - 1);

    f->porta.rect   = (Rectangle){ 1160, 490, 48, 130 };
    f->porta.aberta = false;
}

/* ============================================================================
 * FASE 3 — ~P /\ Q  (NOT P AND Q)
 * Jogador deve deixar P=FALSO e ativar Q=VERDADEIRO.
 * Enganosa: ativar P fecha a porta!
 * ========================================================================== */
static void carregar_fase3(Fase *f) {
    memset(f, 0, sizeof(Fase));
    f->proposicao     = PROP_NAO_P_E_Q;
    f->num_vars_usadas = 2;
    strncpy(f->titulo_prop, "~P /\\ Q", sizeof(f->titulo_prop) - 1);
    strncpy(f->dica, "Cuidado: P deve ficar FALSO! Ative so Q!", sizeof(f->dica) - 1);
    f->pos_inicial_jogador = (Vector2){ 80, 560 };

    f->qtd_plataformas = 6;
    f->plataformas[0].rect = (Rectangle){ 0, 620, 1280, 100 };
    f->plataformas[0].cor  = (Color){ 40, 80, 40, 255 };
    f->plataformas[1].rect = (Rectangle){ 100, 490, 200, 20 };
    f->plataformas[1].cor  = (Color){ 60, 110, 60, 255 };
    f->plataformas[2].rect = (Rectangle){ 380, 420, 180, 20 };
    f->plataformas[2].cor  = (Color){ 60, 110, 60, 255 };
    f->plataformas[3].rect = (Rectangle){ 620, 350, 180, 20 };
    f->plataformas[3].cor  = (Color){ 60, 110, 60, 255 };
    f->plataformas[4].rect = (Rectangle){ 850, 430, 200, 20 };
    f->plataformas[4].cor  = (Color){ 60, 110, 60, 255 };
    f->plataformas[5].rect = (Rectangle){ 1050, 500, 160, 20 };
    f->plataformas[5].cor  = (Color){ 60, 110, 60, 255 };

    f->qtd_botoes = 2;
    /* Botao P — ativar aqui e armadilha */
    f->botoes[0].rect         = (Rectangle){ 110, 460, 60, 30 };
    f->botoes[0].variavel_idx = 0;
    f->botoes[0].ativo        = false;
    f->botoes[0].cor_ativo    = (Color){ 200, 80, 80, 255 };
    f->botoes[0].cor_inativo  = (Color){ 80, 160, 80, 255 };
    strncpy(f->botoes[0].label, "P", sizeof(f->botoes[0].label) - 1);

    /* Botao Q — deve ser ativado */
    f->botoes[1].rect         = (Rectangle){ 630, 320, 60, 30 };
    f->botoes[1].variavel_idx = 1;
    f->botoes[1].ativo        = false;
    f->botoes[1].cor_ativo    = (Color){ 50, 220, 50, 255 };
    f->botoes[1].cor_inativo  = (Color){ 80, 80, 160, 255 };
    strncpy(f->botoes[1].label, "Q", sizeof(f->botoes[1].label) - 1);

    f->porta.rect   = (Rectangle){ 1160, 490, 48, 130 };
    f->porta.aberta = false;
}

/* ============================================================================
 * DISPATCHER
 * ========================================================================== */
void fase_carregar(Fase *fase, int num) {
    switch (num) {
        case 0: carregar_fase1(fase); break;
        case 1: carregar_fase2(fase); break;
        case 2: carregar_fase3(fase); break;
        default: carregar_fase1(fase); break;
    }
}
