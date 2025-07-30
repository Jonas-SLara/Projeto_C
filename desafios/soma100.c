/*
Desafio 1 – Jogo da Soma 100 (nível fácil a médio)
Descrição:
Crie um programa que leia números inteiros entre 1 e 100 até que a soma total seja igual ou superior a 100.
O programa deve ignorar números fora do intervalo.
Ao final, imprima:
a quantidade de números válidos inseridos
a soma total
a média dos números válidos
*/

#include <stdio.h>

char valida(int temp){ return (temp < 100)? 's' : 'n'; }

int main(){
    int temp, soma=0, qtd=0;
    float media;
    while (soma < 100) {
        //valida a entrada para caso digite um valor que não pode ser convertido
        if(scanf("%d",  &temp) != 1){
            printf("erro inesperado");
            return -1;
        }
        
        if(valida(temp) == 's'){
            soma += temp;
            qtd++;
        }
        else{
            printf("numero fora do escopo\n");
        }
    }
    printf("valor da soma: %d \n", soma);
    printf("quantidade de entradas: %d \n", qtd);
    printf("media: %.2f", (float)soma/qtd);
    return 0;
}
