#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "servicos.h"
#include "functions.h"

int inserir_servicos(MYSQL *conn)
{
    Servicos s;

    printf("Tipo de serviço (ex.: Limpeza de Piscina): ");
    scanf(" %[^\n]", s.tipo_servico);

    printf("Descricao: ");
    scanf(" %[^\n]", s.descricao);

    printf("Valor diária: ");
    scanf("%f", &s.valor_diaria);

    char query[512];

    snprintf(query, sizeof(query),
             "INSERT INTO servicos (tipo_servico, descricao, valor_diaria) "
             "VALUES ('%s', '%s', %.2f);",
             s.tipo_servico,
             s.descricao,
             s.valor_diaria);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Erro: %s\n", mysql_error(conn));
        fprintf(stderr, "Query: %s\n", query);
        return 0;
    }

    printf("Serviço inserido com sucesso!\n");
    return 1;
}

int atualizar_servicos(MYSQL *conn)
{
    Servicos s;
    int id;
    char query[700];

    listar_servicos(conn, false);

    printf("\nDigite o ID do serviço que deseja atualizar: ");
    scanf("%d", &id);

    char *campos[] = {
        "Tipo do serviço",
        "Descrição",
        "Valor diária",
        "Todos"
    };

    int opcao = menu_editar(conn, "Serviços", "Serviço", campos, 4);

    if (opcao == 1)
    {
        printf("Tipo do serviço: ");
        scanf(" %[^\n]", s.tipo_servico);

        snprintf(query, sizeof(query),
                 "UPDATE servicos SET tipo_servico = '%s' WHERE servico_id = %d;",
                 s.tipo_servico, id);
    }
    else if (opcao == 2)
    {
        printf("Descrição: ");
        scanf(" %[^\n]", s.descricao);

        snprintf(query, sizeof(query),
                 "UPDATE servicos SET descricao = '%s' WHERE servico_id = %d;",
                 s.descricao, id);
    }
    else if (opcao == 3)
    {
        printf("Valor diária: ");
        scanf("%f", &s.valor_diaria);

        snprintf(query, sizeof(query),
                 "UPDATE servicos SET valor_diaria = %.2f WHERE servico_id = %d;",
                 s.valor_diaria, id);
    }
    else if (opcao == 4)
    {
        printf("Tipo do serviço: ");
        scanf(" %[^\n]", s.tipo_servico);

        printf("Descrição: ");
        scanf(" %[^\n]", s.descricao);

        printf("Valor diária: ");
        scanf("%f", &s.valor_diaria);

        snprintf(query, sizeof(query),
                 "UPDATE servicos SET tipo_servico = '%s', descricao = '%s', valor_diaria = %.2f WHERE servico_id = %d;",
                 s.tipo_servico,
                 s.descricao,
                 s.valor_diaria,
                 id);
    }
    else
    {
        printf("Opção inválida ou cancelada.\n");
        return 0;
    }

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Erro: %s\n", mysql_error(conn));
        fprintf(stderr, "Query: %s\n", query);
        return 0;
    }

    printf("Serviço atualizado com sucesso!\n");
    return 1;
}

int deletar_servicos(MYSQL *conn)
{
    Servicos s;
    int id;
    char query[512];

    listar_servicos(conn, false);

    printf("\nDigite o ID do serviço que deseja deletar: ");
    scanf("%d", &id);

    // Montar a query para deletar o cliente
    snprintf(query, sizeof(query),
             "DELETE FROM servicos WHERE servico_id = %d;", id);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Erro: %s\n", mysql_error(conn));
        fprintf(stderr, "Query: %s\n", query);
        return 0;
    }

    printf("Serviço deletado com sucesso!\n");
    return 1;
}

int listar_servicos(MYSQL *conn, bool search_by_name)
{
    char query[512];
    char busca[100];

    if (!search_by_name)
    {
        snprintf(query, sizeof(query),
                 "SELECT servico_id, tipo_servico, descricao, valor_diaria "
                 "FROM servicos "
                 "ORDER BY tipo_servico ASC;");
    }
    else
    {
        printf("Buscar serviço: ");
        scanf(" %[^\n]", busca);

        snprintf(query, sizeof(query),
                 "SELECT servico_id, tipo_servico, descricao, valor_diaria "
                 "FROM servicos "
                 "WHERE tipo_servico LIKE '%%%s%%' "
                 "OR descricao LIKE '%%%s%%' "
                 "OR CAST(valor_diaria AS CHAR) LIKE '%%%s%%' "
                 "ORDER BY tipo_servico ASC "
                 "LIMIT 10;",
                 busca,
                 busca,
                 busca);
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

    printf("\n| %-5s | %-25s | %-35s | %-15s |\n",
           "ID", "Tipo de Serviço", "Descrição", "Valor diária");

    printf("|-------|---------------------------|-------------------------------------|-----------------|\n");

    while ((row = mysql_fetch_row(result)))
    {
        int id = atoi(row[0]);

        printf("| %-5d | %-25s | %-35s | R$ %-12s |\n",
               id,
               row[1] ? row[1] : "",
               row[2] ? row[2] : "",
               row[3] ? row[3] : "0.00");
    }

    mysql_free_result(result);

    return 1;
}

float valor_diaria(MYSQL *conn, int servico_id)
{
    char query[256];

    snprintf(query, sizeof(query),
             "SELECT valor_diaria "
             "FROM servicos "
             "WHERE servico_id = %d "
             "LIMIT 1;",
             servico_id);

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

    MYSQL_ROW row = mysql_fetch_row(result);

    if (row == NULL)
    {
        printf("Serviço não encontrado.\n");
        mysql_free_result(result);
        return 0;
    }

    float valor_diaria = atof(row[0]);

    mysql_free_result(result);

    return valor_diaria;
}