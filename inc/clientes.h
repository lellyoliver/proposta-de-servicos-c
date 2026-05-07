#ifndef CLIENTES_H
#define CLIENTES_H
#include <mysql/mysql.h>

typedef struct
{
    int cliente_id;
    char name[100];
    char endereco[200];
    char telefone[20];
} Cliente;

int inserir_clientes(MYSQL *conn);
int atualizar_clientes(MYSQL *conn);
int deletar_clientes(MYSQL *conn);
int listar_clientes(MYSQL *conn, bool search_by_name);

#endif