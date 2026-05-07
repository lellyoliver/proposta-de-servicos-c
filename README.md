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


Claro — abaixo está a documentação ajustada e mais explicativa, baseada no texto enviado. 

---

# Organização de Pastas e Arquivos em C

Esta documentação explica como organizar os arquivos do projeto em linguagem C, separando corretamente os arquivos `.c`, `.h`, pastas do projeto e funções reutilizáveis.

O objetivo é deixar o projeto mais organizado, mais fácil de entender e mais simples de manter.

---

## 1. O que são arquivos `.c` e `.h`

Em projetos escritos em C, é comum separar o código em dois tipos principais de arquivos:

* arquivos `.c`
* arquivos `.h`

Cada um tem uma função diferente dentro do projeto.

---

## 2. Arquivos `.c`

Os arquivos com extensão `.c` são os arquivos de implementação.

Isso significa que é dentro deles que escrevemos:

* a lógica do programa;
* as funções completas;
* as regras de negócio;
* os comandos que serão executados;
* as consultas SQL;
* os cálculos;
* as ações de inserir, listar, atualizar e deletar dados.

Exemplo:

```c
clientes.c
```

Esse arquivo será responsável por executar as funções relacionadas aos clientes.

Por exemplo:

* inserir cliente;
* listar clientes;
* atualizar cliente;
* deletar cliente.

No projeto, os arquivos `.c` devem ficar dentro da pasta:

```text
/src/
```

Exemplo:

```text
/src/clientes.c
```

---

## 3. Arquivos `.h`

Os arquivos com extensão `.h` são chamados de arquivos de cabeçalho.

Eles funcionam como uma “interface” do arquivo `.c`.

Ou seja, no arquivo `.h` nós não escrevemos a função completa.
Nós apenas declaramos que aquela função existe.

Isso permite que outros arquivos do projeto consigam usar essas funções.

Exemplo:

```c
clientes.h
```

Esse arquivo informa ao restante do projeto que existem funções relacionadas a clientes.

Por exemplo:

```c
int inserir_clientes(MYSQL *conn);
int atualizar_clientes(MYSQL *conn);
int deletar_clientes(MYSQL *conn);
int listar_clientes(MYSQL *conn, bool search_by_name);
```

No projeto, os arquivos `.h` devem ficar dentro da pasta:

```text
/inc/
```

Exemplo:

```text
/inc/clientes.h
```

---

## 4. Resumo rápido

```text
.c  = onde a função é criada de verdade
.h  = onde a função é declarada para poder ser usada em outros arquivos
```

Exemplo:

```text
clientes.h → avisa que a função existe
clientes.c → contém o código completo da função
main.c     → chama a função quando o usuário escolher uma opção no menu
```

---

## 5. Estrutura de pastas do projeto

A organização do projeto deve seguir este modelo:

```text
projeto/
├── bin/                
├── certs/              
├── documentacao/       
├── inc/                
├── src/                
├── lib/                
├── docker-compose.yml  
├── build.bat           
└── README.md           
```

---

## 6. Explicação de cada pasta

### `/bin/`

Essa pasta guarda arquivos gerados ou necessários para executar o programa.

Normalmente pode conter:

* arquivos `.exe`;
* arquivos `.dll`;
* arquivos necessários do GTK.

Exemplo:

```text
/bin/app.exe
```

---

### `/certs/`

Essa pasta pode ser usada para armazenar certificados, caso o banco de dados precise de SSL.

Exemplo:

```text
/certs/certificado.pem
```

---

### `/documentacao/`

Essa pasta é usada para guardar arquivos explicativos do projeto.

Exemplo:

```text
/documentacao/organizacao-de-pastas.md
```

---

### `/inc/`

Essa pasta guarda os arquivos `.h`.

Exemplo:

```text
/inc/clientes.h
/inc/bd.h
/inc/functions.h
```

---

### `/src/`

