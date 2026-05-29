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

    /* Botao de confirmacao */
    f->botao_confirmar = (Rectangle){ 1060, 585, 90, 30 };
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

    /* Botao de confirmacao */
    f->botao_confirmar = (Rectangle){ 1060, 585, 90, 30 };
}

/* ============================================================================
 * FASE 3 — (P /\ Q) -> R  (IMPLICACAO)
 * Tres variaveis: se P e Q sao verdadeiros, R tambem deve ser.
 * ========================================================================== */
static void carregar_fase3(Fase *f) {
    memset(f, 0, sizeof(Fase));
    f->proposicao      = PROP_IMPLICA;
    f->num_vars_usadas = 3;
    strncpy(f->titulo_prop, "(P/\\Q)->R", sizeof(f->titulo_prop) - 1);
    strncpy(f->dica, "Agora com mais uma proposicao. Descubra a combinacao!", sizeof(f->dica) - 1);
    f->pos_inicial_jogador = (Vector2){ 80, 560 };

    /* Plataformas em escada: subida pelo centro, descida pela direita */
    f->qtd_plataformas = 6;
    /* Chao */
    f->plataformas[0].rect = (Rectangle){ 0, 620, 1280, 100 };
    f->plataformas[0].cor  = (Color){ 30, 45, 70, 255 };
    /* Plataforma P (baixa esquerda) */
    f->plataformas[1].rect = (Rectangle){ 80, 510, 160, 20 };
    f->plataformas[1].cor  = (Color){ 55, 80, 120, 255 };
    /* Ponte esquerda */
    f->plataformas[2].rect = (Rectangle){ 330, 440, 160, 20 };
    f->plataformas[2].cor  = (Color){ 55, 80, 120, 255 };
    /* Plataforma Q (alta centro) */
    f->plataformas[3].rect = (Rectangle){ 570, 370, 160, 20 };
    f->plataformas[3].cor  = (Color){ 55, 80, 120, 255 };
    /* Plataforma R (media direita) */
    f->plataformas[4].rect = (Rectangle){ 810, 440, 160, 20 };
    f->plataformas[4].cor  = (Color){ 55, 80, 120, 255 };
    /* Descida para porta */
    f->plataformas[5].rect = (Rectangle){ 1010, 510, 160, 20 };
    f->plataformas[5].cor  = (Color){ 55, 80, 120, 255 };

    /* Tres botoes */
    f->qtd_botoes = 3;
    /* Botao P */
    f->botoes[0].rect         = (Rectangle){ 90, 480, 60, 30 };
    f->botoes[0].variavel_idx = 0;
    f->botoes[0].ativo        = false;
    f->botoes[0].cor_ativo    = (Color){ 50, 200, 50, 255 };
    f->botoes[0].cor_inativo  = (Color){ 70, 70, 150, 255 };
    strncpy(f->botoes[0].label, "P", sizeof(f->botoes[0].label) - 1);
    /* Botao Q */
    f->botoes[1].rect         = (Rectangle){ 580, 340, 60, 30 };
    f->botoes[1].variavel_idx = 1;
    f->botoes[1].ativo        = false;
    f->botoes[1].cor_ativo    = (Color){ 50, 200, 50, 255 };
    f->botoes[1].cor_inativo  = (Color){ 70, 70, 150, 255 };
    strncpy(f->botoes[1].label, "Q", sizeof(f->botoes[1].label) - 1);
    /* Botao R */
    f->botoes[2].rect         = (Rectangle){ 820, 410, 60, 30 };
    f->botoes[2].variavel_idx = 2;
    f->botoes[2].ativo        = false;
    f->botoes[2].cor_ativo    = (Color){ 50, 200, 50, 255 };
    f->botoes[2].cor_inativo  = (Color){ 70, 70, 150, 255 };
    strncpy(f->botoes[2].label, "R", sizeof(f->botoes[2].label) - 1);

    /* Porta */
    f->porta.rect   = (Rectangle){ 1160, 490, 48, 130 };
    f->porta.aberta = false;

    /* Botao de confirmacao */
    f->botao_confirmar = (Rectangle){ 1060, 585, 90, 30 };
}

/* Helper: inicializa uma plataforma instavel */
static void plat_instavel(Plataforma *p, Rectangle r, Color c) {
    p->rect          = r;
    p->cor           = c;
    p->instavel      = true;
    p->acionada      = false;
    p->timer_colapso = 0.28f; /* colapsa rapido */
    p->colapsada     = false;
}

