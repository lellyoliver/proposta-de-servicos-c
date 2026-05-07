#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <mysql/mysql.h>

void menu(
    MYSQL *conn,
    char *plural,
    char *singular,
    int (*inserir)(MYSQL *conn),
    int (*listar)(MYSQL *conn, bool search_by_name),
    int (*atualizar)(MYSQL *conn),
    int (*deletar)(MYSQL *conn)
);
int menu_editar(
    MYSQL *conn, 
    char *plural, 
    char *singular, 
    char *campos[], 
    int tamanho
);

int menu_principal(
    MYSQL *conn, 
    char *titulo, 
    char *campos[], 
    int tamanho
);

void esperar_enter();
#endif