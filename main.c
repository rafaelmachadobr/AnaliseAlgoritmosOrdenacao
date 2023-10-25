#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para mostrar as estatísticas
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

// Função para ordenar o array usando o algoritmo Bubble Sort
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

// Função para mesclar duas metades ordenadas de um array para o algoritmo Merge Sort
void merge(int arr[], int left, int mid, int right, int *trocas, int *comparacoes) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        (*comparacoes)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        (*trocas)++;
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Função para ordenar um array usando o algoritmo Merge Sort
void mergeSort(int arr[], int left, int right, int *trocas, int *comparacoes) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, trocas, comparacoes);
        mergeSort(arr, mid + 1, right, trocas, comparacoes);
        merge(arr, left, mid, right, trocas, comparacoes);
    }
}

// Função para ordenar um array usando o algoritmo Quick Sort
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
    int trocas = 0, comparacoes = 0; // Variáveis locais para rastrear trocas e comparações

    // Variáveis para armazenar tempo
    float beginBubble, endBubble, tempoBubble;
    float beginMerge, endMerge, tempoMerge;
    float beginQuick, endQuick, tempoQuick;

    FILE *arqNome = fopen("dados\\1k\\Com Duplicidade\\Aleatório\\dtaleat1kdup5.txt", "r");

    // Verificação se o arquivo foi devidamente selecionado
	if (arqNome == NULL) {
	    printf("Erro ao abrir o arquivo. Certifique-se de que o caminho e o nome do arquivo estão corretos.\n");
	    return 1; // Encerra o programa com um código de erro
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

    int sair = 0; // Variável de controle para sair do programa

    while (!sair) {
        printf("Selecione o algoritmo de organização:\n");
        printf("1. Bubble Sort;\n");
        printf("2. Merge Sort;\n");
        printf("3. Quick Sort;\n");
        printf("Número do algoritmo (ou 0 para sair): ");
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
                
            case 2:
			    // Chama o Merge Sort e inicia o timer
			    beginMerge = clock();
			    mergeSort(lista, 0, tamanho - 1, &trocas, &comparacoes);
			    imprimirArray(lista, tamanho);
			    endMerge = clock();
			    tempoMerge = (float)(endMerge - beginMerge) / CLOCKS_PER_SEC;
			    mostrarEstatisticas(comparacoes, trocas, tempoMerge);
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
                sair = 1; // Define a variável "sair" como 1 para sair do loop
                break;

            default:
                printf("\nOpção inválida! Escolha as opções listadas (apenas o número).\n\n");
                break;
        }
    }

    // Fecha o arquivo utilizado
    fclose(arqNome);

    return 0;
}