/* ============================================================================
 * FASE 4 — (~P \/ ~Q) /\ R   i.e. ~(P/\Q) /\ R
 * Proposicao onde tudo-verdadeiro NAO funciona: ao menos P ou Q deve ser F.
 *
 * Mecanica de armadilha:
 *   - Cada gap entre plataformas seguras tem uma plataforma instavel IDENTICA
 *     (mesma cor, sem marcadores) encostada logo apos a borda da plataforma safe.
 *   - Quem CAMINHA para o gap pisa na armadilha e cai (colapso em 0.28s).
 *   - Quem PULA sobrevoa a armadilha e aterra na proxima plataforma segura.
 *   - Posicao X da armadilha e randomizada a cada reinicio dentro do gap.
 *
 * Caminho seguro (via pulo):
 *   Chao -> P(60-200) --pulo 160px--> Bridge(360-500)
 *        --pulo 120px--> Q(560-720) --pulo 160px--> R(880-1030)
 *        -> queda ao chao -> Confirmar -> Porta
 * ========================================================================== */
static void carregar_fase4(Fase *f) {
    memset(f, 0, sizeof(Fase));
    f->proposicao      = PROP_NAND_R;
    f->num_vars_usadas = 3;
    strncpy(f->titulo_prop, "(~P\\/~Q)/\\R", sizeof(f->titulo_prop) - 1);
    strncpy(f->dica, "Nem sempre verdadeiro e a resposta. Cuidado com o caminho!", sizeof(f->dica) - 1);
    f->pos_inicial_jogador = (Vector2){ 80, 560 };

    Color cor = (Color){ 90, 50, 130, 255 };  /* cor unica para safe e trap */

    f->qtd_plataformas = 8;

    /* Chao */
    f->plataformas[0].rect = (Rectangle){ 0, 620, 1280, 100 };
    f->plataformas[0].cor  = (Color){ 50, 20, 70, 255 };

    /* Plataformas SEGURAS */
    f->plataformas[1].rect = (Rectangle){  60, 510, 140, 20 };  /* P   (60-200)  */
    f->plataformas[1].cor  = cor;
    f->plataformas[2].rect = (Rectangle){ 360, 440, 140, 20 };  /* Bridge (360-500) */
    f->plataformas[2].cor  = cor;
    f->plataformas[3].rect = (Rectangle){ 560, 370, 160, 20 };  /* Q   (560-720) */
    f->plataformas[3].cor  = cor;
    f->plataformas[4].rect = (Rectangle){ 880, 440, 150, 20 };  /* R   (880-1030) */
    f->plataformas[4].cor  = cor;

    /*
     * Plataformas INSTAVEIS — mesma cor, encostadas apos cada plataforma safe.
     * X aleatorio dentro do gap; Y identico ao nivel da plataforma anterior.
     * Quem pisa ao caminhar cai; quem pula já passou longe quando desce.
     *
     * Gap 1: P termina x=200, Bridge comeca x=360 → armadilha y=510 (nivel P)
     * Gap 2: Bridge termina x=500, Q comeca x=560 → armadilha y=440 (nivel Bridge)
     * Gap 3: Q termina x=720, R comeca x=880    → armadilha y=370 (nivel Q)
     */
    int x1 = GetRandomValue(200, 270);  /* gap 1 */
    int x2 = GetRandomValue(500, 530);  /* gap 2 */
    int x3 = GetRandomValue(720, 800);  /* gap 3 */
    plat_instavel(&f->plataformas[5], (Rectangle){ x1, 510, 70, 20 }, cor);
    plat_instavel(&f->plataformas[6], (Rectangle){ x2, 440, 60, 20 }, cor);
    plat_instavel(&f->plataformas[7], (Rectangle){ x3, 370, 70, 20 }, cor);

    /* Botoes */
    f->qtd_botoes = 3;
    f->botoes[0].rect         = (Rectangle){  70, 480, 60, 30 };
    f->botoes[0].variavel_idx = 0;
    f->botoes[0].ativo        = false;
    f->botoes[0].cor_ativo    = (Color){ 50, 200, 50, 255 };
    f->botoes[0].cor_inativo  = (Color){ 70, 40, 110, 255 };
    strncpy(f->botoes[0].label, "P", sizeof(f->botoes[0].label) - 1);

    f->botoes[1].rect         = (Rectangle){ 570, 340, 60, 30 };
    f->botoes[1].variavel_idx = 1;
    f->botoes[1].ativo        = false;
    f->botoes[1].cor_ativo    = (Color){ 50, 200, 50, 255 };
    f->botoes[1].cor_inativo  = (Color){ 70, 40, 110, 255 };
    strncpy(f->botoes[1].label, "Q", sizeof(f->botoes[1].label) - 1);

    f->botoes[2].rect         = (Rectangle){ 890, 410, 60, 30 };
    f->botoes[2].variavel_idx = 2;
    f->botoes[2].ativo        = false;
    f->botoes[2].cor_ativo    = (Color){ 50, 200, 50, 255 };
    f->botoes[2].cor_inativo  = (Color){ 70, 40, 110, 255 };
    strncpy(f->botoes[2].label, "R", sizeof(f->botoes[2].label) - 1);

    f->porta.rect      = (Rectangle){ 1160, 490, 48, 130 };
    f->porta.aberta    = false;
    f->botao_confirmar = (Rectangle){ 1060, 585, 90, 30 };
}

