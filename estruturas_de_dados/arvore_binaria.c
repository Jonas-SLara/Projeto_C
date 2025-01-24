#include <stdio.h>
#include <stdlib.h>
/*fun��es: inserir elementos na arvore, imprimir arvore com cada modulo,
buscar elementos na arvore, calcular altura da arvore*/

typedef struct arvore{
	int valor;
	struct arvore *esquerda;
	struct arvore *direita;
}arvore;

arvore *insere_v1(arvore *r, int c){
	//caso base, quando chegar na recurs�o, ou quando inicia uma arvore
	if(r==NULL){
		arvore *aux=(arvore*)malloc(sizeof(arvore));
		aux->direita=NULL;
		aux->esquerda=NULL;
		aux->valor=c;
		return aux;//r->esquerda ou direita onde era null recebe aux
	}
	else{
		//valor menor que a subarvore analisada, a esquerda 
		if(c < r->valor){
			r->esquerda = insere_v1(r->esquerda, c);
		}
		//do contrario a direita
		else{
			r->direita = insere_v1(r->direita, c);
		}
		return r;//desempilha fun��es at� chegar no n� raiz de volta e passala para a main
	}
}

void insere_v2(arvore **r, int c){//tipo de inser��o sem retorno, mais eficiente
	if(*r==NULL){
		*r=(arvore*)malloc(sizeof(arvore));
		(*r)->direita=NULL;
		(*r)->esquerda=NULL;
		(*r)->valor=c;
	}
	else{
		if(c < (*r)->valor){
			insere_v2(&((*r)->esquerda), c);
		}
		else{
			insere_v2(&((*r)->direita), c);
		}
	}
}


void imprime_v1(arvore *r){//pre fixado
	if(r!=NULL){
		printf("%d  ", r->valor);
		imprime_v1(r->esquerda);
		imprime_v1(r->direita);
	}
}

void imprime_v2(arvore *r){//pos fixado
	if(r!=NULL){
		imprime_v2(r->esquerda);
		printf("%d   ", r->valor);
		imprime_v2(r->direita);
	}
}

int calcula_altura(arvore *raiz){
	if(raiz==NULL){
		return -1;
	}
	else{
		//subes = subarvore da esquerda e subdir= subarvore da direita
		int subesq=calcula_altura(raiz->esquerda);
		int subdir=calcula_altura(raiz->direita);
		if(subesq>subdir){
			return subesq+1;
		}
		else{
			return subdir+1;
		}
	}
}

int main(){
    arvore *raiz=NULL;
	insere_v2(&raiz, 50);
	insere_v2(&raiz, 25);
	insere_v2(&raiz, 10);
	insere_v2(&raiz, 30);
	insere_v2(&raiz, 75);  
	insere_v2(&raiz, 60);
	insere_v2(&raiz, 76);
	insere_v2(&raiz, 67);
	insere_v2(&raiz, 80);
	insere_v2(&raiz, 90);
	insere_v2(&raiz, 79);
	imprime_v1(raiz);
	printf("\n");
	int altura=calcula_altura(raiz);
	printf("%d hello world", altura);
	return 0;
}
