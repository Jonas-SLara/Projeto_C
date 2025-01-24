#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"
int main()
{
    srand(time(NULL));
    int n;
    printf("**escolha o tamanho do seu vetor**\n");
    scanf("%d", &n);
    int vetor[n];
    seqVet(vetor, n);
    //printVet(vetor, n);
    printf("\nvetor criado e embaralhado\n");
    //vetor finalizado para teste
    system("pause");
    system("cls");
    //comeca a contar o tempo para ordenamento
    time_t inicio = clock();
    //bubleSort(vetor, n);
    //insertSort(vetor, n);
    //selectSort(vetor, n);
    quickSort(vetor, 0, n);

    time_t fim = clock();
    //printVet(vetor, n);
    
    double tempo = ((double) fim - inicio)/CLOCKS_PER_SEC;
    printf("\ntempo de ordenacao: %f \n", tempo);
    free(vetor);
    return 0;
}