/* ============================================================================
 * FASE 5 — P /\ Q /\ (R \/ S)  (QUATRO VARIAVEIS + INIMIGO)
 * Quatro variaveis. Inimigo perseguidor no cenario.
 * ========================================================================== */
static void carregar_fase5(Fase *f) {
    memset(f, 0, sizeof(Fase));
    f->proposicao      = PROP_BICOND_IMPL;
    f->num_vars_usadas = 4;
    strncpy(f->titulo_prop, "(P<->Q)/\\(R->S)", sizeof(f->titulo_prop) - 1);
    strncpy(f->dica, "Bicondicional e condicional juntos. E cuidado com o inimigo!", sizeof(f->dica) - 1);
    f->pos_inicial_jogador = (Vector2){ 80, 560 };

    /* --- Plataformas --- */
    f->qtd_plataformas = 7;

    /* Chao */
    f->plataformas[0].rect = (Rectangle){ 0, 620, 1280, 100 };
    f->plataformas[0].cor  = (Color){ 60, 10, 10, 255 };
    /* P (baixa) */
    f->plataformas[1].rect = (Rectangle){ 80, 510, 130, 20 };
    f->plataformas[1].cor  = (Color){ 110, 30, 30, 255 };
    /* Q (media) */
    f->plataformas[2].rect = (Rectangle){ 300, 440, 130, 20 };
    f->plataformas[2].cor  = (Color){ 110, 30, 30, 255 };
    /* R (alta) */
    f->plataformas[3].rect = (Rectangle){ 520, 370, 130, 20 };
    f->plataformas[3].cor  = (Color){ 110, 30, 30, 255 };
    /* S (media, descendo) */
    f->plataformas[4].rect = (Rectangle){ 740, 440, 130, 20 };
    f->plataformas[4].cor  = (Color){ 110, 30, 30, 255 };
    /* Descida */
    f->plataformas[5].rect = (Rectangle){ 960, 510, 130, 20 };
    f->plataformas[5].cor  = (Color){ 110, 30, 30, 255 };
    /* Plataforma alta central (bonus / visual) */
    f->plataformas[6].rect = (Rectangle){ 1100, 460, 80, 20 };
    f->plataformas[6].cor  = (Color){ 110, 30, 30, 255 };

    /* --- Botoes (4 variaveis) --- */
    f->qtd_botoes = 4;

    f->botoes[0].rect         = (Rectangle){ 90, 480, 60, 30 };
    f->botoes[0].variavel_idx = 0;
    f->botoes[0].ativo        = false;
    f->botoes[0].cor_ativo    = (Color){ 50, 200, 50, 255 };
    f->botoes[0].cor_inativo  = (Color){ 100, 20, 20, 255 };
    strncpy(f->botoes[0].label, "P", sizeof(f->botoes[0].label) - 1);

    f->botoes[1].rect         = (Rectangle){ 310, 410, 60, 30 };
    f->botoes[1].variavel_idx = 1;
    f->botoes[1].ativo        = false;
    f->botoes[1].cor_ativo    = (Color){ 50, 200, 50, 255 };
    f->botoes[1].cor_inativo  = (Color){ 100, 20, 20, 255 };
    strncpy(f->botoes[1].label, "Q", sizeof(f->botoes[1].label) - 1);

    f->botoes[2].rect         = (Rectangle){ 530, 340, 60, 30 };
    f->botoes[2].variavel_idx = 2;
    f->botoes[2].ativo        = false;
    f->botoes[2].cor_ativo    = (Color){ 50, 200, 50, 255 };
    f->botoes[2].cor_inativo  = (Color){ 100, 20, 20, 255 };
    strncpy(f->botoes[2].label, "R", sizeof(f->botoes[2].label) - 1);

    f->botoes[3].rect         = (Rectangle){ 750, 410, 60, 30 };
    f->botoes[3].variavel_idx = 3;
    f->botoes[3].ativo        = false;
    f->botoes[3].cor_ativo    = (Color){ 50, 200, 50, 255 };
    f->botoes[3].cor_inativo  = (Color){ 100, 20, 20, 255 };
    strncpy(f->botoes[3].label, "S", sizeof(f->botoes[3].label) - 1);

    f->porta.rect   = (Rectangle){ 1160, 490, 48, 130 };
    f->porta.aberta = false;
    f->botao_confirmar = (Rectangle){ 1060, 585, 90, 30 };

    /* --- Inimigo --- */
    f->tem_inimigo      = true;
    f->inimigo.pos      = (Vector2){ 1180, 380 };
    f->inimigo.speed    = 85.0f;
    f->inimigo.ativo    = true;
}

/* ============================================================================
 * DISPATCHER
 * ========================================================================== */
void fase_carregar(Fase *fase, int num) {
    switch (num) {
        case 0: carregar_fase1(fase); break;
        case 1: carregar_fase2(fase); break;
        case 2: carregar_fase3(fase); break;
        case 3: carregar_fase4(fase); break;
        case 4: carregar_fase5(fase); break;
        default: carregar_fase1(fase); break;
    }
}