Essa pasta guarda os arquivos `.c`.

Exemplo:

```text
/src/main.c
/src/clientes.c
/src/bd.c
/src/functions.c
```

---

### `/lib/`

Essa pasta pode ser usada para bibliotecas externas, caso o projeto utilize alguma biblioteca adicional.

---

### `docker-compose.yml`

Esse arquivo serve para subir o banco de dados usando Docker.

Exemplo:

* MariaDB;
* MySQL;
* phpMyAdmin.

---

### `build.bat`

Esse arquivo automatiza a compilação do projeto.

Sempre que você alterar algum arquivo `.c` ou `.h`, será necessário rodar novamente o `build.bat`.

Isso é importante porque o código C precisa ser compilado novamente para gerar o executável atualizado.

---

### `README.md`

Esse arquivo é a documentação principal do projeto no GitHub.

Normalmente ele explica:

* como instalar;
* como configurar;
* como rodar o projeto;
* como compilar;
* quais ferramentas são necessárias.

---

## 7. Importante: sempre rodar o `build.bat`

Depois de alterar qualquer arquivo do projeto, principalmente arquivos dentro de:

```text
/src/
```

ou

```text
/inc/
```

você precisa executar novamente o arquivo:

```text
build.bat
```

Isso recompila o projeto e gera uma versão atualizada do programa.

Se você alterar o código e não rodar o `build.bat`, o programa pode continuar abrindo a versão antiga.

---

# Criando uma nova entidade no projeto

Neste exemplo, vamos usar a entidade:

```text
Clientes
```

A ideia é criar dois arquivos:

```text
clientes.h
clientes.c
```

---

## 8. Criando o arquivo `clientes.h`

O arquivo `clientes.h` deve ser criado dentro da pasta:

```text
/inc/
```

Caminho completo:

```text
/inc/clientes.h
```

Esse arquivo será responsável por declarar:

* a estrutura `Cliente`;
* as funções de clientes.

---

## 9. Exemplo de `clientes.h`

```c
#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdbool.h>
#include <mysql/mysql.h>

/*
    Estrutura Cliente

    Essa estrutura agrupa todas as informações de um cliente
    em uma única variável.

    Campos:
    - id: código do cliente no banco de dados
    - nome: nome do cliente
    - endereco: endereço do cliente
    - telefone: telefone do cliente
*/
typedef struct
{
    int id;
    char nome[100];
    char endereco[200];
    char telefone[20];
} Cliente;

/*
    Declaração das funções de clientes.

    Essas funções serão implementadas no arquivo clientes.c.
*/

int inserir_clientes(MYSQL *conn);

int atualizar_clientes(MYSQL *conn);

int deletar_clientes(MYSQL *conn);

int listar_clientes(MYSQL *conn, bool search_by_name);

#endif
```

---

## 10. O que significa `#ifndef`, `#define` e `#endif`

Esse trecho:

```c
#ifndef CLIENTES_H
#define CLIENTES_H
...
#endif
```

serve para evitar que o mesmo arquivo `.h` seja incluído mais de uma vez durante a compilação.

Isso evita erros como:

```text
redefinition of struct
```

ou

```text
function already declared
```

Sempre que criar um arquivo `.h`, use esse padrão.

Exemplo para um arquivo chamado `propostas.h`:

```c
#ifndef PROPOSTAS_H
#define PROPOSTAS_H

// conteúdo do arquivo

#endif
```

---

## 11. Criando o arquivo `clientes.c`

O arquivo `clientes.c` deve ser criado dentro da pasta:

```text
/src/
```

Caminho completo:

```text
/src/clientes.c
```

Esse arquivo terá o código completo das funções.

---

## 12. Exemplo de início do `clientes.c`

```c
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <mysql/mysql.h>

#include "clientes.h"
#include "functions.h"
```

---

## 13. Explicação dos includes

```c
#include <stdlib.h>
```

