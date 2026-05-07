#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "clientes.h"
#include "functions.h"

int inserir_clientes(MYSQL *conn)
{
    Cliente c;

    printf("Nome: ");
    scanf(" %[^\n]", c.name);

    printf("Endereco: ");
    scanf(" %[^\n]", c.endereco);

    printf("Telefone: ");
    scanf(" %[^\n]", c.telefone);

    char query[512];

    snprintf(query, sizeof(query),
             "INSERT INTO clientes (nome, endereco, telefone) "
             "VALUES ('%s', '%s', '%s');",
             c.name, c.endereco, c.telefone);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Erro: %s\n", mysql_error(conn));
        fprintf(stderr, "Query: %s\n", query);
        return 0;
    }
    printf("Cliente inserido com sucesso!\n");
    return 1;
}

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
        scanf(" %[^\n]", c.name);

        snprintf(query, sizeof(query),
                 "UPDATE clientes SET nome = '%s' WHERE id = %d;",
                 c.name, id);
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
        scanf(" %[^\n]", c.name);

        printf("Endereco: ");
        scanf(" %[^\n]", c.endereco);

        printf("Telefone: ");
        scanf(" %[^\n]", c.telefone);

        snprintf(query, sizeof(query),
                 "UPDATE clientes SET nome = '%s', endereco = '%s', telefone = '%s' WHERE id = %d;",
                 c.name, c.endereco, c.telefone, id);
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

int deletar_clientes(MYSQL *conn)
{
    Cliente c;
    int id;
    char query[512];

    listar_clientes(conn, false);

    printf("\nDigite o ID do cliente que deseja deletar: ");
    scanf("%d", &id);

    // Montar a query para deletar o cliente
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
        scanf(" %[^\n]", c.name);

        snprintf(query, sizeof(query),
                 "SELECT id, nome, endereco, telefone FROM clientes "
                 "WHERE nome LIKE '%%%s%%';",
                 c.name);
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