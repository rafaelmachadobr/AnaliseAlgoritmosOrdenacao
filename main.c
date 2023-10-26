#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Funcao para mostrar as estatisticas
void mostrarEstatisticas(int comparacoes, int trocas, float tempoExecucao)
{
	printf("\nNumero de comparacoes: %i\n", comparacoes);
	printf("nNumero de trocas de posicao: %i\n", trocas);
	printf("Tempo (em segundos): %f\n\n", tempoExecucao);
}

// Funcao para imprimir o array
void imprimirArray(int lista[], int tamanho)
{
	printf("\n[");
	for (int i = 0; i < tamanho; i++)
	{
		printf("%d", lista[i]);
		if (i < tamanho - 1)
		{
			printf(", ");
		}
	}
	printf("]\n");
}

// Funcao Bubble Sort
void bubbleSort(int vetor[], int tamanho, int *trocas, int *comparacoes)
{
	int aux, i, j;
	for (j = tamanho - 1; j >= 1; j--)
	{
		for (i = 0; i < j; i++)
		{
			(*comparacoes)++;
			if (vetor[i] > vetor[i + 1])
			{
				(*trocas)++;
				aux = vetor[i];
				vetor[i] = vetor[i + 1];
				vetor[i + 1] = aux;
			}
		}
	}
}