Usado para funções padrão da linguagem C, como conversão de texto para número.

---

```c
#include <stdio.h>
```

Usado para entrada e saída de dados.

Exemplo:

```c
printf("Mensagem");
scanf("%d", &id);
```

---

```c
#include <conio.h>
```

Pode ser usado para funções de controle do console.

---

```c
#include <string.h>
```

Usado para manipulação de textos.

---

```c
#include <mysql/mysql.h>
```

Usado para conexão e execução de comandos no banco MySQL/MariaDB.

---

```c
#include "clientes.h"
```

Inclui o arquivo de cabeçalho dos clientes.

---

```c
#include "functions.h"
```

Inclui funções auxiliares reutilizáveis do projeto, como menus e pausas.

---

# Função de inserir clientes

A função abaixo insere um novo cliente no banco de dados.

```c
int inserir_clientes(MYSQL *conn)
{
    Cliente c;

    printf("Nome: ");
    scanf(" %[^\n]", c.nome);

    printf("Endereco: ");
    scanf(" %[^\n]", c.endereco);

    printf("Telefone: ");
    scanf(" %[^\n]", c.telefone);

    char query[512];

    snprintf(query, sizeof(query),
             "INSERT INTO clientes (nome, endereco, telefone) "
             "VALUES ('%s', '%s', '%s');",
             c.nome, c.endereco, c.telefone);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Erro: %s\n", mysql_error(conn));
        fprintf(stderr, "Query: %s\n", query);
        return 0;
    }

    printf("Cliente inserido com sucesso!\n");
    return 1;
}
```

---

## 14. Explicação da função inserir

```c
Cliente c;
```

Cria uma variável chamada `c` do tipo `Cliente`.

Ela vai guardar temporariamente os dados digitados pelo usuário.

---

```c
scanf(" %[^\n]", c.nome);
```

Lê o texto digitado pelo usuário até ele apertar Enter.

Esse formato permite ler textos com espaço.

Exemplo:

```text
Maria da Silva
```

---

```c
char query[512];
```

Cria uma variável para armazenar o comando SQL.

---

```c
snprintf(query, sizeof(query), ...);
```

Monta o comando SQL com segurança, limitando o tamanho máximo da string.

---

```c
mysql_query(conn, query)
```

Executa o comando SQL no banco de dados.

---

# Função de listar clientes

Essa função lista os clientes cadastrados.

```c
int listar_clientes(MYSQL *conn, bool search_by_name)
{
    Cliente c;
    char query[512];

    if (!search_by_name)
    {
        snprintf(query, sizeof(query),
                 "SELECT id, nome, endereco, telefone FROM clientes;");
    }
    else
    {
        printf("Nome: ");
        scanf(" %[^\n]", c.nome);

        snprintf(query, sizeof(query),
                 "SELECT id, nome, endereco, telefone FROM clientes "
                 "WHERE nome LIKE '%%%s%%';",
                 c.nome);
    }

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Erro: %s\n", mysql_error(conn));
        fprintf(stderr, "Query: %s\n", query);
        return 0;
    }

    MYSQL_RES *result = mysql_store_result(conn);

    if (result == NULL)
    {
        fprintf(stderr, "Erro ao armazenar resultado: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_ROW row;

    printf("| %-5s | %-20s | %-30s | %-15s |\n",
           "ID", "Nome", "Endereco", "Telefone");

    while ((row = mysql_fetch_row(result)))
    {
        int id = atoi(row[0]);

        printf("| %-5d | %-20s | %-30s | %-15s |\n",
               id,
               row[1] ? row[1] : "",
               row[2] ? row[2] : "",
               row[3] ? row[3] : "");
    }

    mysql_free_result(result);

    return 1;
}
```

---

## 15. Explicação da listagem

```c
bool search_by_name
```

Esse parâmetro define se a listagem será completa ou filtrada por nome.

Se for `false`, lista todos os clientes.

