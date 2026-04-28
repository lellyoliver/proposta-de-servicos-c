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

---

## Rodando a build

### 1. Clonar o repositório

No terminal, execute:

```bash
git clone https://github.com/lellyoliver/proposta-de-servicos-c.git
```

### 2. Acessar a pasta do projeto

```bash
cd proposta-de-servicos-c
```

### 3. Executar a build

Execute o arquivo `build.bat` para compilar o projeto e copiar as dependências necessárias do GTK:

```bash
build.bat
```

### 4. Executar o aplicativo

Após a build, execute:

```bash
app.exe
```

Isso irá iniciar o aplicativo com todas as dependências corretamente configuradas.

# MYSQL (C) + MariaDB/phpMyAdmin com Docker

## Pré-requisitos

- MSYS2 instalado
- Docker Desktop em execução

## Instalação do cliente MariaDB no MSYS2

Abra o terminal:

```bash
MSYS2 MinGW64
```

Instale a biblioteca cliente MariaDB para C:

```bash
pacman -S mingw-w64-x86_64-libmariadbclient
```

Para validar a instalação, rode:

```bash
pacman -Ss mariadb
```

Deve aparecer algo semelhante a:

```bash
clangarm64/mingw-w64-clang-aarch64-libmariadbclient 3.4.8-1
    MariaDB client libraries (mingw-w64)

mingw64/mingw-w64-x86_64-libmariadbclient 3.4.8-1 [installed]
    MariaDB client libraries (mingw-w64)

ucrt64/mingw-w64-ucrt-x86_64-libmariadbclient 3.4.8-1
    MariaDB client libraries (mingw-w64)

clang64/mingw-w64-clang-x86_64-libmariadbclient 3.4.8-1
    MariaDB client libraries (mingw-w64)
```

Se aparecer `[installed]`, a biblioteca está pronta para uso.

---

## Subindo o banco com Docker

O projeto possui um arquivo:

```bash
docker-compose.yml
```

Para iniciar os containers:

```bash
docker compose up -d
```

Isso irá subir:

- MariaDB
- phpMyAdmin

Para parar e remover os containers:

```bash
docker compose down
```

---

## Executando a aplicação em C

Com o Docker rodando e o banco ativo, execute o `build.bat` do projeto.

Ao rodar a aplicação corretamente, o retorno esperado será:

```bash
Conectado!
OK
Pressione Enter para sair...
```

Isso indica que:

- A aplicação em C conectou no MariaDB
- O container está respondendo corretamente
- O ambiente está configurado com sucesso

---

## Acesso ao phpMyAdmin (painel para consulta SQL)

Após subir os containers, acesse no navegador:

```bash
http://localhost:8083/
```

Use as credenciais definidas no `docker-compose.yml`.
