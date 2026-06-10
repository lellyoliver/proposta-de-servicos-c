#include <stdlib.h>
#include <stdio.h>
#include <direct.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <string.h>
#include <mysql/mysql.h>
#include "propostas.h"
#include "servicos.h"
#include "functions.h"
#include "clientes.h"

int inserir_propostas(MYSQL *conn)
{
    Propostas p;
    float valor_total;
    char busca_cliente[100];
    char busca_servico[100];
    strcpy(p.status, "em aberto");

    printf("Buscar um cliente\n");
    listar_clientes(conn, busca_cliente);

    printf("\nDigite o Cliente ID: ");
    scanf("%d", &p.cliente_id);

    printf("Buscar um tipo de Servico\n");
    listar_servicos(conn, busca_servico);

    printf("Digite o Tipo de Servico ID: ");
    scanf("%d", &p.servico_id);

    printf("Descricao: ");
    scanf(" %[^\n]", p.descricao);

    p.valor_unitario = valor_diaria(conn, p.servico_id);

    if (p.valor_unitario <= 0)
    {
        printf("Valor da diária não encontrado.\n");
        return 0;
    }

    printf("Valor diária: R$ %.2f\n", p.valor_unitario);

    printf("Quantidade de dias: ");
    scanf("%d", &p.qnt_dias);

    printf("Data inicio YYYY-MM-DD: ");
    scanf(" %[^\n]", p.data_inicio);

    printf("Data final YYYY-MM-DD: ");
    scanf(" %[^\n]", p.data_final);

    valor_total = p.valor_unitario * p.qnt_dias;
    printf("Valor total: %.2f\n", valor_total);


    char query[512];

   snprintf(query, sizeof(query),
        "INSERT INTO propostas ("
        "cliente_id, "
        "servico_id, "
        "descricao, "
        "valor_unitario, "
        "status, "
        "qnt_dias, "
        "valor_total, "
        "data_inicio, "
        "data_final, "
        "data_proposta"
        ") VALUES (%d, %d, '%s', %.2f, '%s', %d, %.2f, '%s', '%s', NOW());",
        p.cliente_id,
        p.servico_id,
        p.descricao,
        p.valor_unitario,
        p.status,
        p.qnt_dias,
        valor_total,
        p.data_inicio,
        p.data_final
    );

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Erro: %s\n", mysql_error(conn));
        fprintf(stderr, "Query: %s\n", query);
        return 0;
    }
    printf("Proposta inserida com sucesso!\n");
    gerar_csv_proposta(p, valor_total);
    return 1;
}

int gerar_csv_proposta(Propostas p, float valor_total)
{
    FILE *arquivo;
    char nome_arquivo[300];

    time_t agora = time(NULL);
    struct tm *data = localtime(&agora);

    _mkdir("files");

    snprintf(nome_arquivo, sizeof(nome_arquivo),
             "files/proposta_%04d-%02d-%02d_%02d-%02d-%02d.csv",
             data->tm_year + 1900,
             data->tm_mon + 1,
             data->tm_mday,
             data->tm_hour,
             data->tm_min,
             data->tm_sec);

    arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL)
    {
        printf("Erro ao criar CSV.\n");
        return 0;
    }

    fprintf(arquivo, "cliente_id;servico_id;descricao;valor_unitario;status;qnt_dias;valor_total;data_inicio;data_final\n");

    fprintf(arquivo, "%d;%d;%s;%.2f;%s;%d;%.2f;%s;%s\n",
            p.cliente_id,
            p.servico_id,
            p.descricao,
            p.valor_unitario,
            p.status,
            p.qnt_dias,
            valor_total,
            p.data_inicio,
            p.data_final);

    fclose(arquivo);

    printf("CSV gerado com sucesso: %s\n", nome_arquivo);
    return 1;
}