Se for `true`, pergunta um nome e busca clientes parecidos.

---

```sql
SELECT id, nome, endereco, telefone FROM clientes;
```

Busca todos os clientes da tabela.

---

```sql
WHERE nome LIKE '%texto%'
```

Busca clientes cujo nome contenha o texto digitado.

---

```c
MYSQL_RES *result = mysql_store_result(conn);
```

Armazena o resultado retornado pelo banco.

---

```c
MYSQL_ROW row;
```

Representa uma linha do resultado.

---

```c
while ((row = mysql_fetch_row(result)))
```

Percorre cada linha retornada pelo banco.

---

```c
mysql_free_result(result);
```

Libera a memória usada pelo resultado.

Isso é importante para evitar consumo desnecessário de memória.

---

# Função de atualizar clientes

```c
int atualizar_clientes(MYSQL *conn)
{
    Cliente c;
    int id;
    char query[512];

    listar_clientes(conn, false);

    printf("\nDigite o ID do cliente que deseja atualizar: ");
    scanf("%d", &id);

    char *campos[] = {"Nome", "Endereco", "Telefone", "Todos"};
    int opcao = menu_editar(conn, "Clientes", "Cliente", campos, 4);

    if (opcao == 1)
    {
        printf("Nome: ");
        scanf(" %[^\n]", c.nome);

        snprintf(query, sizeof(query),
                 "UPDATE clientes SET nome = '%s' WHERE id = %d;",
                 c.nome, id);
    }
    else if (opcao == 2)
    {
        printf("Endereco: ");
        scanf(" %[^\n]", c.endereco);

        snprintf(query, sizeof(query),
                 "UPDATE clientes SET endereco = '%s' WHERE id = %d;",
                 c.endereco, id);
    }
    else if (opcao == 3)
    {
        printf("Telefone: ");
        scanf(" %[^\n]", c.telefone);

        snprintf(query, sizeof(query),
                 "UPDATE clientes SET telefone = '%s' WHERE id = %d;",
                 c.telefone, id);
    }
    else if (opcao == 4)
    {
        printf("Nome: ");
        scanf(" %[^\n]", c.nome);

        printf("Endereco: ");
        scanf(" %[^\n]", c.endereco);

        printf("Telefone: ");
        scanf(" %[^\n]", c.telefone);

        snprintf(query, sizeof(query),
                 "UPDATE clientes SET nome = '%s', endereco = '%s', telefone = '%s' WHERE id = %d;",
                 c.nome, c.endereco, c.telefone, id);
    }
    else
    {
        printf("Opcao invalida ou cancelada.\n");
        return 0;
    }

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Erro: %s\n", mysql_error(conn));
        fprintf(stderr, "Query: %s\n", query);
        return 0;
    }

    printf("Cliente atualizado com sucesso!\n");
    return 1;
}
```

---

## 16. Explicação da atualização

Primeiro a função lista todos os clientes:

```c
listar_clientes(conn, false);
```

Depois o usuário escolhe o ID do cliente que deseja editar:

```c
scanf("%d", &id);
```

Em seguida, aparece um menu perguntando qual campo será alterado:

```c
Nome
Endereco
Telefone
Todos
```

Dependendo da opção escolhida, a função monta um comando SQL diferente.

Exemplo:

```sql
UPDATE clientes SET nome = 'Maria' WHERE id = 1;
```

---

# Função de deletar clientes

```c
int deletar_clientes(MYSQL *conn)
{
    int id;
    char query[512];

    listar_clientes(conn, false);

    printf("\nDigite o ID do cliente que deseja deletar: ");
    scanf("%d", &id);

    snprintf(query, sizeof(query),
             "DELETE FROM clientes WHERE id = %d;", id);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Erro: %s\n", mysql_error(conn));
        fprintf(stderr, "Query: %s\n", query);
        return 0;
    }

    printf("Cliente deletado com sucesso!\n");
    return 1;
}
```

