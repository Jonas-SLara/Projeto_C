/*
 *Leia uma palavra (sem acentos) e verifique se ela é um palíndromo 
 *(ou seja, se pode ser lida da mesma forma de trás para frente).
 *Não use strings prontas nem string.h: use char * e laços para comparação.
 *use a função fgets para controlar a entrada
*/

#include <stdio.h>
#include <stdlib.h>


#define END '\0'

int comprimento(char * palavra){
    int i=0;
    while(palavra[i] != END){ i++; }
    return i-1; //caractere nulo não contará
}

char verificar(char * palavra){
    int comp = comprimento(palavra)-1; //ultimo index do vetor de char
    int meio = comp/2; // 0, 1, 2, 3, 4

    for(int i = 0; i <= meio; i++){
        if(palavra[i] != palavra[comp-i]){
            return 'n'; //diferente então não é palindromo
        }
    }
    return 's';
}

int main(){
    char * palavra = malloc(30 * sizeof(char));
    fgets(palavra, 30, stdin);

    printf("%s", palavra);
    char res = verificar(palavra);
    printf("%c \n", res);
    getchar();
    free(palavra);
    return 0;
}
