# proposta-de-servicos-c

Guia completo para configurar ambiente em C com GTK4 no Windows utilizando MSYS2.

## Instalação do GTK4 no Windows (MSYS2)

### 1. Instalar o MSYS2

Baixe o instalador oficial:

Download: [https://github.com/msys2/msys2-installer/releases/download/2026-03-22/msys2-x86_64-20260322.exe](https://github.com/msys2/msys2-installer/releases/download/2026-03-22/msys2-x86_64-20260322.exe)

Instale no caminho padrão:

```
C:\msys64
```

---

### Ajuste necessário (caso falte mirrorlist)

Verifique se o arquivo abaixo existe:

```
C:\msys64\etc\pacman.d\mirrorlist.mingw64
```

Caso não exista:

1. Abra o terminal:

```
MSYS2 MinGW64
```

2. Execute:

```bash
cp /etc/pacman.d/mirrorlist.mingw /etc/pacman.d/mirrorlist.mingw64
```

3. Confirme se o arquivo foi criado corretamente em:

```
C:\msys64\etc\pacman.d
```

---

## 2. Atualizar o MSYS2 (obrigatório)

### Primeira atualização

Abra:

```
MSYS2 MSYS
```

Execute:

```bash
pacman -Syu
```

Se o terminal solicitar, feche após a conclusão.

---

### Segunda atualização

Abra novamente:

```
MSYS2 MSYS
```

Execute:

```bash
pacman -Su
```

---

## 3. Instalar GTK4 e ferramentas

Abra o terminal:

```
MSYS2 MinGW64
```

Execute:

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gtk4 mingw-w64-x86_64-pkgconf
```

---

## 4. Validar instalação

Execute os comandos abaixo:

```bash
gcc --version
pkg-config --version
pkg-config --cflags gtk4
```

Se os comandos retornarem informações sem erro, o ambiente está configurado corretamente.
