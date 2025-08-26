#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

float *vetA;
float *vetB;

// Estrutura de argumentos para cada thread
typedef struct {
    long int n;        // tamanho dos vetores
    int nthreads;    // número de threads
    int id;          // id da thread
} t_args;

// Função que cada thread executa
void *produto_interno_thread(void *args) {
    t_args *arg = (t_args*) args;
    long int fatia = arg->n / arg->nthreads;
    long int ini = arg->id * fatia;
    long int fim = (arg->id == arg->nthreads - 1) ? arg->n : ini + fatia;

    float soma_local = 0;
    for(long int i = ini; i < fim; i++) {
        soma_local += vetA[i] * vetB[i];
    }

    float *ret = (float*) malloc(sizeof(float));
    if(ret) *ret = soma_local;
    pthread_exit((void*) ret);
}

int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Uso: %s <arquivo_binario> <nthreads>\n", argv[0]);
        return -1;
    }

    char *arquivo = argv[1];
    int nthreads = atoi(argv[2]);
    long int n;

    FILE *arq = fopen(arquivo, "rb");
    if(!arq) { perror("Erro ao abrir arquivo"); return -1; }

    // lê dimensão
    if(fread(&n, sizeof(long int), 1, arq) != 1) {
        perror("Erro lendo n");
        fclose(arq);
        return -1;
    }

    // aloca vetores
    vetA = (float*) malloc(sizeof(float) * n);
    vetB = (float*) malloc(sizeof(float) * n);
    if(!vetA || !vetB) { perror("malloc"); fclose(arq); return -1; }

    if(fread(vetA, sizeof(float), n, arq) != n) { perror("Erro lendo vetA"); fclose(arq); return -1; }
    if(fread(vetB, sizeof(float), n, arq) != n) { perror("Erro lendo vetB"); fclose(arq); return -1; }

    double resultado_sequencial;
    if(fread(&resultado_sequencial, sizeof(double), 1, arq) != 1) { perror("Erro lendo resultado sequencial"); fclose(arq); return -1; }
    fclose(arq);

    // Cria threads
    pthread_t *tid = (pthread_t*) malloc(sizeof(pthread_t) * nthreads);
    if(!tid) { perror("malloc tid"); return -1; }

    t_args *args;
    double inicio, fim;
    GET_TIME(inicio);

    for(int i = 0; i < nthreads; i++) {
        args = (t_args*) malloc(sizeof(t_args));
        args->n = n;
        args->nthreads = nthreads;
        args->id = i;
        pthread_create(&tid[i], NULL, produto_interno_thread, (void*) args);
    }

    // coleta resultados
    float produto = 0;
    float *soma_thread;
    for(int i = 0; i < nthreads; i++) {
        pthread_join(tid[i], (void**) &soma_thread);
        produto += *soma_thread;
        free(soma_thread);
    }

    GET_TIME(fim);

    printf("Produto interno concorrente = %.9f\n", produto);
    printf("Produto interno sequencial  = %.9f\n", resultado_sequencial);
    printf("Variacao relativa           = %.9f\n", (resultado_sequencial - produto)/resultado_sequencial);
    printf("Tempo de execucao           = %.9f segundos\n", fim - inicio);

    free(vetA);
    free(vetB);
    free(tid);

    return 0;
}