int atualizar_propostas(MYSQL *conn)
{
    Propostas p;
    int id;
    char query[1024];
    float valor_total;

    listar_propostas(conn, false);

    printf("\nDigite o ID da proposta que deseja atualizar: ");
    scanf("%d", &id);

    char *campos[] = {
        "Cliente",
        "Servico",
        "Descricao",
        "Status",
        "Quantidade de dias",
        "Datas",
        "Todos"
    };

    int opcao = menu_editar(conn, "Propostas", "Proposta", campos, 7);

    if (opcao == 1)
    {
        listar_clientes(conn, false);

        printf("Cliente ID: ");
        scanf("%d", &p.cliente_id);

        snprintf(query, sizeof(query),
                 "UPDATE propostas SET cliente_id = %d WHERE proposta_id = %d;",
                 p.cliente_id, id);
    }
    else if (opcao == 2)
    {
        listar_servicos(conn, false);

        printf("Servico ID: ");
        scanf("%d", &p.servico_id);

        p.valor_unitario = valor_diaria(conn, p.servico_id);

        printf("Quantidade de dias: ");
        scanf("%d", &p.qnt_dias);

        valor_total = p.valor_unitario * p.qnt_dias;

        snprintf(query, sizeof(query),
                 "UPDATE propostas SET servico_id = %d, valor_unitario = %.2f, qnt_dias = %d, valor_total = %.2f WHERE proposta_id = %d;",
                 p.servico_id, p.valor_unitario, p.qnt_dias, valor_total, id);
    }
    else if (opcao == 3)
    {
        printf("Descricao: ");
        scanf(" %[^\n]", p.descricao);

        snprintf(query, sizeof(query),
                 "UPDATE propostas SET descricao = '%s' WHERE proposta_id = %d;",
                 p.descricao, id);
    }
    else if (opcao == 4)
    {
        printf("Status: ");
        scanf(" %[^\n]", p.status);

        snprintf(query, sizeof(query),
                 "UPDATE propostas SET status = '%s' WHERE proposta_id = %d;",
                 p.status, id);
    }
    else if (opcao == 5)
    {
        printf("Valor unitario atual/novo: ");
        scanf("%f", &p.valor_unitario);

        printf("Quantidade de dias: ");
        scanf("%d", &p.qnt_dias);

        valor_total = p.valor_unitario * p.qnt_dias;

        snprintf(query, sizeof(query),
                 "UPDATE propostas SET valor_unitario = %.2f, qnt_dias = %d, valor_total = %.2f WHERE proposta_id = %d;",
                 p.valor_unitario, p.qnt_dias, valor_total, id);
    }
    else if (opcao == 6)
    {
        printf("Data inicio YYYY-MM-DD: ");
        scanf(" %[^\n]", p.data_inicio);

        printf("Data final YYYY-MM-DD: ");
        scanf(" %[^\n]", p.data_final);

        snprintf(query, sizeof(query),
                 "UPDATE propostas SET data_inicio = '%s', data_final = '%s' WHERE proposta_id = %d;",
                 p.data_inicio, p.data_final, id);
    }
    else if (opcao == 7)
    {
        listar_clientes(conn, false);
        printf("Cliente ID: ");
        scanf("%d", &p.cliente_id);

        listar_servicos(conn, false);
        printf("Servico ID: ");
        scanf("%d", &p.servico_id);

        printf("Descricao: ");
        scanf(" %[^\n]", p.descricao);

        p.valor_unitario = valor_diaria(conn, p.servico_id);

        printf("Status: ");
        scanf(" %[^\n]", p.status);

        printf("Quantidade de dias: ");
        scanf("%d", &p.qnt_dias);

        printf("Data inicio YYYY-MM-DD: ");
        scanf(" %[^\n]", p.data_inicio);

        printf("Data final YYYY-MM-DD: ");
        scanf(" %[^\n]", p.data_final);

        valor_total = p.valor_unitario * p.qnt_dias;

        snprintf(query, sizeof(query),
                 "UPDATE propostas SET cliente_id = %d, servico_id = %d, descricao = '%s', valor_unitario = %.2f, status = '%s', qnt_dias = %d, valor_total = %.2f, data_inicio = '%s', data_final = '%s' WHERE proposta_id = %d;",
                 p.cliente_id,
                 p.servico_id,
                 p.descricao,
                 p.valor_unitario,
                 p.status,
                 p.qnt_dias,
                 valor_total,
                 p.data_inicio,
                 p.data_final,
                 id);
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

    printf("Proposta atualizada com sucesso!\n");
    return 1;
}

int deletar_propostas(MYSQL *conn)
{
    int id;
    char query[512];

    listar_propostas(conn, false);

    printf("\nDigite o ID da proposta que deseja deletar: ");
    scanf("%d", &id);

    snprintf(query, sizeof(query),
             "DELETE FROM propostas WHERE proposta_id = %d;",
             id);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Erro: %s\n", mysql_error(conn));
        fprintf(stderr, "Query: %s\n", query);
        return 0;
    }

    printf("Proposta deletada com sucesso!\n");
    return 1;
}

