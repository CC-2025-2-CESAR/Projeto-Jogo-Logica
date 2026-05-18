# ============================================================================
# Makefile - Logic Gates Adventure
# ============================================================================
#
# Linux/macOS : make
# Windows     : use build.bat  (mais simples) ou
#               make RAYLIB_PATH=C:/raylib
#
# Estrutura:
#   src/core/         main.c, game.c, tipos.h
#   src/entidades/    player.c
#   src/sistemas/     logica.c, fases.c
#   src/interface/    ui.c
# ============================================================================

CC       := gcc
FONTES   := $(wildcard src/*.c) $(wildcard src/*/*.c)
INCLUDES := -Isrc -Isrc/core -Isrc/entidades -Isrc/sistemas -Isrc/interface
OBJETOS  := $(patsubst src/%.c,build/%.o,$(FONTES))

# ============================================================
# Windows (cmd + MinGW)
# ============================================================
ifeq ($(OS),Windows_NT)

# Caminho do Raylib — edite ou passe via: make RAYLIB_PATH=C:/meu/raylib
RAYLIB_PATH ?= C:/raylib

EXECUTAVEL       := logic_gates.exe
COMANDO_EXECUTAR := logic_gates.exe

RAYLIB_INC := -I$(RAYLIB_PATH)/include
RAYLIB_LIB := -L$(RAYLIB_PATH)/lib -lraylib -lopengl32 -lgdi32 -lwinmm -lm

CFLAGS  := -Wall -Wextra -std=c11 -g $(INCLUDES) $(RAYLIB_INC)
LDFLAGS := $(RAYLIB_LIB)

define CRIAR_PASTA
	if not exist "$(subst /,\,$(1))" mkdir "$(subst /,\,$(1))"
endef

# ============================================================
# Linux / macOS
# ============================================================
else

EXECUTAVEL       := logic_gates
COMANDO_EXECUTAR := ./logic_gates

# Detecta Raylib: pkg-config > /usr/local > fallback
ifeq ($(shell pkg-config --exists raylib 2>/dev/null && echo yes),yes)
    RAYLIB_INC := $(shell pkg-config --cflags raylib)
    RAYLIB_LIB := $(shell pkg-config --libs raylib)
else ifneq ($(wildcard /usr/local/include/raylib.h),)
    RAYLIB_INC := -I/usr/local/include
    RAYLIB_LIB := /usr/local/lib/libraylib.a
else
    RAYLIB_INC :=
    RAYLIB_LIB := -lraylib
endif

CFLAGS  := -Wall -Wextra -std=c11 -g $(INCLUDES) $(RAYLIB_INC)
LDFLAGS := $(RAYLIB_LIB) -lm -ldl -lpthread -lX11 -lXrandr -lXi -lXcursor -lXinerama

define CRIAR_PASTA
	mkdir -p $(1)
endef

endif

# ============================================================
# Regras
# ============================================================
.PHONY: all run executar clean limpar

all: $(EXECUTAVEL)

$(EXECUTAVEL): $(OBJETOS)
	$(CC) $(OBJETOS) -o $@ $(LDFLAGS)
	@echo ""
	@echo "==> Logic Gates Adventure compilado com sucesso!"
	@echo ""

build/%.o: src/%.c
	$(call CRIAR_PASTA,$(dir $@))
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
