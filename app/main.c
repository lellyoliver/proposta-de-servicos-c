#include <stdio.h>
#include "bd.h"

int main() {
    if (conectar_bd()) {
        printf("OK\n");
    } else {
        printf("ERRO\n");
    }

    printf("Pressione Enter para sair...");
    getchar();

    return 0;
}