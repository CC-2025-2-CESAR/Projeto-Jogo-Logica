#include "game.h"
#include "player.h"
#include "fases.h"
#include "logica.h"
#include "ui.h"
#include "raylib.h"
#include <stdio.h>

/* ============================================================================
 * AUXILIARES INTERNOS
 * ========================================================================== */

/* Desenha o cenario: plataformas, botoes e porta */
static void desenhar_cenario(const Fase *fase) {
    for (int i = 0; i < fase->qtd_plataformas; i++) {
        DrawRectangleRec(fase->plataformas[i].rect, fase->plataformas[i].cor);
        DrawRectangleLinesEx(fase->plataformas[i].rect, 2, (Color){0,0,0,80});
    }

    for (int i = 0; i < fase->qtd_botoes; i++) {
        const Botao *b = &fase->botoes[i];
        Color cor = b->ativo ? b->cor_ativo : b->cor_inativo;
        DrawRectangleRec(b->rect, cor);
        DrawRectangleLinesEx(b->rect, 2, WHITE);
        DrawText(b->label,
                 (int)(b->rect.x + b->rect.width/2  - MeasureText(b->label, 18)/2),
                 (int)(b->rect.y + b->rect.height/2 - 9),
                 18, WHITE);
        const char *vf = b->ativo ? "V" : "F";
        Color cvf = b->ativo ? (Color){50,255,50,255} : (Color){255,80,80,255};
        DrawText(vf,
                 (int)(b->rect.x + b->rect.width/2 - MeasureText(vf, 14)/2),
                 (int)(b->rect.y + b->rect.height + 4),
                 14, cvf);
    }

    const Porta *p = &fase->porta;
    if (p->aberta) {
        DrawRectangleLinesEx(p->rect, 4, (Color){50,255,50,255});
        DrawText("ABERTA",
                 (int)(p->rect.x + p->rect.width/2 - MeasureText("ABERTA",14)/2),
                 (int)(p->rect.y - 22), 14, (Color){50,255,50,255});
    } else {
        DrawRectangleRec(p->rect, (Color){180,60,20,255});
        DrawRectangleLinesEx(p->rect, 3, (Color){220,100,40,255});
        DrawText(fase->titulo_prop,
                 (int)(p->rect.x + p->rect.width/2 - MeasureText(fase->titulo_prop, 16)/2),
                 (int)(p->rect.y - 26), 16, (Color){255,220,80,255});
        DrawText("FECHADA",
                 (int)(p->rect.x + p->rect.width/2 - MeasureText("FECHADA",12)/2),
                 (int)(p->rect.y - 44), 12, (Color){255,80,80,220});
    }
}

/* Verifica se jogador esta proximo de um botao e retorna o indice, ou -1 */
static int botao_proximo(const Fase *fase, const Jogador *j) {
    for (int i = 0; i < fase->qtd_botoes; i++) {
        Rectangle area = fase->botoes[i].rect;
        area.x -= 20; area.y -= 20;
        area.width += 40; area.height += 40;
        if (CheckCollisionRecs(j->rect, area)) return i;
    }
    return -1;
}

/* ============================================================================
 * INICIALIZACAO
 * ========================================================================== */
void game_inicializar(EstadoJogo *g) {
    g->estado_atual    = ESTADO_MENU;
    g->num_fase        = 0;
    g->opcao_menu      = 0;
    g->timer_transicao = 0;
    fase_carregar(&g->fase_atual, 0);
    player_inicializar(&g->jogador, g->fase_atual.pos_inicial_jogador);
}

/* ============================================================================
 * ATUALIZACAO
 * ========================================================================== */
