#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

float *vetor1, *vetor2;

typedef struct {
    int nthreads;
    int id;
    long int dimensao;
} t_Args;

typedef struct {
    int id;
    double prod_thread;
} t_Ret;

void* produto_interno(void* args) {
    t_Args* t_args = (t_Args *) args;
    t_Ret* t_ret = (t_Ret*) malloc(sizeof(t_Ret));
    long int fatia = t_args->dimensao/t_args->nthreads;
    long int inicio = t_args->id*fatia;
    long int fim = inicio + fatia;
    double prod_thread = 0;
    if (t_args->id == t_args->nthreads - 1) {
        fim = t_args->dimensao;
    }

    for(int i = inicio; i < fim; i++) {
        prod_thread += vetor1[i]*vetor2[i];
        printf("%lf\n", prod_thread);
    }

    t_ret->id = t_args->id;
    t_ret->prod_thread = prod_thread;
    pthread_exit((void*) t_ret);
}

int main (int argc, char* argv[]) {
    FILE* arquivo;
    t_Ret* t_ret = (t_Ret*) malloc(sizeof(t_Ret));
    long int dimensao;
    double retorno_thread;
    int nthreads;
    double var_relativa;
    double start, finish, elapsed, resultado_sequencial, resultado_concorrencia = 0;
    if (argc < 3) {
        printf("Erro! Entrada esperada:\n%s <num threads> <nome arquivo>\n", argv[0]);
        return 1;
    }

    nthreads = atoi(argv[1]);
    pthread_t tid[nthreads];
    arquivo = fopen(argv[2], "rb");

    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo.");
    }

    fread(&dimensao, sizeof(long int), 1, arquivo);
    vetor1 = (float *) malloc(dimensao*sizeof(float));
    vetor2 = (float *) malloc(dimensao*sizeof(float));
    fread(vetor1, sizeof(float), dimensao, arquivo);
    fread(vetor2, sizeof(float), dimensao, arquivo);
    fread(&resultado_sequencial, sizeof(double), 1, arquivo);
    // for (int i = 0; i < dimensao; i++) {
    //     printf("%d ", vetor1[i]);
    // }
    // printf("\n");
    // for (int i = 0; i < dimensao; i++) {
    //     printf("%d ", vetor2[i]);
    // }
    // printf("\n");
    // printf("%ld\n", dimensao);
    // printf("\n");
    // printf("%ld\n", resultado_sequencial); 
    GET_TIME(start);
    for (int i = 0; i < nthreads; i++) {
        t_Args* t_args = (t_Args *) malloc(sizeof(t_Args));
        t_args->nthreads = nthreads;
        t_args->id = i;
        t_args->dimensao = dimensao;
        pthread_create(&tid[i], NULL, produto_interno, (void *) t_args);
    }

    for (int i = 0 ; i < nthreads; i++) {
        pthread_join(tid[i], (void **) &t_ret);
        resultado_concorrencia += t_ret->prod_thread;
    }
    GET_TIME(finish);

    elapsed = finish - start;
    var_relativa = abs((resultado_sequencial - resultado_concorrencia) / resultado_sequencial);
    printf("Result Seq: %lf\nResult Con: %lf\n", resultado_sequencial, resultado_concorrencia);
    printf("Variacao relativa: %f\n", var_relativa);
    printf("Tempo Concorrente: %lf segundos\n", elapsed);
    return 0;
}