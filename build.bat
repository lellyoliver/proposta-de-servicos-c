@echo off
setlocal

:: ================================
:: CONFIGURAÇÕES (EDITE AQUI)
:: ================================

:: Caminho do MSYS2
set MSYS=C:\msys64


:: Caminho do seu projeto
set PROJ=C:\seu\camninho\da\pasta\aqui

:: Caminho do código fonte
set SRC=src/main.c

:: Nome do executável
set OUT=app.exe

:: ================================
:: BUILD
:: ================================

echo Compilando...

"%MSYS%\usr\bin\env.exe" MSYSTEM=MINGW64 "%MSYS%\usr\bin\bash.exe" -lc "cd $(cygpath '%PROJ%') && gcc %SRC% -o %OUT% $(pkg-config --cflags --libs gtk4)"

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