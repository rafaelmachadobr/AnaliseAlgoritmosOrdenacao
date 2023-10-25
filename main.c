#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int movimento = 0; // Variável global de registro dos movimentos.
int trocas = 0, comparacoes = 0; // Variáveis de registro das trocas e comparações

// Função para mostrar as estatisticas
void mostrarEstatisticas(int comparacoes, int trocas, float tempoExecucao) {
    printf("\nNúmero de comparações: %i", comparacoes);
    printf("\nNúmero de trocas de posição: %i", trocas);
    printf("\nTempo (em segundos): %f\n", tempoExecucao);
}

// Função para imprimir o array
void imprimirArray(int lista[], int tamanho) {
    printf("[");
    for (int i = 0; i < tamanho; i++) {
        printf("%d", lista[i]);
        if (i < tamanho - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Função para printar o array
void printArray(int lista[], int tamanho) {
    printf("[");
    for (int i = 0; i < tamanho; i++) {
        printf("%d, ", lista[i]);
    }
    printf("]\n");
}

// Função Bubble Sort
void bubbleSort(int vetor[], int tamanho) {
    int aux, i, j;
    for (j = tamanho - 1; j >= 1; j--) {
        for (i = 0; i < j; i++) {
            comparacoes++;
            if (vetor[i] > vetor[i + 1]) {
                trocas++;
                aux = vetor[i];
                vetor[i] = vetor[i + 1];
                vetor[i + 1] = aux;
            }
        }
    }
}

// Função QuickSort
void quick_sort(int *a, int left, int right) {
    int i, j, x, y;
    i = left;
    j = right;
    x = a[(left + right) / 2];
    trocas += 3;
    while (i <= j) {
        while (a[i] < x && i < right) {
            i++;
            comparacoes++;
            trocas++;
        }
        while (a[j] > x && j > left) {
            j--;
            comparacoes++;
            trocas++;
        }
        if (i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            movimento += 3;
            i++;
            j--;
        }
    }
    if (j > left) {
        quick_sort(a, left, j);
    }
    if (i < right) {
        quick_sort(a, i, right);
    }
}

int main() {
    int numero, valor, tamanho = 50, lista[50] = {}; // Declaração dos valores a serem usados (tamanhos)

    // Variáveis para armazenar tempo
    float beginBubble, endBubble, tempoBubble;
    float beginQuick, endQuick, tempoQuick;

    FILE *arqNome = fopen("dados\\1k\\Com Duplicidade\\Aleatório\\dtaleat1kdup5.txt", "r");

    // Verificação se o arquivo foi devidamente selecionado
    if (arqNome != NULL) {
        int i = 0;
    int numeroLido;

    while (i < tamanho && fscanf(arqNome, "%d", &numeroLido) != EOF) {
        if (numeroLido != 0) {
            lista[i] = numeroLido;
            i++;
        }
    }

    tamanho = i;
    }

    LOOP: // Usado para reiniciar o menu
    printf("Selecione o algoritmo de organização:\n");
    printf("1. Bubble Sort;\n");
    printf("3. Quick Sort;\n");
    printf("Número do algoritmo: ");
    scanf("\n %d", &valor); // Leitura do input

    switch (valor) // Switch que trata qual função será chamada
    {
    case 1:
        // Chama Bubble Sort e inicia timer
        beginBubble = clock();
        bubbleSort(lista, tamanho);

        imprimirArray(lista, tamanho);

        endBubble = clock();
        tempoBubble = (float)(endBubble - beginBubble) / CLOCKS_PER_SEC; // Contagem do tempo

        mostrarEstatisticas(comparacoes, trocas, tempoBubble);
        break;

    case 3:
        // Chama o Quick Sort e inicia o timer
        beginQuick = clock();
        quick_sort(lista, 0, tamanho - 1);

        imprimirArray(lista, tamanho);

        endQuick = clock();
        tempoQuick = (float)(endQuick - beginQuick) / CLOCKS_PER_SEC; // Contagem do tempo

        mostrarEstatisticas(comparacoes, trocas, tempoQuick);
        break;

    default: // Caso o usuário escolha um número diferente de 1, 2, 3 ou 4
        printf("\nOpção inválida! Escolha as opções listadas (apenas o número).\n\n");
        goto LOOP;
    }

    // Fecha o arquivo utilizado
    fclose(arqNome);

    return 0;
}

