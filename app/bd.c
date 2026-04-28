#include <mysql/mysql.h>
#include <stdio.h>

int conectar_bd() {
    MYSQL *conn = mysql_init(NULL);

    if (!conn) {
        printf("Erro init\n");
        return 0;
    }

    int protocol = MYSQL_PROTOCOL_TCP;
    mysql_options(conn, MYSQL_OPT_PROTOCOL, &protocol);

    if (!mysql_real_connect(conn,
                            "127.0.0.1",
                            "admin",
                            "admin",
                            "db",
                            3306,
                            NULL,
                            0)) {

        printf("Erro: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    printf("Conectado!\n");

    mysql_close(conn);
    return 1;
}