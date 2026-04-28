@echo off
setlocal

:: ================================
:: CONFIGURAÇÕES (EDITE AQUI)
:: ================================

:: Caminho do MSYS2
set MSYS=C:\msys64

:: Caminho do seu projeto
set PROJ=C:\Users\Lenovo\Documents\Faculdade\proposta-de-servicos-c

:: Caminho do código fonte (agora usa todos os .c)
set SRC=app/main.c app/bd.c

:: Nome do executável
set OUT=app.exe

:: ================================
:: BUILD
:: ================================

echo Compilando...

"%MSYS%\usr\bin\env.exe" MSYSTEM=MINGW64 "%MSYS%\usr\bin\bash.exe" -lc "cd $(cygpath '%PROJ%') && gcc %SRC% -o %OUT% $(pkg-config --cflags --libs gtk4) -lmysqlclient"

if errorlevel 1 (
    echo Erro na compilacao
    pause
    exit /b
)

echo Copiando DLLs...

xcopy "%MSYS%\mingw64\bin\*.dll" "%PROJ%\" /Y >nul

echo.
echo Build concluido! %OUT% atualizado
pause