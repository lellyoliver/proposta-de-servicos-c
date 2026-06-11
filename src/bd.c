#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

int criar_tabelas(MYSQL *conn)
{
    const char *clientes =
        "CREATE TABLE IF NOT EXISTS clientes ("
        "cliente_id INT AUTO_INCREMENT PRIMARY KEY,"
        "nome VARCHAR(100) NOT NULL,"
        "endereco VARCHAR(200),"
        "telefone VARCHAR(20),"
        "criado_em DATETIME DEFAULT CURRENT_TIMESTAMP"
        ") ENGINE=InnoDB;";

    const char *servicos =
        "CREATE TABLE IF NOT EXISTS servicos ("
        "servico_id INT AUTO_INCREMENT PRIMARY KEY,"
        "tipo_servico VARCHAR(100) NOT NULL,"
        "descricao VARCHAR(200),"
        "valor_diaria DECIMAL(10,2) NOT NULL"
        ") ENGINE=InnoDB;";

    const char *propostas =
        "CREATE TABLE IF NOT EXISTS propostas ("
        "proposta_id INT AUTO_INCREMENT PRIMARY KEY,"
        "cliente_id INT NOT NULL,"
        "servico_id INT NOT NULL,"
        "descricao VARCHAR(200) NOT NULL,"
        "valor_unitario DECIMAL(10,2) NOT NULL,"
        "status VARCHAR(50) NOT NULL,"
        "qnt_dias INT NOT NULL,"
        "valor_total DECIMAL(10,2) NOT NULL,"
        "data_inicio DATE NOT NULL,"
        "data_final DATE NOT NULL,"
        "data_proposta DATETIME DEFAULT CURRENT_TIMESTAMP,"
        "CONSTRAINT fk_propostas_clientes "
        "FOREIGN KEY (cliente_id) REFERENCES clientes(cliente_id) "
        "ON UPDATE CASCADE ON DELETE RESTRICT,"
        "CONSTRAINT fk_propostas_servicos "
        "FOREIGN KEY (servico_id) REFERENCES servicos(servico_id) "
        "ON UPDATE CASCADE ON DELETE RESTRICT"
        ") ENGINE=InnoDB;";

    if (mysql_query(conn, clientes))
    {
        printf("Erro ao criar tabela clientes: %s\n", mysql_error(conn));
        return 0;
    }

    if (mysql_query(conn, servicos))
    {
        printf("Erro ao criar tabela servicos: %s\n", mysql_error(conn));
        return 0;
    }

    if (mysql_query(conn, propostas))
    {
        printf("Erro ao criar tabela propostas: %s\n", mysql_error(conn));
        return 0;
    }

    printf("Tabelas verificadas/criadas com sucesso!\n");
    return 1;
}

MYSQL *conectar_bd()
{
    MYSQL *conn = mysql_init(NULL);

    if (!conn)
    {
        printf("Erro ao iniciar conexão\n");
        return NULL;
    }

    int protocol = MYSQL_PROTOCOL_TCP;
    mysql_options(conn, MYSQL_OPT_PROTOCOL, &protocol);

    if (!mysql_real_connect(conn, "127.0.0.1", "admin", "admin", "db", 3306, NULL, 0))
    {
        printf("Erro ao conectar: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    criar_tabelas(conn);

    return conn;
}
