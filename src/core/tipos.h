

#ifndef TIPOS_H
#define TIPOS_H

#include "raylib.h"  
#include <stdbool.h> 
#include <stddef.h>   


#define LARGURA_TELA      1280
#define ALTURA_TELA       720
#define FPS_ALVO          60
#define MAX_OBSTACULOS    40 

/* ============================================================================
 * ENUMS - "Int com nome"
 * --------------------------------------------------------------------------
 * Enum = tipo que e internamente um int, mas com nomes legiveis. Em vez de
 * escrever "if (estado == 2)", voce escreve "if (estado == COMBATE)".
 * Bem mais facil de ler e dificil de errar.
 * ========================================================================== */

/* Estados da maquina de estados do jogo.
 * Main.c tem um switch que decide o que rodar baseado nesse valor. */
typedef enum {
    ESTADO_MENU,                /* tela inicial */
    ESTADO_GAME_OVER,           /* morreu, mostra score */
    ESTADO_SAIR                 /* sinaliza main pra fechar a janela */
} EstadoAtual;

typedef enum {
    OBSTACULOS,
    PAREDE,
} TipoObstaculo;



/* ============================================================================
 * STRUCTS DO JOGO
 * --------------------------------------------------------------------------
 * Toda entidade importante tem sua propria struct. Passamos elas por ponteiro
 * nas funcoes (Jogador *j), o que e mais rapido que copiar e permite que a
 * funcao modifique os campos.
 * ========================================================================== */

/* -------------------- JOGADOR -------------------- */
typedef struct {
    Vector2 posicao;        /* x, y na tela. Vector2 e do Raylib. */
    Vector2 velocidade;     /* usado pra mover de forma suave */
    float   raio;           /* pra colisao circular */
    int     vida;           /* HP atual */
    int     vida_maxima;    /* HP teto */
    float   velocidade_movimento;  /* pixels por segundo */
    int     biomassa;       /* moeda da meta-progressao */
} Jogador;


typedef struct {
    Vector2       posicao;
    float         raio;
    TipoObstaculo tipo;
} Obstaculo;


/* -------------------- DADOS SALVOS (DEV 2) --------------------
 * Persistem entre runs. Dev 2 salva/carrega de saves/biomassa.dat
 * usando fwrite/fread (REQUISITO OBRIGATORIO do PIF: arquivo).
 * ------------------------------------------------------------- */
typedef struct {
    char nome_jogador[32];
} DadosSalvos;


/* ============================================================================
 * ESTADO DO JOGO (STRUCT RAIZ)
 * --------------------------------------------------------------------------
 * Essa e a struct mae. Ela carrega absolutamente tudo do estado atual.
 * Passamos ponteiro dela (EstadoJogo *ej) pra todas as funcoes do jogo.
 *
 * POR QUE USAR ESSA STRUCT RAIZ?
 *   - Zero variaveis globais espalhadas pelo codigo.
 *   - Toda funcao ve o contexto inteiro e pode modificar o que precisa.
 *   - Facil de salvar/carregar: so serializa essa struct.
 *   - Fica obvio quem depende de que.
 * ========================================================================== */
typedef struct {
    /* --- Maquina de estados --- */
    EstadoAtual estado_atual;
    EstadoAtual proximo_estado;   /* buffer de transicao pra trocar entre frames */

    /* --- Entidades principais --- */
    Jogador   jogador;
    DadosSalvos salvamento;

    /* --- Camera 2D ---
     * O jogador vive em um mundo infinito (sem bordas). A camera segue o
     * jogador: camera.target = jogador.posicao. offset e o ponto da tela onde
     * o target aparece (centro da tela = player centralizado). Tudo que for
     * desenhado dentro de BeginMode2D(camera)/EndMode2D e interpretado em
     * coordenadas de mundo; o que fica fora e coord de tela (HUD, menus). */
    Camera2D  camera;


    /* --- Tempo e frames --- */
    float     delta_tempo;        /* segundos desde o ultimo frame */
    float     tempo_total;        /* tempo acumulado da run */
    int       contador_frames;

    /* --- Debug --- */
    bool      modo_debug;         /* F1 alterna; mostra FPS e info extra */

    /* --- Pausa (sandbox) ---
     * pausado = true congela a logica de combate e abre um menu sobreposto
     * com "Continuar" e "Voltar ao menu". opcao_pausa marca qual esta
     * destacada (0 = continuar, 1 = menu). */
    bool      pausado;
    int       opcao_pausa;

    /* --- Obstaculos do mapa (sandbox) ---
     * Array fixo com layout gerado a partir da seed da run. qtd_obstaculos
     * eh quantos slots do array estao realmente preenchidos. Bloqueiam tanto
     * o jogador quanto os inimigos. */
    Obstaculo obstaculos[MAX_OBSTACULOS];
    int       qtd_obstaculos;
} EstadoJogo;

#endif /* TIPOS_H */
