#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <mysql/mysql.h>
#include "bd.h"
#include "clientes.h"
#include "propostas.h"
#include "servicos.h"
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
        "Clientes",
        "Propostas",
        "Servicos",
    };

    int opcao;

    do
    {
        opcao = menu_principal(conn, "Menu Principal", opcoes, 3); //3 é a quantidsade de opções

        switch (opcao)
        {
        case 1:
            menu(conn, "Clientes", "Cliente",
                 inserir_clientes,
                 listar_clientes,
                 atualizar_clientes,
                 deletar_clientes);
            break;

        case 2:
            menu(conn, "Propostas", "Proposta",
                 inserir_propostas, 
                 listar_propostas,
                 atualizar_propostas,
                 deletar_propostas);
            break;

        case 3:
            menu(conn, "Servicos", "Servico",
                 inserir_servicos, 
                 listar_servicos,
                 atualizar_servicos,
                 deletar_servicos);
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