void game_atualizar(EstadoJogo *g) {
    float dt = GetFrameTime();

    switch (g->estado_atual) {

    case ESTADO_MENU: {
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))   g->opcao_menu = (g->opcao_menu + 2) % 3;
        if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) g->opcao_menu = (g->opcao_menu + 1) % 3;
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) {
            if (g->opcao_menu == 0) {
                g->num_fase = 0;
                fase_carregar(&g->fase_atual, 0);
                player_inicializar(&g->jogador, g->fase_atual.pos_inicial_jogador);
                g->estado_atual = ESTADO_JOGANDO;
            } else if (g->opcao_menu == 1) {
                g->estado_atual = ESTADO_CREDITOS;
            } else {
                g->estado_atual = ESTADO_SAIR;
            }
        }
        break;
    }

    case ESTADO_CREDITOS: {
        if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER))
            g->estado_atual = ESTADO_MENU;
        break;
    }

    case ESTADO_JOGANDO: {
        if (IsKeyPressed(KEY_ESCAPE)) { g->estado_atual = ESTADO_MENU; break; }

        if (IsKeyPressed(KEY_R)) {
            fase_carregar(&g->fase_atual, g->num_fase);
            player_inicializar(&g->jogador, g->fase_atual.pos_inicial_jogador);
            break;
        }

        player_atualizar(&g->jogador, &g->fase_atual, dt);

        if (IsKeyPressed(KEY_E)) {
            int idx = botao_proximo(&g->fase_atual, &g->jogador);
            if (idx >= 0) {
                Botao *b = &g->fase_atual.botoes[idx];
                b->ativo = !b->ativo;
                g->fase_atual.variaveis[b->variavel_idx] = b->ativo;
            }
        }

        g->fase_atual.porta.aberta = logica_avaliar(&g->fase_atual);

        if (g->fase_atual.porta.aberta &&
            CheckCollisionRecs(g->jogador.rect, g->fase_atual.porta.rect)) {
            g->timer_transicao = 0;
            g->estado_atual = ESTADO_FASE_COMPLETA;
        }
        break;
    }

    case ESTADO_FASE_COMPLETA: {
        g->timer_transicao += dt;
        if ((IsKeyPressed(KEY_ENTER) || g->timer_transicao > 3.0f)) {
            g->num_fase++;
            if (g->num_fase >= fase_total()) {
                g->estado_atual = ESTADO_VITORIA;
            } else {
                fase_carregar(&g->fase_atual, g->num_fase);
                player_inicializar(&g->jogador, g->fase_atual.pos_inicial_jogador);
                g->estado_atual = ESTADO_JOGANDO;
            }
        }
        break;
    }

    case ESTADO_VITORIA: {
        if (IsKeyPressed(KEY_ENTER)) {
            g->num_fase = 0;
            fase_carregar(&g->fase_atual, 0);
            player_inicializar(&g->jogador, g->fase_atual.pos_inicial_jogador);
            g->estado_atual = ESTADO_MENU;
        }
        break;
    }

    case ESTADO_SAIR: break;
    }
}

/* ============================================================================
 * DESENHO
 * ========================================================================== */
void game_desenhar(const EstadoJogo *g) {
    switch (g->estado_atual) {

    case ESTADO_MENU:
        ui_desenhar_menu(g->opcao_menu);
        break;

    case ESTADO_CREDITOS:
        ui_desenhar_creditos();
        break;

    case ESTADO_JOGANDO: {
        ClearBackground((Color){ 20, 20, 45, 255 });
        desenhar_cenario(&g->fase_atual);
        player_desenhar(&g->jogador);
        ui_desenhar_hud(&g->fase_atual);
        ui_desenhar_painel_logico(&g->fase_atual);
        char buf[32];
        snprintf(buf, sizeof(buf), "FASE %d / %d", g->num_fase + 1, fase_total());
        DrawText(buf, 10, 58, 20, (Color){200,200,200,220});
        {
            int idx = botao_proximo(&g->fase_atual, &g->jogador);
            if (idx >= 0) {
                const Botao *b = &g->fase_atual.botoes[idx];
                DrawText("[E]",
                         (int)(b->rect.x + b->rect.width/2 - MeasureText("[E]",16)/2),
                         (int)(b->rect.y - 24), 16, (Color){255,255,80,255});
            }
        }
        break;
    }

    case ESTADO_FASE_COMPLETA:
        ClearBackground((Color){ 20, 20, 45, 255 });
        desenhar_cenario(&g->fase_atual);
        player_desenhar(&g->jogador);
        ui_desenhar_painel_logico(&g->fase_atual);
        ui_desenhar_fase_completa(g->num_fase);
        break;

    case ESTADO_VITORIA:
        ui_desenhar_vitoria();
        break;

    case ESTADO_SAIR: break;
    }
}

/* ============================================================================
 * FINALIZACAO
 * ========================================================================== */
void game_finalizar(EstadoJogo *g) {
    (void)g;
}
