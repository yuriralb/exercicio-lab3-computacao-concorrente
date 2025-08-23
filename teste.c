#include <stdio.h>
#include <stdlib.h>

int main() {
    float *vetor1, *vetor2;
    long int dimensao;
    double produto_interno;
    FILE* arq;

    arq = fopen("dados.bin", "rb");
    fread(&dimensao, sizeof(long int), 1, arq);
    vetor1 = (float*) malloc(sizeof(float) * dimensao);
    vetor2 = (float*) malloc(sizeof(float) * dimensao);
    fread(vetor1, sizeof(float), dimensao, arq);
    fread(vetor2, sizeof(float), dimensao, arq);
    fread(&produto_interno, sizeof(double), 1, arq);

    printf("\n[");
    for (long int i = 0; i < dimensao; i++) {
        printf("%f ", vetor1[i]);
    }
    printf("]\n");

    printf("\n[");
    for (long int i = 0; i < dimensao; i++) {
        printf("%f ", vetor2[i]);
    }
    printf("]\n");

    printf("Produto interno: %lf\n", produto_interno);

    return 0;
}