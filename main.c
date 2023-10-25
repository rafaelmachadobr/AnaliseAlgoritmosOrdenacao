#include <stdio.h>

int main() {
    FILE *arquivo = fopen("dados\\10\\Com Duplicidade\\Aleatório\\dtaleat10dup0.txt", "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    int valor;
    while (fscanf(arquivo, "%d", &valor) != EOF) {
        printf("%d\n", valor);
    }

    fclose(arquivo);

    return 0;
}

