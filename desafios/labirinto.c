

/*
ALGORITMO DE BACKTRACKING E um labirinto
O algoritmo de backtracking é uma técnica de resolução de 
problemas que explora sistematicamente todas as possíveis 
soluções de um problema, testando cada opção e "retornando"
(backtracking) quando uma escolha leva a um beco sem saída
ou uma solução inválida.
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//diretivas para a matriz do labirinto
#define L 5
#define A 5

int** criarMatrizBinaria(){
    //aloca um numero L de colunas para a matriz que é um vetor de vetores
    int ** obj = malloc(sizeof(int*) * L);
    //em cada index da coluna, aloca um vetor de tamanho A para as linhas
    for(int i=0; i<A; i++){
        obj[i] = malloc(sizeof(int) * A);
    }

    //preenche a matriz com numeros randomicos
    for(int i=0; i<A; i++){
        for(int j=0; j<L; j++){
            obj[i][j] = rand() % 2;
        }
    }
    //deve começar pelo canto superior esquerdo que sempre será 0
    obj[0][0] = 0;
    return obj;
}

void printMatrizBinaria(int **mat){
    for (int i=0; i<L; i++) {
        for(int j=0; j<A; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void liberarMatrizBinaria(int **mat){
    for(int i=0; i<L; i++){
        free(mat[i]);
    }
    free(mat);
}

//dado que o inicio é em mat[0][0] e o fim em mat[A-1][L-1]
int caminhar(int **mat, int py, int px){

    if(py < 0 || py > A-1 || px < 0 || px > L-1) return 0;
    if(mat[py][px] == 1) return 0;

    //achou o ponto
    if(py == A-1 && px == L-1) return 1; 
    
    if(caminhar(mat, py, px+1)==1 || caminhar(mat, py+1, px)==1){
        return 1;
    }
    return 0;
}

int main(){
    srand(time(NULL)); //gerador de numeros randomicos
    int ** mat = criarMatrizBinaria();
    printMatrizBinaria(mat);

    if(caminhar(mat, 0, 0)==1){
        printf("achou o caminho");
    }else{
        printf("nao achou o caminho");
    }

    liberarMatrizBinaria(mat);
    return 0;
}
