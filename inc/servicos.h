#ifndef SERVICOS_H
#define SERVICOS_H
#include <mysql/mysql.h>

typedef struct {
    int servico_id;
    char tipo_servico[100];
    char descricao[200];
    float valor_diaria;
} Servicos;

int inserir_servicos(MYSQL *conn);
int atualizar_servicos(MYSQL *conn);
int deletar_servicos(MYSQL *conn);
int listar_servicos(MYSQL *conn, bool search_by_name);
float valor_diaria(MYSQL *conn, int servico_id);

#endif