int listar_propostas(MYSQL *conn, bool search_by_name)
{
    char query[1500];
    char busca[100];

    if (!search_by_name)
    {
        snprintf(query, sizeof(query),
            "SELECT "
            "p.proposta_id, "
            "c.nome, "
            "s.tipo_servico, "
            "p.descricao, "
            "p.valor_unitario, "
            "p.qnt_dias, "
            "p.valor_total, "
            "p.status, "
            "p.data_inicio, "
            "p.data_final, "
            "p.data_proposta "
            "FROM propostas p "
            "INNER JOIN clientes c ON p.cliente_id = c.cliente_id "
            "INNER JOIN servicos s ON p.servico_id = s.servico_id "
            "ORDER BY p.proposta_id DESC;");
    }
    else
    {
        printf("Buscar proposta: ");
        scanf(" %[^\n]", busca);

       snprintf(query, sizeof(query),
        "SELECT "
        "p.proposta_id, "
        "c.nome, "
        "s.tipo_servico, "
        "p.descricao, "
        "p.valor_unitario, "
        "p.qnt_dias, "
        "p.valor_total, "
        "p.status, "
        "p.data_inicio, "
        "p.data_final, "
        "p.data_proposta "
        "FROM propostas p "
        "INNER JOIN clientes c ON p.cliente_id = c.cliente_id "
        "INNER JOIN servicos s ON p.servico_id = s.servico_id "
        "WHERE c.nome LIKE '%%%s%%' "
        "OR s.tipo_servico LIKE '%%%s%%' "
        "OR CAST(p.proposta_id AS CHAR) LIKE '%%%s%%' "
        "OR p.descricao LIKE '%%%s%%' "
        "OR p.status LIKE '%%%s%%' "
        "ORDER BY p.proposta_id DESC "
        "LIMIT 10;",
        busca,
        busca,
        busca,
        busca,
        busca
    );
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

    printf("\n| %-5s | %-20s | %-20s | %-25s | %-10s | %-5s | %-12s | %-12s |\n",
           "ID", "Cliente", "Serviço", "Descrição", "Diária", "Dias", "Total", "Status");

    printf("|-------|----------------------|----------------------|---------------------------|------------|-------|--------------|--------------|\n");

    while ((row = mysql_fetch_row(result)))
    {
        printf("| %-5s | %-20s | %-20s | %-25s | R$ %-7s | %-5s | R$ %-9s | %-12s |\n",
               row[0] ? row[0] : "",
               row[1] ? row[1] : "",
               row[2] ? row[2] : "",
               row[3] ? row[3] : "",
               row[4] ? row[4] : "0.00",
               row[5] ? row[5] : "0",
               row[6] ? row[6] : "0.00",
               row[7] ? row[7] : "");
    }

    mysql_free_result(result);

    return 1;
}