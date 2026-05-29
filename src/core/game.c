#include "game.h"
#include "player.h"
#include "fases.h"
#include "logica.h"
#include "ui.h"
#include "raylib.h"
#include <stdio.h>
#include <math.h>

/* ============================================================================
 * AUXILIARES INTERNOS
 * ========================================================================== */

/* Desenha o cenario: plataformas, botoes e porta */
static void desenhar_cenario(const Fase *fase) {
    /* Plataformas */
    for (int i = 0; i < fase->qtd_plataformas; i++) {
        const Plataforma *pl = &fase->plataformas[i];
        if (pl->colapsada) continue;
        DrawRectangleRec(pl->rect, pl->cor);
        DrawRectangleLinesEx(pl->rect, 2, (Color){0,0,0,80});
    }

    /* Inimigo */
    if (fase->tem_inimigo && fase->inimigo.ativo) {
        float ex = fase->inimigo.pos.x;
        float ey = fase->inimigo.pos.y;
        DrawRectangle((int)ex, (int)ey, 32, 32, (Color){220, 30, 30, 255});
        DrawRectangleLinesEx((Rectangle){ex, ey, 32, 32}, 2, (Color){255, 110, 110, 255});
        DrawRectangle((int)ex + 5,  (int)ey + 8, 6, 6, (Color){255, 220, 0, 255});
        DrawRectangle((int)ex + 21, (int)ey + 8, 6, 6, (Color){255, 220, 0, 255});
    }

    /* Botoes */
    for (int i = 0; i < fase->qtd_botoes; i++) {
        const Botao *b = &fase->botoes[i];
        Color cor = b->ativo ? b->cor_ativo : b->cor_inativo;
        DrawRectangleRec(b->rect, cor);
        DrawRectangleLinesEx(b->rect, 2, WHITE);
        /* Label da variavel */
        DrawText(b->label,
                 (int)(b->rect.x + b->rect.width/2  - MeasureText(b->label, 18)/2),
                 (int)(b->rect.y + b->rect.height/2 - 9),
                 18, WHITE);
        /* Estado V/F abaixo */
        const char *vf = b->ativo ? "V" : "F";
        Color cvf = b->ativo ? (Color){50,255,50,255} : (Color){255,80,80,255};
        DrawText(vf,
                 (int)(b->rect.x + b->rect.width/2 - MeasureText(vf, 14)/2),
                 (int)(b->rect.y + b->rect.height + 4),
                 14, cvf);
    }

    /* Porta */
    const Porta *p = &fase->porta;
    if (p->aberta) {
        /* Porta aberta: contorno verde */
        DrawRectangleLinesEx(p->rect, 4, (Color){50,255,50,255});
        DrawText("ABERTA",
                 (int)(p->rect.x + p->rect.width/2 - MeasureText("ABERTA",14)/2),
                 (int)(p->rect.y - 22), 14, (Color){50,255,50,255});
    } else {
        DrawRectangleRec(p->rect, (Color){180,60,20,255});
        DrawRectangleLinesEx(p->rect, 3, (Color){220,100,40,255});
        /* Proposicao acima da porta */
        DrawText(fase->titulo_prop,
                 (int)(p->rect.x + p->rect.width/2 - MeasureText(fase->titulo_prop, 16)/2),
                 (int)(p->rect.y - 26), 16, (Color){255,220,80,255});
        DrawText("FECHADA",
                 (int)(p->rect.x + p->rect.width/2 - MeasureText("FECHADA",12)/2),
                 (int)(p->rect.y - 44), 12, (Color){255,80,80,220});

        /* Botao de confirmacao */
        Rectangle bc = fase->botao_confirmar;
        DrawRectangleRec(bc, (Color){180, 140, 20, 255});
        DrawRectangleLinesEx(bc, 2, (Color){255, 220, 60, 255});
        const char *txt = "CONFIRMAR";
        DrawText(txt,
                 (int)(bc.x + bc.width/2 - MeasureText(txt, 12)/2),
                 (int)(bc.y + bc.height/2 - 6),
                 12, (Color){20, 10, 0, 255});
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

/* Verifica se jogador esta proximo do botao de confirmacao */
static bool confirmar_proximo(const Fase *fase, const Jogador *j) {
    Rectangle area = fase->botao_confirmar;
    area.x -= 20; area.y -= 20;
    area.width += 40; area.height += 40;
    return CheckCollisionRecs(j->rect, area);
}

/* ============================================================================
 * INICIALIZACAO
 * ========================================================================== */
void game_inicializar(EstadoJogo *g) {
    g->estado_atual    = ESTADO_MENU;
    g->num_fase        = 0;
    g->opcao_menu      = 0;
    g->timer_transicao = 0;
    g->timer_fase      = 45.0f;
    fase_carregar(&g->fase_atual, 0);
    player_inicializar(&g->jogador, g->fase_atual.pos_inicial_jogador);
}

/* ============================================================================
 * ATUALIZACAO
 * ========================================================================== */
void game_atualizar(EstadoJogo *g) {
    float dt = GetFrameTime();

    switch (g->estado_atual) {

    /* ---------- MENU ---------- */
    case ESTADO_MENU: {
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))   g->opcao_menu = (g->opcao_menu + 2) % 3;
        if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) g->opcao_menu = (g->opcao_menu + 1) % 3;
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) {
            if (g->opcao_menu == 0) {
                g->num_fase   = 0;
                g->timer_fase = 45.0f;
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

    /* ---------- CREDITOS ---------- */
    case ESTADO_CREDITOS: {
        if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER))
            g->estado_atual = ESTADO_MENU;
        break;
    }

    /* ---------- JOGANDO ---------- */
    case ESTADO_JOGANDO: {
        if (IsKeyPressed(KEY_ESCAPE)) { g->estado_atual = ESTADO_MENU; break; }

        /* Reiniciar fase */
        if (IsKeyPressed(KEY_R)) {
            g->timer_fase = 45.0f;
            fase_carregar(&g->fase_atual, g->num_fase);
            player_inicializar(&g->jogador, g->fase_atual.pos_inicial_jogador);
            break;
        }

        /* Contagem regressiva */
        g->timer_fase -= dt;
        if (g->timer_fase <= 0.0f) {
            g->timer_fase        = 0.0f;
            g->timer_transicao   = 0;
            g->motivo_game_over  = MOTIVO_TEMPO_ESGOTADO;
            g->estado_atual      = ESTADO_GAME_OVER;
            break;
        }

        /* Atualizar jogador */
        player_atualizar(&g->jogador, &g->fase_atual, dt);

        /* Interacao com botoes e botao de confirmacao */
        if (IsKeyPressed(KEY_E)) {
            int idx = botao_proximo(&g->fase_atual, &g->jogador);
            if (idx >= 0) {
                Botao *b = &g->fase_atual.botoes[idx];
                b->ativo = !b->ativo;
                g->fase_atual.variaveis[b->variavel_idx] = b->ativo;
            } else if (!g->fase_atual.porta.aberta &&
                       confirmar_proximo(&g->fase_atual, &g->jogador)) {
                if (logica_avaliar(&g->fase_atual)) {
                    g->fase_atual.porta.aberta = true;
                } else {
                    g->timer_transicao  = 0;
                    g->motivo_game_over = MOTIVO_RESPOSTA_ERRADA;
                    g->estado_atual     = ESTADO_GAME_OVER;
                }
            }
        }

        /* Plataformas instaveis */
        for (int i = 0; i < g->fase_atual.qtd_plataformas; i++) {
            Plataforma *pl = &g->fase_atual.plataformas[i];
            if (!pl->instavel || pl->colapsada) continue;
            bool em_cima =
                g->jogador.no_chao &&
                g->jogador.rect.y + g->jogador.rect.height >= pl->rect.y - 2 &&
                g->jogador.rect.y + g->jogador.rect.height <= pl->rect.y + pl->rect.height + 5 &&
                g->jogador.rect.x + g->jogador.rect.width  > pl->rect.x &&
                g->jogador.rect.x < pl->rect.x + pl->rect.width;
            if (em_cima && !pl->acionada) pl->acionada = true;
            if (pl->acionada) {
                pl->timer_colapso -= dt;
                if (pl->timer_colapso <= 0.0f) pl->colapsada = true;
            }
        }

        /* Inimigo perseguidor */
        if (g->fase_atual.tem_inimigo && g->fase_atual.inimigo.ativo) {
            Inimigo *en = &g->fase_atual.inimigo;
            float cx = g->jogador.rect.x + LARGURA_JOGADOR / 2.0f;
            float cy = g->jogador.rect.y + ALTURA_JOGADOR  / 2.0f;
            float dx = cx - (en->pos.x + 16);
            float dy = cy - (en->pos.y + 16);
            float dist = sqrtf(dx*dx + dy*dy);
            if (dist > 1.0f) {
                en->pos.x += (dx / dist) * en->speed * dt;
                en->pos.y += (dy / dist) * en->speed * dt;
            }
            Rectangle er = { en->pos.x, en->pos.y, 32, 32 };
            if (CheckCollisionRecs(g->jogador.rect, er)) {
                g->timer_transicao  = 0;
                g->motivo_game_over = MOTIVO_INIMIGO;
                g->estado_atual     = ESTADO_GAME_OVER;
                break;
            }
        }

        /* Verifica se jogador entrou na porta aberta */
        if (g->fase_atual.porta.aberta &&
            CheckCollisionRecs(g->jogador.rect, g->fase_atual.porta.rect)) {
            g->timer_transicao = 0;
            g->estado_atual = ESTADO_FASE_COMPLETA;
        }
        break;
    }

    /* ---------- FASE COMPLETA ---------- */
    case ESTADO_FASE_COMPLETA: {
        g->timer_transicao += dt;
        if ((IsKeyPressed(KEY_ENTER) || g->timer_transicao > 3.0f)) {
            g->num_fase++;
            if (g->num_fase >= fase_total()) {
                g->estado_atual = ESTADO_VITORIA;
            } else {
                g->timer_fase = 45.0f;
                fase_carregar(&g->fase_atual, g->num_fase);
                player_inicializar(&g->jogador, g->fase_atual.pos_inicial_jogador);
                g->estado_atual = ESTADO_JOGANDO;
            }
        }
        break;
    }

    /* ---------- GAME OVER ---------- */
    case ESTADO_GAME_OVER: {
        g->timer_transicao += dt;
        if (IsKeyPressed(KEY_ENTER) || g->timer_transicao > 3.0f) {
            g->num_fase   = 0;
            g->timer_fase = 45.0f;
            fase_carregar(&g->fase_atual, 0);
            player_inicializar(&g->jogador, g->fase_atual.pos_inicial_jogador);
            g->estado_atual = ESTADO_JOGANDO;
        }
        break;
    }

    /* ---------- VITORIA ---------- */
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
        /* Fundo */
        ClearBackground((Color){ 20, 20, 45, 255 });
        /* Cenario */
        desenhar_cenario(&g->fase_atual);
        /* Jogador */
        player_desenhar(&g->jogador);
        /* HUD */
        ui_desenhar_hud(&g->fase_atual);
        /* Painel logico */
        ui_desenhar_painel_logico(&g->fase_atual);
        /* Numero da fase no topo esquerdo */
        char buf[32];
        snprintf(buf, sizeof(buf), "FASE %d / %d", g->num_fase + 1, fase_total());
        DrawText(buf, 10, 58, 20, (Color){200,200,200,220});
        /* Timer */
        ui_desenhar_timer(g->timer_fase);
        /* Indicador de interacao proximo */
        {
            int idx = botao_proximo(&g->fase_atual, &g->jogador);
            if (idx >= 0) {
                const Botao *b = &g->fase_atual.botoes[idx];
                DrawText("[E]",
                         (int)(b->rect.x + b->rect.width/2 - MeasureText("[E]",16)/2),
                         (int)(b->rect.y - 24), 16, (Color){255,255,80,255});
            } else if (!g->fase_atual.porta.aberta &&
                       confirmar_proximo(&g->fase_atual, &g->jogador)) {
                Rectangle bc = g->fase_atual.botao_confirmar;
                const char *hint = "[E] CONFIRMAR";
                DrawText(hint,
                         (int)(bc.x + bc.width/2 - MeasureText(hint,15)/2),
                         (int)(bc.y - 24), 15, (Color){255,220,60,255});
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

    case ESTADO_GAME_OVER:
        ClearBackground((Color){ 20, 20, 45, 255 });
        desenhar_cenario(&g->fase_atual);
        player_desenhar(&g->jogador);
        ui_desenhar_game_over(g->motivo_game_over);
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
    (void)g; /* nada a liberar por ora */
}
