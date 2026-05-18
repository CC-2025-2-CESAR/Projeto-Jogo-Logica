#include "raylib.h"
#include "tipos.h"
#include "game.h"

int main(void) {
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Logic Gates Adventure");
    SetTargetFPS(FPS_ALVO);

    EstadoJogo g = {0};
    game_inicializar(&g);

    while (!WindowShouldClose() && g.estado_atual != ESTADO_SAIR) {
        game_atualizar(&g);
        BeginDrawing();
            game_desenhar(&g);
        EndDrawing();
    }

    game_finalizar(&g);
    CloseWindow();
    return 0;
}
