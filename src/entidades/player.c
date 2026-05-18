#include "player.h"
#include "raylib.h"

void player_inicializar(Jogador *j, Vector2 pos) {
    j->rect       = (Rectangle){ pos.x, pos.y, LARGURA_JOGADOR, ALTURA_JOGADOR };
    j->velocidade = (Vector2){ 0, 0 };
    j->no_chao    = false;
}

void player_atualizar(Jogador *j, const Fase *fase, float dt) {
    float vx = 0;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  vx = -VELOC_HORIZONTAL;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) vx =  VELOC_HORIZONTAL;
    j->velocidade.x = vx;

    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && j->no_chao) {
        j->velocidade.y = FORCA_PULO;
        j->no_chao = false;
    }

    j->velocidade.y += GRAVIDADE * dt;

    j->rect.x += j->velocidade.x * dt;
    j->rect.y += j->velocidade.y * dt;

    j->no_chao = false;
    for (int i = 0; i < fase->qtd_plataformas; i++) {
        Rectangle plat = fase->plataformas[i].rect;
        if (CheckCollisionRecs(j->rect, plat)) {
            if (j->velocidade.y >= 0 &&
                j->rect.y + j->rect.height - j->velocidade.y * dt <= plat.y + 2) {
                j->rect.y       = plat.y - j->rect.height;
                j->velocidade.y = 0;
                j->no_chao      = true;
            } else if (j->velocidade.x > 0 &&
                       j->rect.x + j->rect.width - j->velocidade.x * dt <= plat.x + 2) {
                j->rect.x = plat.x - j->rect.width;
            } else if (j->velocidade.x < 0 &&
                       j->rect.x - j->velocidade.x * dt >= plat.x + plat.width - 2) {
                j->rect.x = plat.x + plat.width;
            } else if (j->velocidade.y < 0) {
                j->rect.y       = plat.y + plat.height;
                j->velocidade.y = 0;
            }
        }
    }

    if (j->rect.x < 0) j->rect.x = 0;
    if (j->rect.x + j->rect.width > LARGURA_TELA)
        j->rect.x = LARGURA_TELA - j->rect.width;
}

void player_desenhar(const Jogador *j) {
    DrawRectangleRec(j->rect, (Color){ 70, 130, 220, 255 });
    float ex = j->rect.x + 6;
    float ey = j->rect.y + 10;
    DrawRectangle((int)ex,      (int)ey,     8, 8, WHITE);
    DrawRectangle((int)(ex+14), (int)ey,     8, 8, WHITE);
    DrawRectangle((int)(ex+2),  (int)(ey+2), 4, 4, (Color){20,20,80,255});
    DrawRectangle((int)(ex+16), (int)(ey+2), 4, 4, (Color){20,20,80,255});
}
