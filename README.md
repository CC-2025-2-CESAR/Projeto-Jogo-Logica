# Logic Gates Adventure

Jogo de puzzle/plataforma 2D desenvolvido em C com Raylib para a disciplina de Lógica da CESAR School.

O jogador resolve fases manipulando proposições lógicas visuais. Cada porta do cenário exibe uma sentença lógica — como `P ∧ Q` ou `¬P ∧ Q` — e só abre quando a proposição for verdadeira. Um painel na tela mostra a avaliação em tempo real.

---

## Grupo

Arthur Reis · Arthur Almeida · Gabi Vital · Gabriel Malta · Luísa Fischer · Luísa Muniz · Maria Luísa Muniz · Matheus Assis · Sofia Vilela

---

## Como compilar

### Linux

```bash
# 1. Instalar dependências de sistema
sudo apt install cmake libx11-dev libxrandr-dev libxi-dev libxcursor-dev libxinerama-dev

# 2. Compilar e instalar a Raylib
git clone --depth=1 https://github.com/raysan5/raylib.git /tmp/raylib
cmake -S /tmp/raylib -B /tmp/raylib/build -DPLATFORM=Desktop -DCMAKE_BUILD_TYPE=Release
cmake --build /tmp/raylib/build --parallel
sudo cmake --install /tmp/raylib/build --prefix /usr/local

# 3. Compilar o jogo
make

# 4. Executar
./logic_gates
```

### Windows

Com Raylib instalado e disponível via `pkg-config`:

```bash
make
.\logic_gates.exe
```

---

## Controles

| Tecla | Ação |
|-------|------|
| `A` / `←` | Mover para a esquerda |
| `D` / `→` | Mover para a direita |
| `Espaço` / `W` / `↑` | Pular |
| `E` | Interagir com botão/alavanca |
| `R` | Reiniciar a fase |
| `ESC` | Voltar ao menu / sair |

---

## Fases

| Fase | Proposição | Objetivo |
|------|-----------|----------|
| 1 | `P ∧ Q` | Ativar **os dois** botões P e Q |
| 2 | `P ∨ Q` | Ativar **pelo menos um** botão |
| 3 | `¬P ∧ Q` | Deixar P **falso** e ativar apenas Q |

---

## Estrutura do projeto

```
src/
├── core/
│   ├── tipos.h          # Structs e enums (Jogador, Fase, Botao, Porta…)
│   ├── main.c           # Loop principal
│   ├── game.h / game.c  # Máquina de estados e integração
├── entidades/
│   └── player.h / player.c  # Física: gravidade, pulo, colisão
├── sistemas/
│   ├── logica.h / logica.c  # Avaliação das proposições
│   └── fases.h  / fases.c   # Definição das 3 fases
└── interface/
    └── ui.h / ui.c      # Menu, HUD e painel lógico
```

---

## Branches

| Branch | Módulo |
|--------|--------|
| `main` | Código estável — jogo completo |
| `feature/logica-proposicional` | Motor lógico e design das fases |
| `feature/fisica-jogador` | Física e movimentação do personagem |
| `feature/interface-hud` | Menu, créditos e painel lógico |
| `feature/gameplay-loop` | Loop principal e integração dos módulos |
