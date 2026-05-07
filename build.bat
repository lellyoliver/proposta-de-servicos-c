@echo off
setlocal

:: ================================
:: CONFIGURAÇÕES
:: ================================

set MSYS=C:\msys64
set PROJ=C:\Users\Lenovo\Documents\Faculdade\proposta-de-servicos-c

:: Todos os .c
set SRC=src/*.c

:: Executável
set OUT=bin/app.exe

:: ================================
:: BUILD
:: ================================

echo Compilando...

"%MSYS%\usr\bin\env.exe" MSYSTEM=MINGW64 "%MSYS%\usr\bin\bash.exe" -lc "cd $(cygpath '%PROJ%') && mkdir -p bin && gcc %SRC% -Iinc -o %OUT% $(pkg-config --cflags --libs gtk4) -lmysqlclient"

if errorlevel 1 (
    echo.
    echo Erro na compilacao
    pause
    exit /b
)

echo.
echo Copiando DLLs...

xcopy "%MSYS%\mingw64\bin\*.dll" "%PROJ%\bin\" /Y >nul

echo.
echo Build concluido!
echo Executavel: %OUT%
pause