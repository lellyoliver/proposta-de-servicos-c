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
        "Clientes",
        "Propostas"};

    int opcao;

    do
    {
        opcao = menu_principal(conn, "Menu Principal", opcoes, 2);

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
            // menu propostas depois
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
            esperar_enter();
            break;
        }

    } while (opcao != 0); // 🔥 volta pro menu principal

    mysql_close(conn);
    return 0;
}