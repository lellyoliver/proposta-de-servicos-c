#ifndef PROPOSTAS_H
#define PROPOSTAS_H
#include <mysql/mysql.h>

typedef struct {
    int cliente_id;
    int servico_id;
    char descricao[200];
    float valor_unitario;
    char status[50];
    int qnt_dias;
    char data_inicio[20];
    char data_final[20];
} Propostas;

int inserir_propostas(MYSQL *conn);
int atualizar_propostas(MYSQL *conn);
int deletar_propostas(MYSQL *conn);
int listar_propostas(MYSQL *conn, bool search_by_name);
int gerar_csv_proposta(Propostas p, float valor_total);

#endif