---

## 17. Explicação da exclusão

A função primeiro mostra os clientes cadastrados.

Depois o usuário informa o ID do cliente que deseja excluir.

Exemplo de SQL gerado:

```sql
DELETE FROM clientes WHERE id = 1;
```

Atenção: essa ação remove o registro do banco.

---

# Ligando os arquivos no `main.c`

Depois de criar:

```text
/inc/clientes.h
/src/clientes.c
```

é necessário chamar o arquivo `.h` no `main.c`.

Abra:

```text
/src/main.c
```

E adicione:

```c
#include "clientes.h"
```

Exemplo:

```c
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <mysql/mysql.h>

#include "bd.h"
#include "clientes.h"
#include "functions.h"
```

---

## 18. Exemplo de `main.c`

```c
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <mysql/mysql.h>

#include "bd.h"
#include "clientes.h"
#include "functions.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    MYSQL *conn = conectar_bd();

    if (conn == NULL)
    {
        printf("Erro ao conectar\n");
        return 1;
    }

    char *opcoes[] = {
        "Clientes"
    };

    int opcao;

    do
    {
        opcao = menu_principal(conn, "Menu Principal", opcoes, 1);

        switch (opcao)
        {
        case 1:
            menu(conn, "Clientes", "Cliente",
                 inserir_clientes,
                 listar_clientes,
                 atualizar_clientes,
                 deletar_clientes);
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
            esperar_enter();
            break;
        }

    } while (opcao != 0);

    mysql_close(conn);

    return 0;
}
```

---

## 19. Atenção ao número de opções do menu

Se você tiver apenas uma opção:

```c
char *opcoes[] = {
    "Clientes"
};
```

Então o menu deve receber `1`:

```c
menu_principal(conn, "Menu Principal", opcoes, 1);
```

Se futuramente adicionar outra opção:

```c
char *opcoes[] = {
    "Clientes",
    "Propostas"
};
```

Então altere para `2`:

```c
menu_principal(conn, "Menu Principal", opcoes, 2);
```

---

# Adicionando uma nova entidade

Se quiser criar uma nova área, como `Propostas`, siga o mesmo padrão.

Você deverá criar:

```text
/inc/propostas.h
/src/propostas.c
```

Depois adicionar no `main.c`:

```c
#include "propostas.h"
```

E atualizar o menu:

```c
char *opcoes[] = {
    "Clientes",
    "Propostas"
};
```

Também será necessário criar as funções:

```c
inserir_propostas
listar_propostas
atualizar_propostas
deletar_propostas
```

---

# Checklist final

Sempre que criar uma nova entidade, conferir:

```text
1. Criou o arquivo .h dentro de /inc/
2. Criou o arquivo .c dentro de /src/
3. Declarou as funções no arquivo .h
4. Implementou as funções no arquivo .c
5. Incluiu o .h no main.c
6. Adicionou a opção no menu principal
7. Chamou a função menu() com inserir, listar, atualizar e deletar
8. Rodou o build.bat novamente
9. Testou o executável atualizado
```

---

# Observação importante sobre segurança

Os exemplos atuais montam comandos SQL usando `snprintf`.

Isso funciona para fins de estudo, mas em sistemas reais o ideal é usar prepared statements para evitar SQL Injection.

Como este projeto tem objetivo acadêmico e de aprendizado, o modelo atual pode ser usado, mas é importante saber que existe uma forma mais segura para projetos profissionais.

---

# Conclusão

A separação entre arquivos `.h` e `.c` ajuda a deixar o projeto mais limpo, organizado e fácil de manter.

A lógica principal é:

```text
.h  → declara o que existe
.c  → executa o que foi declarado
main.c → chama as funções no fluxo principal do programa
```

Sempre que alterar o código, execute novamente:

```text
build.bat
```

Assim o projeto será recompilado e o programa será atualizado.
