/* gera_binario.c
 * Gera arquivo binário com dois vetores aleatórios e o produto interno sequencial
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Uso: %s <nome_arquivo> <tamanho_vetor>\n", argv[0]);
        return -1;
    }

    char *nome_arquivo = argv[1];
    long int n = atol(argv[2]);

    float *vetA = (float*) malloc(sizeof(float) * n);
    float *vetB = (float*) malloc(sizeof(float) * n);

    if(!vetA || !vetB) {
        perror("malloc");
        return -1;
    }

    srand(time(NULL));

    // Preenche vetores com valores aleatórios entre 0 e 10
    for(long int i = 0; i < n; i++) {
        vetA[i] = ((float)rand() / RAND_MAX) * 10.0;
        vetB[i] = ((float)rand() / RAND_MAX) * 10.0;
    }

    // Calcula produto interno sequencial
    double produto = 0;
    for(long int i = 0; i < n; i++) {
        produto += vetA[i] * vetB[i];
    }

    // Grava no arquivo binário
    FILE *arq = fopen(nome_arquivo, "wb");
    if(!arq) {
        perror("fopen");
        free(vetA);
        free(vetB);
        return -1;
    }

    fwrite(&n, sizeof(long int), 1, arq);
    fwrite(vetA, sizeof(float), n, arq);
    fwrite(vetB, sizeof(float), n, arq);
    fwrite(&produto, sizeof(double), 1, arq);

    fclose(arq);
    free(vetA);
    free(vetB);

    printf("Arquivo '%s' criado com sucesso!\n", nome_arquivo);
    printf("Produto interno sequencial = %.6lf\n", produto);

    return 0;
}
