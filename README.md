# 📦 proposta-de-servicos-c

Guia completo para configurar ambiente em C com GTK4 no Windows usando MSYS2.

---

## 🧱 Instalação do GTK4 no Windows (MSYS2)

### 🚀 1. Instalar o MSYS2

1. Baixe o instalador oficial:

👉 [Download MSYS2 (2026-03-22)](https://github.com/msys2/msys2-installer/releases/download/2026-03-22/msys2-x86_64-20260322.exe)

2. Instale no caminho padrão:

```bash
C:\msys64
```

---

### ⚠️ Ajuste necessário (caso falte mirrorlist)

Antes de continuar, verifique se existe o arquivo:

```
C:\msys64\etc\pacman.d\mirrorlist.mingw64
```

Se **não existir**, faça o seguinte:

1. Abra o terminal:

```
MSYS2 MinGW64
```

2. Execute:

```bash
cp /etc/pacman.d/mirrorlist.mingw /etc/pacman.d/mirrorlist.mingw64
```

3. Confirme se o arquivo foi criado corretamente na pasta:

```
C:\msys64\etc\pacman.d
```

---

## 🔄 2. Atualizar o MSYS2 (OBRIGATÓRIO)

### 👉 Primeira atualização

Abra:

```
MSYS2 MSYS
```

Execute:

```bash
pacman -Syu
```

> Se o terminal pedir para fechar, apenas feche.

---

### 👉 Segunda atualização

Abra novamente:

```
MSYS2 MSYS
```

Execute:

```bash
pacman -Su
```

---

## ⚙️ 3. Instalar GTK4 e ferramentas

Agora utilize o terminal correto:

```
MSYS2 MinGW64
```

Execute:

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gtk4 mingw-w64-x86_64-pkgconf
```

---

## ✅ 4. Validar instalação

Execute os comandos abaixo para garantir que tudo está funcionando:

```bash
gcc --version
pkg-config --version
pkg-config --cflags gtk4
```

@echo off
setlocal

:: ================================
:: CONFIGURAÇÕES (EDITE AQUI)
:: ================================

:: Caminho do MSYS2
set MSYS=C:\msys64

:: Caminho do seu projeto
set PROJ=C:\caminho\para\seu\projeto

:: Caminho do código fonte (relativo ao projeto)
set SRC=src/main.c

:: Nome do executável
set OUT=app.exe

:: ================================
:: BUILD
:: ================================

echo Compilando...

"%MSYS%\usr\bin\env.exe" MSYSTEM=MINGW64 "%MSYS%\usr\bin\bash.exe" -lc "cd $(cygpath '%PROJ%') && gcc %SRC% -o %OUT% $(pkg-config --cflags --libs gtk4)"

if errorlevel 1 (
    echo ❌ Erro na compilação
    pause
    exit /b
)

echo Copiando DLLs...

xcopy "%MSYS%\mingw64\bin\*.dll" "%PROJ%\" /Y >nul

echo.
echo ✔ Build concluído! %OUT% atualizado
pause
