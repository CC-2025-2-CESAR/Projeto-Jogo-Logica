#ifndef TIPOS_H
#define TIPOS_H

#include "raylib.h"
#include <stdbool.h>
#include <stddef.h>

/* ============================================================================
 * CONSTANTES
 * ========================================================================== */
#define LARGURA_TELA      1280
#define ALTURA_TELA       720
#define FPS_ALVO          60

#define MAX_PLATAFORMAS   16
#define MAX_BOTOES        4
#define MAX_VARS_LOGICAS  4   /* P, Q, R, S */

/* Fisica */
#define GRAVIDADE         1200.0f
#define FORCA_PULO        -550.0f
#define VELOC_HORIZONTAL  280.0f
#define LARGURA_JOGADOR   32
#define ALTURA_JOGADOR    48

/* ============================================================================
 * ENUMS
 * ========================================================================== */
typedef enum {
    ESTADO_MENU,
    ESTADO_CREDITOS,
    ESTADO_JOGANDO,
    ESTADO_FASE_COMPLETA,
    ESTADO_GAME_OVER,
    ESTADO_VITORIA,
    ESTADO_SAIR
} EstadoAtual;

/* Tipo da proposicao logica da porta */
typedef enum {
    PROP_E,           /* P /\ Q          */
    PROP_OU,          /* P \/ Q          */
    PROP_NAO_P_E_Q,   /* ¬P /\ Q         */
    PROP_IMPLICA,     /* (P /\ Q) -> R         */
    PROP_BICONDICIONAL, /* P <-> Q             */
    PROP_NAND_R,        /* (~P \/ ~Q) /\ R            */
    PROP_BICOND_IMPL    /* (P <-> Q) /\ (R -> S)     */
} TipoProposicao;

/* ============================================================================
 * STRUCTS DE ENTIDADE
 * ========================================================================== */

typedef struct {
    Rectangle rect;
    Vector2   velocidade;
    bool      no_chao;
} Jogador;

typedef struct {
    Rectangle rect;
    Color     cor;
    bool      instavel;       /* colapsa quando o jogador pisa */
    bool      acionada;       /* contagem regressiva iniciada   */
    float     timer_colapso;  /* segundos ate colapsar          */
    bool      colapsada;      /* ja desapareceu                 */
} Plataforma;

typedef struct {
    Vector2 pos;
    float   speed;
    bool    ativo;
} Inimigo;

/* Botao/alavanca que o jogador interage para alterar P, Q ou R */
typedef struct {
    Rectangle rect;
    int       variavel_idx; /* 0=P, 1=Q, 2=R */
    bool      ativo;        /* valor logico atual */
    Color     cor_ativo;
    Color     cor_inativo;
    char      label[4];     /* "P", "Q", "R"  */
} Botao;

/* Porta: fica fechada ate a proposicao ser verdadeira */
typedef struct {
    Rectangle rect;
    bool      aberta;
} Porta;

/* Fase completa */
typedef struct {
    Plataforma   plataformas[MAX_PLATAFORMAS];
    int          qtd_plataformas;
    Botao        botoes[MAX_BOTOES];
    int          qtd_botoes;
    Porta        porta;
    TipoProposicao proposicao;
    bool         variaveis[MAX_VARS_LOGICAS]; /* P, Q, R */
    char         titulo_prop[32];  /* ex: "P /\\ Q" */
    char         dica[96];
    int          num_vars_usadas;  /* quantas variaveis esta fase usa */
    Vector2      pos_inicial_jogador;
    Rectangle    botao_confirmar;    /* botao de confirmacao proximo a porta */
    bool         tem_inimigo;
    Inimigo      inimigo;
} Fase;

typedef enum {
    MOTIVO_RESPOSTA_ERRADA = 0,
    MOTIVO_TEMPO_ESGOTADO  = 1,
    MOTIVO_INIMIGO         = 2
} MotivoGameOver;

/* ============================================================================
 * ESTADO RAIZ
 * ========================================================================== */
typedef struct {
    EstadoAtual estado_atual;
    Jogador     jogador;
    Fase        fase_atual;
    int         num_fase;       /* 0-based */
    int         opcao_menu;
    float       timer_transicao;
    float          timer_fase;       /* contagem regressiva de 45s */
    MotivoGameOver motivo_game_over;
} EstadoJogo;

#endif /* TIPOS_H */
