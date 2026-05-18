@echo off
chcp 65001 > nul
setlocal

rem ============================================================
rem  build.bat - Logic Gates Adventure
rem  Compilador: MinGW (gcc) + Raylib para Windows
rem ============================================================
rem
rem  COMO USAR:
rem  1. Baixe o Raylib para Windows em:
rem     https://github.com/raysan5/raylib/releases
rem     Escolha: raylib-X.X.X_win64_mingw-w64.zip
rem
rem  2. Extraia o zip. Dentro voce tera uma pasta com:
rem       include\raylib.h
rem       lib\libraylib.a
rem
rem  3. Ajuste RAYLIB_PATH abaixo para apontar para essa pasta.
rem
rem  4. Certifique-se que gcc.exe esta no PATH.
rem     Se usar o w64devkit que vem com o Raylib, ajuste GCC abaixo.
rem
rem  Execute este arquivo clicando duas vezes ou via terminal:
rem     build.bat
rem ============================================================

rem --- CONFIGURE AQUI -------------------------------------------
rem Caminho da pasta do Raylib (onde estao as pastas include\ e lib\)
set RAYLIB_PATH=C:\raylib

rem Compilador. Se o gcc estiver no PATH, deixe apenas "gcc".
rem Se usar o w64devkit do Raylib, aponte para ele, por exemplo:
rem   set GCC=C:\raylib\w64devkit\bin\gcc.exe
set GCC=gcc
rem --------------------------------------------------------------

echo.
echo ============================================
echo   Logic Gates Adventure - Build Windows
echo ============================================
echo.

rem Verifica se gcc existe
where %GCC% > nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo [ERRO] Compilador nao encontrado: %GCC%
    echo.
    echo Opcoes:
    echo   1. Instale o w64devkit: https://github.com/skeeto/w64devkit/releases
    echo   2. Ou instale o MinGW-w64: https://winlibs.com
    echo   3. Ajuste a variavel GCC no inicio deste arquivo.
    echo.
    goto fim_erro
)

rem Verifica se o Raylib esta no caminho configurado
if not exist "%RAYLIB_PATH%\include\raylib.h" (
    echo [ERRO] raylib.h nao encontrado em: %RAYLIB_PATH%\include\
    echo.
    echo Solucao:
    echo   1. Baixe o Raylib em https://github.com/raysan5/raylib/releases
    echo      Arquivo: raylib-X.X.X_win64_mingw-w64.zip
    echo   2. Extraia para %RAYLIB_PATH%
    echo   3. Verifique se existe: %RAYLIB_PATH%\include\raylib.h
    echo   4. Ou edite RAYLIB_PATH no inicio deste arquivo.
    echo.
    goto fim_erro
)

if not exist "%RAYLIB_PATH%\lib\libraylib.a" (
    echo [ERRO] libraylib.a nao encontrado em: %RAYLIB_PATH%\lib\
    echo Verifique se a pasta lib\ existe dentro de %RAYLIB_PATH%
    echo.
    goto fim_erro
)

echo [OK] GCC encontrado
echo [OK] Raylib encontrado em %RAYLIB_PATH%
echo.

rem Cria pastas de build
if not exist build             mkdir build
if not exist build\core        mkdir build\core
if not exist build\entidades   mkdir build\entidades
if not exist build\sistemas    mkdir build\sistemas
if not exist build\interface   mkdir build\interface

rem Flags de compilacao
set INCLUDES=-Isrc\core -Isrc\entidades -Isrc\sistemas -Isrc\interface -I%RAYLIB_PATH%\include
set LIBS=-L%RAYLIB_PATH%\lib -lraylib -lopengl32 -lgdi32 -lwinmm -lm
set CFLAGS=-Wall -Wextra -std=c11 -g %INCLUDES%

echo Compilando modulos...

%GCC% %CFLAGS% -c src\core\main.c          -o build\core\main.o
if %ERRORLEVEL% neq 0 goto fim_erro

%GCC% %CFLAGS% -c src\core\game.c          -o build\core\game.o
if %ERRORLEVEL% neq 0 goto fim_erro

%GCC% %CFLAGS% -c src\entidades\player.c   -o build\entidades\player.o
if %ERRORLEVEL% neq 0 goto fim_erro

%GCC% %CFLAGS% -c src\sistemas\logica.c    -o build\sistemas\logica.o
if %ERRORLEVEL% neq 0 goto fim_erro

%GCC% %CFLAGS% -c src\sistemas\fases.c     -o build\sistemas\fases.o
if %ERRORLEVEL% neq 0 goto fim_erro

%GCC% %CFLAGS% -c src\interface\ui.c       -o build\interface\ui.o
if %ERRORLEVEL% neq 0 goto fim_erro

echo Linkando...

%GCC% build\core\main.o build\core\game.o build\entidades\player.o ^
      build\sistemas\logica.o build\sistemas\fases.o build\interface\ui.o ^
      -o logic_gates.exe %LIBS%
if %ERRORLEVEL% neq 0 goto fim_erro

echo.
echo ============================================
echo   Compilado com sucesso!
echo   Execute: logic_gates.exe
echo ============================================
echo.
goto fim

:fim_erro
echo.
echo ============================================
echo   FALHA na compilacao.
echo ============================================
echo.

:fim
endlocal
pause
