/*
Programa auxiliar para gerar um vetor de floats 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000 //valor maximo de um elemento do vetor
//descomentar o define abaixo caso deseje imprimir uma versao do vetor gerado no formato texto
//#define LOG 

int main(int argc, char*argv[]) {
   float *vetor1, *vetor2; //vetores que serão gerados
   long int n; //qtde de elementos do vetor
   float elem1; //valor gerado para incluir no vetor 1
   float elem2; //valor gerado para incluir no vetor 2
   double elapsed, produto = 0; //produto interno dos elementos gerados
   //double start, finish;
   clock_t start, finish;
   int fator = 1; //fator multiplicador para gerar números negativos
   FILE * descritorArquivo; //descritor do arquivo de saida

   //recebe os argumentos de entrada
   if(argc < 3) {
      fprintf(stderr, "Digite: %s <dimensao> <nome arquivo saida>\n", argv[0]);
      return 1;
   }
   n = atoi(argv[1]);
   
   //aloca memoria para o vetor
   vetor1 = (float*) malloc(sizeof(float) * n);
   vetor2 = (float*) malloc(sizeof(float) * n);
   if(!(vetor1) || !(vetor2)) {
      fprintf(stderr, "Erro de alocao da memoria do vetor\n");
      return 2;
   }
   //preenche o vetor com valores float aleatorios
   srand(time(NULL));
   for(long int i = 0; i < n; i++) {
        elem1 = (rand() % MAX)/3.0 * fator;
        elem2 = (rand() % MAX)/3.0 * fator;
        vetor1[i] = elem1;
        vetor2[i] = elem2;
        fator *= -1;
   }

   //calcula produto interno e mede tempo
   start = clock();
   for (long int i = 0; i < n; i++) {
      produto += vetor1[i]*vetor2[i];
   }
   finish = clock();
   elapsed = (double) (finish - start) / CLOCKS_PER_SEC;
   //imprimir na saida padrao o vetor gerado
   #ifdef LOG
   fprintf(stdout, "%ld\n", n);
   for(long int i=0; i<n; i++) {
      fprintf(stdout, "%f ",vetor[i]);
   }
   fprintf(stdout, "\n");
   fprintf(stdout, "%lf\n", soma);
   #endif

   //escreve o vetor no arquivo
   //abre o arquivo para escrita binaria
   descritorArquivo = fopen(argv[2], "wb");
   if(!descritorArquivo) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 3;
   }
   //escreve a dimensao
   fwrite(&n, sizeof(long int), 1, descritorArquivo);
   //escreve os elementos do vetor
   fwrite(vetor1, sizeof(float), n, descritorArquivo);
   fwrite(vetor2, sizeof(float), n, descritorArquivo);
   //escreve o somatorio
   fwrite(&produto, sizeof(double), 1, descritorArquivo);
   //finaliza o uso das variaveis
   fclose(descritorArquivo);
   free(vetor1);
   free(vetor2);
   printf("Tempo Sequencial: %f\n", elapsed);
   return 0;
} 
