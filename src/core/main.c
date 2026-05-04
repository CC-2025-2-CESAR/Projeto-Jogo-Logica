#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>  
#include <tipos.h>  


int main(void) {
    /* 1. Inicializacao do Raylib (abre a janela, prepara contexto grafico) */
    InitWindow(LARGURA_TELA, ALTURA_TELA, "AUGUR - Projeto PIF CESAR");
    SetTargetFPS(FPS_ALVO);


    /* 2. Prepara o estado do jogo.
     * A sintaxe " = {0}" zera TODOS os campos da struct (ponteiros = NULL,
     * numeros = 0, bools = false). E um idioma classico em C. */
    EstadoJogo ej = {0};
    jogo_inicializar(&ej);

    /* 3. LOOP PRINCIPAL.
     * WindowShouldClose() = true quando o usuario clica no X ou aperta ESC.
     * ESTADO_SAIR permite que a gente encerre pelo codigo tambem. */
    while (!WindowShouldClose() && ej.estado_atual != ESTADO_SAIR) {
        jogo_atualizar(&ej);

        /* Bloco de desenho - tudo entre BeginDrawing e EndDrawing vai pra tela. */
        BeginDrawing();
            ClearBackground(BLACK);   /* limpa o frame anterior */
            jogo_desenhar(&ej);
        EndDrawing();
    }

    /* 4. Limpeza - libera memoria alocada dinamicamente e fecha a janela. */
    jogo_finalizar(&ej);
    CloseWindow();
    return 0;
}


/* ============================================================================
 * INICIALIZACAO
 * --------------------------------------------------------------------------
 * Chamada UMA VEZ no inicio. Prepara valores default das structs.
 * ========================================================================== */
static void jogo_inicializar(EstadoJogo *ej) {
    ej->estado_atual   = ESTADO_MENU;
    ej->proximo_estado = ESTADO_MENU;

    jogador_inicializar(&ej->jogador);
    salvamento_carregar(&ej->salvamento);   /* stub por enquanto */


    /* Camera 2D: offset no centro da tela + target na posicao do jogador.
     * Resultado: o jogador aparece sempre centralizado e o mundo "rola"
     * conforme ele anda. Zoom 1.0 = sem zoom. */
    ej->camera.offset   = (Vector2){ LARGURA_TELA / 2.0f, ALTURA_TELA / 2.0f };
    ej->camera.target   = ej->jogador.posicao;
    ej->camera.rotation = 0.0f;
    ej->camera.zoom     = 1.0f;

    ej->modo_debug = false;
}