// Funcao Merge Sort
void merge(int arr[], int esquerda, int meio, int direita, int *trocas, int *comparacoes)
{
    int i, j, k;
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
    {
        L[i] = arr[esquerda + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[meio + 1 + j];
    }

    i = 0;
    j = 0;
    k = esquerda;
    while (i < n1 && j < n2)
    {
        (*comparacoes)++;
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        (*trocas)++;
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int esquerda, int direita, int *trocas, int *comparacoes)
{
    if (esquerda < direita)
    {
        int meio = esquerda + (direita - esquerda) / 2;
        mergeSort(arr, esquerda, meio, trocas, comparacoes);
        mergeSort(arr, meio + 1, direita, trocas, comparacoes);
        merge(arr, esquerda, meio, direita, trocas, comparacoes);
    }
}

// Funcao QuickSort
void quickSort(int *a, int esquerda, int direita, int *trocas, int *comparacoes)
{
    int i, j, x, y;
    i = esquerda;
    j = direita;
    x = a[(esquerda + direita) / 2];
    (*trocas) += 3;
    while (i <= j)
    {
        while (a[i] < x && i < direita)
        {
            i++;
            (*comparacoes)++;
            (*trocas)++;
        }
        while (a[j] > x && j > esquerda)
        {
            j--;
            (*comparacoes)++;
            (*trocas)++;
        }
        if (i <= j)
        {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            (*trocas) += 3;
            i++;
            j--;
        }
    }
    if (j > esquerda)
    {
        quickSort(a, esquerda, j, trocas, comparacoes);
    }
    if (i < direita)
    {
        quickSort(a, i, direita, trocas, comparacoes);
    }
}


int main()
{
	int valor, tamanho;
	int trocas = 0, comparacoes = 0;
	int sairPrograma = 0; // Variavel de controle para sair do programa

	printf("\n=== Programa de Analise de Algoritmos de Ordenacao ===\n");
	printf("Este programa permite analisar o desempenho de algoritmos de ordenacao.\n");

	while (!sairPrograma)
	{
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
		printf("Numero do tamanho (1-9): ");
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
		printf("\nNumero da duplicidade (1-2): ");
		int duplicidadeValor;
		scanf("%d", &duplicidadeValor);

		if (duplicidadeValor < 1 || duplicidadeValor > 2)
		{
			printf("Opcao invalida!\n");
			return 1;
		}

		printf("Selecione a ordem:\n\n");
		printf("1. Aleatorio\n");
		printf("2. Concavo-DecresceCresce\n");
		printf("3. Convexo-CresceDescresce\n");
		printf("4. Crescente\n");
		printf("5. Descrescente\n\n");
		printf("Numero da ordem (1-5): ");
		int ordemValor;
		scanf("%d", &ordemValor);

		if (ordemValor < 1 || ordemValor > 5)
		{
			printf("Opcao invalida!\n");
			return 1;
		}

		printf("\nSelecione o sufixo do arquivo (0 a 9): ");
		int arquivoSufixo;
		scanf("%d", &arquivoSufixo);

		if (arquivoSufixo < 0 || arquivoSufixo > 9)
		{
			printf("Sufixo invalido!\n");
			return 1;
		}

		tamanho = tamanhosInteiros[valor - 1];

		// Constroi o caminho do arquivo de dados com base nas selecoes do usuario
		char caminhoArquivo[256];
		snprintf(caminhoArquivo, sizeof(caminhoArquivo), "dados\\%s\\%s\\%s\\dt%s%s%s%d.txt",
				 tamanhos[valor - 1], duplicidade[duplicidadeValor - 1], ordem[ordemValor - 1], abreviacoesOrdem[ordemValor - 1],
				 tamanhos[valor - 1], duplicidadeOrdem[duplicidadeValor - 1], arquivoSufixo);

		printf("\nBase de dados selecionada selecionada com tamanho %s, %s e %s.\n\n", tamanhos[valor - 1], duplicidade[duplicidadeValor - 1], ordem[ordemValor - 1]);

		// Abre o arquivo
		FILE *arqNome = fopen(caminhoArquivo, "r");

		if (arqNome == NULL)
		{
			printf("Erro ao abrir o arquivo. Certifique-se de que o caminho e o nome do arquivo estao corretos.\n");
			return 1; // Encerra o programa com um codigo de erro
		}

		int lista[tamanho];

		// Variaveis para armazenar tempo
		float beginBubble, endBubble, tempoBubble;
		float beginMerge, endMerge, tempoMerge;
		float beginQuick, endQuick, tempoQuick;

		// Verificacao se o arquivo foi devidamente selecionado
		if (arqNome == NULL)
		{
			printf("Erro ao abrir o arquivo. Certifique-se de que o caminho e o nome do arquivo estao corretos.\n");
			return 1; // Encerra o programa com um codigo de erro
		}

		// O arquivo foi aberto com sucesso, podemos continuar a leitura
		int i = 0;
		int numeroLido;

		while (i < tamanho && fscanf(arqNome, "%d", &numeroLido) != EOF)
		{
			if (numeroLido != 0)
			{
				lista[i] = numeroLido;
				i++;
			}
		}

		tamanho = i;

		char *nomeDoArquivo = strrchr(caminhoArquivo, '\\');
		if (nomeDoArquivo != NULL)
		{
			nomeDoArquivo++; // Avancar para o primeiro caractere apos a ultima barra invertida
		}
		else
		{
			// Se nao houver barra invertida no caminho, use o caminho inteiro como nome do arquivo
			nomeDoArquivo = caminhoArquivo;
		}

		// Adicionar a extensao ".txt" ao nome do arquivo
		char nomeDoRelatorio[256];
		snprintf(nomeDoRelatorio, sizeof(nomeDoRelatorio), "relatorios\\relatorio_%s.txt", nomeDoArquivo);

		FILE *relatorio = fopen(nomeDoRelatorio, "w");
		if (relatorio == NULL)
		{
			printf("Erro ao criar o arquivo de relatorio.\n");
			return 1;
		}

		fprintf(relatorio, "Relatorio de Analise de Algoritmos de Ordenacao\n\n");
		fprintf(relatorio, "Base de dados selecionada com tamanho %s, %s e %s.\n\n", tamanhos[valor - 1], duplicidade[duplicidadeValor - 1], ordem[ordemValor - 1]);
		fprintf(relatorio, "Caminho do arquivo: %s\n\n", caminhoArquivo);
		fclose(relatorio);

		int sairBaseDados = 0;

		while (!sairBaseDados)
		{
			printf("Selecione o algoritmo de organizacao:\n");
			printf("1. Bubble Sort;\n");
			printf("2. Merge Sort;\n");
			printf("3. Quick Sort;\n");
			printf("\nNumero do algoritmo (ou 0 para sair da base de dados atual): ");

			if (scanf("%d", &valor) != 1)
			{
				printf("\nEntrada invalida! Insira um numero correspondente a opcao desejada.\n\n");
				while (getchar() != '\n')
					; // Limpa o buffer de entrada
				continue;
			}

			// Extrair o nome do arquivo do caminho
			char *nomeDoArquivo = strrchr(caminhoArquivo, '\\');
			if (nomeDoArquivo != NULL)
			{
				nomeDoArquivo++; // Avance para o primeiro caractere apos a ultima barra invertida
			}
			else
			{
				// Se nao houver barra invertida no caminho, use o caminho inteiro como nome do arquivo
				nomeDoArquivo = caminhoArquivo;
			}

			// Adicionar a extensao ".txt" ao nome do arquivo
			char nomeDoRelatorio[256];
			snprintf(nomeDoRelatorio, sizeof(nomeDoRelatorio), "relatorios\\relatorio_%s.txt", nomeDoArquivo);

			FILE *relatorio = fopen(nomeDoRelatorio, "a"); // Abra o arquivo de relatorio em modo de anexacao
			if (relatorio == NULL)
			{
				printf("Erro ao criar o arquivo de relatorio.\n");
				return 1;
			}

			fprintf(relatorio, "Algoritmo: "); // Indique qual algoritmo esta sendo registrado
			switch (valor)
			{
			case 1:
				// Chama Bubble Sort e inicia timer
				fprintf(relatorio, "Bubble Sort\n");
				beginBubble = clock();
				bubbleSort(lista, tamanho, &trocas, &comparacoes);
				imprimirArray(lista, tamanho);
				endBubble = clock();
				tempoBubble = (float)(endBubble - beginBubble) / CLOCKS_PER_SEC;

				fprintf(relatorio, "Numero de comparacoes: %i\n", comparacoes);
				fprintf(relatorio, "Numero de trocas de posicao: %i\n", trocas);
				fprintf(relatorio, "Tempo (em segundos): %f\n\n", tempoBubble);
				mostrarEstatisticas(comparacoes, trocas, tempoBubble);

				break;

			case 2:
				// Chama o Merge Sort e inicia o timer
				fprintf(relatorio, "Merge Sort\n");
				beginMerge = clock();
				mergeSort(lista, 0, tamanho - 1, &trocas, &comparacoes);
				imprimirArray(lista, tamanho);
				endMerge = clock();
				tempoMerge = (float)(endMerge - beginMerge) / CLOCKS_PER_SEC;

				fprintf(relatorio, "Numero de comparacoes: %i\n", comparacoes);
				fprintf(relatorio, "Numero de trocas de posicao: %i\n", trocas);
				fprintf(relatorio, "Tempo (em segundos): %f\n\n", tempoMerge);
				mostrarEstatisticas(comparacoes, trocas, tempoMerge);
				break;

			case 3:
				// Chama o Quick Sort e inicia o timer
				fprintf(relatorio, "Quick Sort\n");
				beginQuick = clock();
				quickSort(lista, 0, tamanho - 1, &trocas, &comparacoes);
				imprimirArray(lista, tamanho);
				endQuick = clock();
				tempoQuick = (float)(endQuick - beginQuick) / CLOCKS_PER_SEC;

				fprintf(relatorio, "Numero de comparacoes: %i\n", comparacoes);
				fprintf(relatorio, "Numero de trocas de posicao: %i\n", trocas);
				fprintf(relatorio, "Tempo (em segundos): %f\n\n", tempoQuick);
				mostrarEstatisticas(comparacoes, trocas, tempoQuick);

				break;

			case 0:
				sairBaseDados = 1; // Define a variavel "sair" como 1 para sair do loop
				break;

			default:
				printf("\nOpcao invalida! Escolha as opcoes listadas (apenas o numero).\n\n");
				break;
			}

			fclose(relatorio);

			// Pergunta ao usuario se deseja selecionar outra base de dados
			printf("Deseja selecionar outra base de dados? (0 para sair ou qualquer outro numero para continuar): ");
			int resposta;
			scanf("%d", &resposta);
			if (resposta == 0)
			{
				sairBaseDados = 1; // Define a variavel "sairBaseDados" como 1 para sair do loop
			}
		}

		// Fecha o arquivo utilizado
		fclose(arqNome);

		// Reinicie as variaveis de controle para selecionar uma nova base de dados
		trocas = 0;
		comparacoes = 0;

		printf("\nDeseja sair do programa? (0 para sair ou qualquer outro numero para continuar): ");
		int resposta;
		scanf("%d", &resposta);
		if (resposta == 0)
		{
			sairPrograma = 1;
		}
	}

	printf("\nObrigado por usar o nosso programa! Esperamos que tenha sido util.\n");

	return 0; // Encerra o programa
}

