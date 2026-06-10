@echo off
setlocal

set MSYS=C:\msys64
set PROJ=C:\Users\Lenovo\Documents\Faculdade\proposta-de-servicos-c
set SRC=src/*.c
set OUT=bin/app.exe

echo ================================
echo Arquivos C que serao compilados:
echo ================================

dir "%PROJ%\src\*.c" /b

echo.
echo Compilando...

"%MSYS%\usr\bin\env.exe" MSYSTEM=MINGW64 "%MSYS%\usr\bin\bash.exe" -lc "cd $(cygpath '%PROJ%') && mkdir -p bin && gcc %SRC% -Iinc -o %OUT% -lmysqlclient"

if errorlevel 1 (
    echo.
    echo Erro na compilacao
    pause
    exit /b
)

echo.
echo Copiando DLLs necessarias...

copy "%MSYS%\mingw64\bin\libmariadb.dll" "%PROJ%\bin\" /Y
copy "%MSYS%\mingw64\bin\libgcc_s_seh-1.dll" "%PROJ%\bin\" /Y
copy "%MSYS%\mingw64\bin\libwinpthread-1.dll" "%PROJ%\bin\" /Y
copy "%MSYS%\mingw64\bin\zlib1.dll" "%PROJ%\bin\" /Y
copy "%MSYS%\mingw64\bin\libcrypto-3-x64.dll" "%PROJ%\bin\" /Y
copy "%MSYS%\mingw64\bin\libssl-3-x64.dll" "%PROJ%\bin\" /Y

copy "%MSYS%\mingw64\bin\libzstd.dll" "%PROJ%\bin\" /Y
copy "%MSYS%\mingw64\bin\libcurl-4.dll" "%PROJ%\bin\" /Y
copy "%MSYS%\mingw64\bin\libbrotlidec.dll" "%PROJ%\bin\" /Y
copy "%MSYS%\mingw64\bin\libidn2-0.dll" "%PROJ%\bin\" /Y
copy "%MSYS%\mingw64\bin\libnghttp3-9.dll" "%PROJ%\bin\" /Y
copy "%MSYS%\mingw64\bin\libnghttp2-14.dll" "%PROJ%\bin\" /Y
copy "%MSYS%\mingw64\bin\libngtcp2_crypto_ossl-0.dll" "%PROJ%\bin\" /Y
copy "%MSYS%\mingw64\bin\libpsl-5.dll" "%PROJ%\bin\" /Y
copy "%MSYS%\mingw64\bin\libngtcp2-16.dll" "%PROJ%\bin\" /Y
copy "%MSYS%\mingw64\bin\libssh2-1.dll" "%PROJ%\bin\" /Y
copy "%MSYS%\mingw64\bin\libiconv-2.dll" "%PROJ%\bin\" /Y
copy "%MSYS%\mingw64\bin\libintl-8.dll" "%PROJ%\bin\" /Y
copy "%MSYS%\mingw64\bin\libbrotlicommon.dll" "%PROJ%\bin\" /Y
copy "%MSYS%\mingw64\bin\libunistring-5.dll" "%PROJ%\bin\" /Y

echo.
echo Build concluido!
echo Executavel: %OUT%
pause