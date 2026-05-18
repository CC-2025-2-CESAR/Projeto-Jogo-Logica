#include "ui.h"
#include "logica.h"
#include "raylib.h"
#include <stdio.h>

/* ============================================================================
 * MENU PRINCIPAL
 * ========================================================================== */
void ui_desenhar_menu(int opcao) {
    ClearBackground((Color){ 15, 15, 35, 255 });

    DrawText("LOGIC GATES",  318, 98,  60, (Color){30,30,80,200});
    DrawText("LOGIC GATES",  315, 95,  60, (Color){80,180,255,255});
    DrawText("ADVENTURE",    368, 158, 46, (Color){30,30,80,200});
    DrawText("ADVENTURE",    365, 155, 46, (Color){200,230,255,255});

    DrawText("Resolva puzzles de logica proposicional!", 355, 220, 20, (Color){160,200,255,200});

    /* Simbolos logicos decorativos */
    DrawText("/\\",   80, 300, 48, (Color){ 80,180,255, 60});
    DrawText("\\/",  200, 380, 48, (Color){ 80,255,180, 60});
    DrawText("~",   1100, 280, 60, (Color){255,180, 80, 60});
    DrawText("->",  1050, 380, 48, (Color){255, 80,180, 60});
    DrawText("<->",  140, 460, 40, (Color){200,200, 80, 60});

    const char *opcoes[] = { "INICIAR", "CREDITOS", "SAIR" };
    Color cores_normal[] = { {180,220,255,220}, {180,220,255,220}, {180,220,255,220} };
    Color cores_sel[]    = { {80,220,80,255},   {80,200,255,255},  {255,80,80,255}   };
    for (int i = 0; i < 3; i++) {
        int y  = 320 + i * 80;
        Color c = (opcao == i) ? cores_sel[i] : cores_normal[i];
        int fs  = (opcao == i) ? 36 : 28;
        if (opcao == i) DrawRectangle(500, y-8, 280, fs+16, (Color){30,30,80,180});
        DrawText(opcoes[i], 640 - MeasureText(opcoes[i], fs)/2, y, fs, c);
    }

    DrawText("Use W/S ou setas para navegar, ENTER para confirmar",
             640 - MeasureText("Use W/S ou setas para navegar, ENTER para confirmar",16)/2,
             660, 16, (Color){100,120,180,180});
}

/* ============================================================================
 * CREDITOS
 * ========================================================================== */
void ui_desenhar_creditos(void) {
    ClearBackground((Color){ 10, 10, 30, 255 });
    DrawText("CREDITOS", 640 - MeasureText("CREDITOS", 50)/2, 40, 50, (Color){80,180,255,255});

    const char *nomes[] = {
        "Arthur Reis", "Arthur Almeida", "Gabi Vital",
        "Gabriel Malta", "Luisa Fischer", "Luisa Muniz",
        "Maria Luisa Muniz", "Matheus Assis", "Sofia Vilela"
    };
    for (int i = 0; i < 9; i++) {
        DrawText(nomes[i], 640 - MeasureText(nomes[i], 26)/2, 130 + i * 50, 26,
                 (Color){200,230,255,220});
    }
    DrawText("Disciplina de Logica - CESAR School",
             640 - MeasureText("Disciplina de Logica - CESAR School", 20)/2,
             600, 20, (Color){120,160,200,180});
    DrawText("ESC ou ENTER para voltar",
             640 - MeasureText("ESC ou ENTER para voltar", 18)/2,
             650, 18, (Color){100,120,160,160});
}

/* ============================================================================
 * HUD
 * ========================================================================== */
void ui_desenhar_hud(const Fase *fase) {
    DrawRectangle(0, 0, LARGURA_TELA, 54, (Color){0,0,0,180});
    DrawText(fase->titulo_prop, 10, 10, 28, (Color){255,220,80,255});
    DrawText(fase->dica,
             LARGURA_TELA/2 - MeasureText(fase->dica, 16)/2,
             32, 16, (Color){200,200,200,200});
    DrawText("[E] Interagir  [R] Reiniciar  [ESC] Sair",
             LARGURA_TELA - MeasureText("[E] Interagir  [R] Reiniciar  [ESC] Sair", 14) - 8,
             36, 14, (Color){140,140,180,200});
}

/* ============================================================================
 * PAINEL LOGICO — avaliacao em tempo real visivel na tela
 * ========================================================================== */
void ui_desenhar_painel_logico(const Fase *fase) {
    char l1[64], l2[64], l3[64];
    logica_descricao(fase, l1, l2, l3);

    bool resultado  = logica_avaliar(fase);
    Color cor_fundo = resultado ? (Color){0,60,0,210}   : (Color){60,0,0,210};
    Color cor_borda = resultado ? (Color){50,220,50,255} : (Color){220,50,50,255};

    int px = LARGURA_TELA - 380, py = 58, pw = 372, ph = 120;
    DrawRectangle(px, py, pw, ph, cor_fundo);
    DrawRectangleLinesEx((Rectangle){px, py, pw, ph}, 2, cor_borda);

    DrawText("[ AVALIACAO LOGICA ]", px + 8, py + 6,  16, (Color){200,200,200,230});
    DrawText(l1,                     px + 8, py + 30, 18, WHITE);
    DrawText(l2,                     px + 8, py + 54, 18, (Color){255,230,80,255});
    DrawText(l3,                     px + 8, py + 80, 20, cor_borda);
}

/* ============================================================================
 * FASE COMPLETA
 * ========================================================================== */
void ui_desenhar_fase_completa(int num_fase) {
    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, (Color){0,0,0,160});
    DrawText("PORTA ABERTA!",
             640 - MeasureText("PORTA ABERTA!", 60)/2, 240, 60, (Color){80,255,80,255});
    char buf[64];
    snprintf(buf, sizeof(buf), "Fase %d concluida!", num_fase + 1);
    DrawText(buf, 640 - MeasureText(buf, 36)/2, 320, 36, WHITE);
    DrawText("Pressione ENTER para a proxima fase",
             640 - MeasureText("Pressione ENTER para a proxima fase", 24)/2,
             400, 24, (Color){200,220,255,220});
}

/* ============================================================================
 * VITORIA
 * ========================================================================== */
void ui_desenhar_vitoria(void) {
    ClearBackground((Color){ 10, 10, 30, 255 });
    DrawText("PARABENS!",
             640 - MeasureText("PARABENS!", 70)/2, 160, 70, (Color){255,220,50,255});
    DrawText("Voce resolveu todas as fases!",
             640 - MeasureText("Voce resolveu todas as fases!", 34)/2,
             260, 34, WHITE);
    DrawText("A logica proposicional foi sua aliada.",
             640 - MeasureText("A logica proposicional foi sua aliada.", 24)/2,
             320, 24, (Color){150,220,255,220});
    DrawText("Pressione ENTER para voltar ao menu ou ESC para sair",
             640 - MeasureText("Pressione ENTER para voltar ao menu ou ESC para sair", 20)/2,
             440, 20, (Color){160,180,220,200});
}
