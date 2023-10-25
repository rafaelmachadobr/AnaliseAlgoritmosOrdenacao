#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para mostrar as estatísticas
void mostrarEstatisticas(int comparacoes, int trocas, float tempoExecucao) {
    printf("\nNúmero de comparações: %i\n", comparacoes);
    printf("Número de trocas de posição: %i\n", trocas);
    printf("Tempo (em segundos): %f\n\n", tempoExecucao);
}

// Função para imprimir o array
void imprimirArray(int lista[], int tamanho) {
    printf("\n[");
    for (int i = 0; i < tamanho; i++) {
        printf("%d", lista[i]);
        if (i < tamanho - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Função Bubble Sort
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

// Função Merge Sort
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

void mergeSort(int arr[], int left, int right, int *trocas, int *comparacoes) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, trocas, comparacoes);
        mergeSort(arr, mid + 1, right, trocas, comparacoes);
        merge(arr, left, mid, right, trocas, comparacoes);
    }
}

// Função QuickSort
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
    int valor, tamanho;
    int trocas = 0, comparacoes = 0;

    printf("Selecione o tamanho da base de dados:\n\n");
    printf("1. 10\n");
    printf("2. 50\n");
    printf("3. 100\n");
    printf("4. 500\n");
    printf("5. 1k\n");
    printf("6. 5k\n");
    printf("7. 10k\n");
    printf("8. 50k\n");
    printf("9. 100k\n\n");
    printf("Número do tamanho (1-9): ");
    scanf("%d", &valor);

    char *tamanhos[] = {"10", "50", "100", "500", "1k", "5k", "10k", "50k", "100k"};
    int tamanhosInteiros[] = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000};
    char *duplicidade[] = {"Com Duplicidade", "Sem Duplicidade"};
    char *ordem[] = {"Aleatório", "Concavo-DecresceCresce", "Convexo-CresceDescresce", "Crescente", "Descrescente"};
    char *abreviacoesOrdem[] = {"aleat", "concv", "convx", "cresc", "decre"};
    char *duplicidadeOrdem[] = {"dup", "uni"};

    printf("\nSelecione a duplicidade:\n\n");
    printf("1. Com Duplicidade\n");
    printf("2. Sem Duplicidade\n");
    printf("\nNúmero da duplicidade (1-2): ");
    int duplicidadeValor;
    scanf("%d", &duplicidadeValor);

    if (duplicidadeValor < 1 || duplicidadeValor > 2) {
        printf("Opção inválida!\n");
        return 1;
    }

    printf("Selecione a ordem:\n\n");
    printf("1. Aleatório\n");
    printf("2. Concavo-DecresceCresce\n");
    printf("3. Convexo-CresceDescresce\n");
    printf("4. Crescente\n");
    printf("5. Descrescente\n\n");
    printf("Número da ordem (1-5): ");
    int ordemValor;
    scanf("%d", &ordemValor);

    if (ordemValor < 1 || ordemValor > 5) {
        printf("Opção inválida!\n");
        return 1;
    }

	printf("\nSelecione o sufixo do arquivo (0 a 9): ");
	int arquivoSufixo;
	scanf("%d", &arquivoSufixo);

	if (arquivoSufixo < 0 || arquivoSufixo > 9) {
	    printf("Sufixo inválido!\n");
	    return 1;
	}
	
	tamanho = tamanhosInteiros[valor - 1];

    // Constrói o caminho do arquivo de dados com base nas seleções do usuário
    char caminhoArquivo[256];
	snprintf(caminhoArquivo, sizeof(caminhoArquivo), "dados\\%s\\%s\\%s\\dt%s%s%s%d.txt",
    tamanhos[valor - 1], duplicidade[duplicidadeValor - 1], ordem[ordemValor - 1], abreviacoesOrdem[ordemValor - 1],
    tamanhos[valor - 1], duplicidadeOrdem[duplicidadeValor - 1], arquivoSufixo);

	printf("\nBase de dados selecionada selecionada com tamanho %s, %s e %s.\n\n", tamanhos[valor - 1], duplicidade[duplicidadeValor - 1], ordem[ordemValor - 1]);

    // Abre o arquivo
    FILE *arqNome = fopen(caminhoArquivo, "r");

    if (arqNome == NULL) {
        printf("Erro ao abrir o arquivo. Certifique-se de que o caminho e o nome do arquivo estão corretos.\n");
        return 1; // Encerra o programa com um código de erro
    }

    int lista[tamanho];

    // Variáveis para armazenar tempo
    float beginBubble, endBubble, tempoBubble;
    float beginMerge, endMerge, tempoMerge;
    float beginQuick, endQuick, tempoQuick;

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

        if (scanf("%d", &valor) != 1) {
            printf("\nEntrada inválida! Insira um número correspondente à opção desejada.\n\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            continue;
        }

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

	free(lista); // Libera a memória alocada para o array dinâmico
	return 0; // Encerra o programa
}

