# ============================================================================
# Makefile - Logic Gates Adventure
# ============================================================================
#
# Estrutura:
#   src/core/         main.c, game.c, tipos.h
#   src/entidades/    player.c
#   src/sistemas/     logica.c, fases.c
#   src/interface/    ui.c
# ============================================================================

CC         := gcc
PKG_CONFIG := pkg-config

FONTES   := $(wildcard src/*.c) $(wildcard src/*/*.c)
INCLUDES := -Isrc -Isrc/core -Isrc/entidades -Isrc/sistemas -Isrc/interface

OBJETOS  := $(patsubst src/%.c,build/%.o,$(FONTES))

RAYLIB_INC := $(shell \
    if pkg-config --exists raylib 2>/dev/null; then pkg-config --cflags raylib; \
    elif [ -f /usr/local/include/raylib.h ]; then echo "-I/usr/local/include"; \
    else echo ""; fi)

RAYLIB_LIB := $(shell \
    if pkg-config --exists raylib 2>/dev/null; then pkg-config --libs raylib; \
    elif [ -f /usr/local/lib/libraylib.a ]; then echo "/usr/local/lib/libraylib.a"; \
    else echo "-lraylib"; fi)

ifeq ($(OS),Windows_NT)
    EXECUTAVEL      := logic_gates.exe
    COMANDO_EXECUTAR:= .\logic_gates.exe
    CFLAGS  := -Wall -Wextra -std=c11 -g $(INCLUDES) $(RAYLIB_INC)
    LDFLAGS := $(RAYLIB_LIB) -lopengl32 -lgdi32 -lwinmm -lm
    define CRIAR_PASTA
        if not exist "$(subst /,\,$(1))" mkdir "$(subst /,\,$(1))"
    endef
else
    EXECUTAVEL      := logic_gates
    COMANDO_EXECUTAR:= ./logic_gates
    CFLAGS  := -Wall -Wextra -std=c11 -g $(INCLUDES) $(RAYLIB_INC)
    LDFLAGS := $(RAYLIB_LIB) -lm -ldl -lpthread -lX11 -lXrandr -lXi -lXcursor -lXinerama
    define CRIAR_PASTA
        mkdir -p $(1)
    endef
endif

.PHONY: all run executar clean limpar

all: $(EXECUTAVEL)

$(EXECUTAVEL): $(OBJETOS)
	$(CC) $(OBJETOS) -o $@ $(LDFLAGS)
	@echo ""
	@echo "==> Logic Gates Adventure compilado com sucesso!"
	@echo ""

build/%.o: src/%.c
	@$(call CRIAR_PASTA,$(dir $@))
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXECUTAVEL)
	$(COMANDO_EXECUTAR)

executar: run

clean:
ifeq ($(OS),Windows_NT)
	@if exist build rmdir /S /Q build
	@if exist logic_gates.exe del /Q logic_gates.exe
else
	rm -rf build logic_gates logic_gates.exe
endif

limpar: clean
