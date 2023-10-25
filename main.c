#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fun��o para mostrar as estatisticas
void mostrarEstatisticas(int comparacoes, int trocas, float tempoExecucao) {
    printf("\nN�mero de compara��es: %i", comparacoes);
    printf("\nN�mero de trocas de posi��o: %i", trocas);
    printf("\nTempo (em segundos): %f\n", tempoExecucao);
}

// Fun��o para imprimir o array
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

// Fun��o para printar o array
void printArray(int lista[], int tamanho) {
    printf("[");
    for (int i = 0; i < tamanho; i++) {
        printf("%d, ", lista[i]);
    }
    printf("]\n");
}

// Fun��o Bubble Sort
void bubbleSort(int vetor[], int tamanho, int *trocas, int *comparacoes) {
    int aux, i, j;
    for (j = tamanho - 1; j >= 1; j--) {
        for (i = 0; i < j; i++) {
            (*comparacoes)++;
            if (vetor[i] > vetor[i + 1]) {
                (*trocas)++;
                aux = vetor[i];
                vetor[i] = vetor[i + 1];
                vetor[i + 1] = aux;
            }
        }
    }
}

// Fun��o QuickSort
void quickSort(int *a, int left, int right, int *trocas, int *comparacoes) {
    int i, j, x, y;
    i = left;
    j = right;
    x = a[(left + right) / 2];
    (*trocas) += 3;
    while (i <= j) {
        while (a[i] < x && i < right) {
            i++;
            (*comparacoes)++;
            (*trocas)++;
        }
        while (a[j] > x && j > left) {
            j--;
            (*comparacoes)++;
            (*trocas)++;
        }
        if (i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            (*trocas) += 3;
            i++;
            j--;
        }
    }
    if (j > left) {
        quickSort(a, left, j, trocas, comparacoes);
    }
    if (i < right) {
        quickSort(a, i, right, trocas, comparacoes);
    }
}

int main() {
    int valor, tamanho = 50;
    int lista[50] = {0}; // Inicializa o array com zeros
    int trocas = 0, comparacoes = 0; // Vari�veis locais para rastrear trocas e compara��es

    // Vari�veis para armazenar tempo
    float beginBubble, endBubble, tempoBubble;
    float beginQuick, endQuick, tempoQuick;

    FILE *arqNome = fopen("dados\\1k\\Com Duplicidade\\Aleat�rio\\dtaleat1kdup5.txt", "r");

    // Verifica��o se o arquivo foi devidamente selecionado
	if (arqNome == NULL) {
	    printf("Erro ao abrir o arquivo. Certifique-se de que o caminho e o nome do arquivo est�o corretos.\n");
	    return 1; // Encerra o programa com um c�digo de erro
	}
	
	// O arquivo foi aberto com sucesso, podemos continuar a leitura
	int i = 0;
	int numeroLido;
	
	while (i < tamanho && fscanf(arqNome, "%d", &numeroLido) != EOF) {
	    if (numeroLido != 0) {
	        lista[i] = numeroLido;
	        i++;
	    }
	}

	tamanho = i;

    int sair = 0; // Vari�vel de controle para sair do programa

    while (!sair) {
        printf("Selecione o algoritmo de organiza��o:\n");
        printf("1. Bubble Sort;\n");
        printf("3. Quick Sort;\n");
        printf("N�mero do algoritmo (ou 0 para sair): ");
        scanf("%d", &valor);

        switch (valor) {
            case 1:
                // Chama Bubble Sort e inicia timer
                beginBubble = clock();
                bubbleSort(lista, tamanho, &trocas, &comparacoes);
                imprimirArray(lista, tamanho);
                endBubble = clock();
                tempoBubble = (float)(endBubble - beginBubble) / CLOCKS_PER_SEC;
                mostrarEstatisticas(comparacoes, trocas, tempoBubble);
                break;

            case 3:
                // Chama o Quick Sort e inicia o timer
                beginQuick = clock();
                quickSort(lista, 0, tamanho - 1, &trocas, &comparacoes);
                imprimirArray(lista, tamanho);
                endQuick = clock();
                tempoQuick = (float)(endQuick - beginQuick) / CLOCKS_PER_SEC;
                mostrarEstatisticas(comparacoes, trocas, tempoQuick);
                break;

            case 0:
                sair = 1; // Define a vari�vel "sair" como 1 para sair do loop
                break;

            default:
                printf("\nOp��o inv�lida! Escolha as op��es listadas (apenas o n�mero).\n\n");
                break;
        }
    }

    // Fecha o arquivo utilizado
    fclose(arqNome);

    return 0;
}

