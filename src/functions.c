#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <mysql/mysql.h>

void esperar_enter()
{
    int c;

    printf("\nPressione ENTER para voltar ao menu anterior...");

    while ((c = getchar()) != '\n' && c != EOF)
        ;
    getchar();
}

void menu(
    MYSQL *conn,
    char *plural,
    char *singular,
    int (*inserir)(MYSQL *conn),
    int (*listar)(MYSQL *conn, bool search_by_name),
    int (*atualizar)(MYSQL *conn),
    int (*deletar)(MYSQL *conn))
{
    int opcao;

    do
    {
        system("cls");

        printf("===== Editar %s =====\n", singular);
        printf("Escolha abaixo um número para a operação desejada:\n");
        printf("1 - Inserir %s\n", singular);
        printf("2 - Listar %s\n", plural);
        printf("3 - Pesquisar %s\n", plural);
        printf("4 - Atualizar %s\n", singular);
        printf("5 - Deletar %s\n", singular);
        printf("0 - Voltar Menu Principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        system("cls");

        switch (opcao)
        {
        case 1:
            inserir(conn);
            esperar_enter();
            break;

        case 2:
            listar(conn, false);
            esperar_enter();
            break;

        case 3:
            listar(conn, true);
            esperar_enter();
            break;

        case 4:
            atualizar(conn);
            esperar_enter();
            break;

        case 5:
            deletar(conn);
            esperar_enter();
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
}

int menu_editar(
    MYSQL *conn,
    char *plural,
    char *singular,
    char *campos[],
    int tamanho)
{
    int opcao;

    system("cls");

    printf("===== Editar %s =====\n", plural);
    printf("Escolha abaixo um número para a operação desejada:\n");

    for (int i = 0; i < tamanho; i++)
    {
        printf("%d - %s\n", i + 1, campos[i]);
    }

    printf("0 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    return opcao;
}

int menu_principal(
    MYSQL *conn,
    char *titulo,
    char *campos[],
    int tamanho)
{
    int opcao;

    system("cls");

    printf("===== %s =====\n", titulo);
    printf("Escolha abaixo um número para a operação desejada:\n");

    for (int i = 0; i < tamanho; i++)
    {
        printf("%d - %s\n", i + 1, campos[i]);
    }

    printf("0 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    return opcao;
}