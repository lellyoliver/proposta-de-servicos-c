#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

MYSQL* conectar_bd() {
    MYSQL *conn = mysql_init(NULL);

    if (!conn) {
        printf("Erro ao iniciar conexão\n");
        return NULL;
    }

    int protocol = MYSQL_PROTOCOL_TCP;
    mysql_options(conn, MYSQL_OPT_PROTOCOL, &protocol);

    if (!mysql_real_connect(conn, "127.0.0.1", "admin", "admin", "db", 3306, NULL, 0)) {
        printf("Erro ao conectar: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    
    return conn;
}