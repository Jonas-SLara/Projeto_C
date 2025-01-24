/*LISTA DUPLAMENTE ENCADEADA com elementos ordenados em ordem crescente 
a mediada em que são inseridos */
#include <stdio.h>
#include <stdlib.h>
struct pessoas{
	char nome[20];
	int idade;
	struct pessoas *next;
	struct pessoas *bef;
};
typedef struct pessoas lista;

//função para buscar o elemento sucessor
lista *busca(lista *HEAD, int N){
	lista *p=HEAD;
	while(p!=NULL && N>p->idade){
		p=p->next;
	}
	return p;
}

//função para printar lista
void printIdades(lista *HEAD){
	fflush(stdin);
	lista *q=HEAD;
	while(q!=NULL){
		printf("%s\t", q->nome);
		printf("%d\n", q->idade);
		q=q->next;
	}
	system("pause");
	system("cls");
}

//função para inserir elementos e ordenalos
lista *add(lista *HEAD, int N){
	lista *novo=NULL;
	novo=(lista*)malloc(sizeof(lista));
	novo->idade=N;
	fflush(stdin);
	printf("nome: ");
	gets(novo->nome);
	if(HEAD==NULL){//apenas o primeiro elemento inserido desta forma
		novo->bef=NULL;
		novo->next=NULL;
		HEAD=novo;
		return HEAD;//para a execução aqui
	}
	//parte de orndenar
	lista *p=busca(HEAD, N);
	if(p==HEAD){//ficara à esquerda do primeiro nó e sera o novo HEAD
		novo->next=HEAD;
		HEAD->bef=novo;
		HEAD=novo;
		return HEAD;
	}
	else if(p==NULL){//ficara à direita do último elemento
		lista *q = HEAD;
		while(q->next!=NULL){
			q=q->next;
		}
		q->next=novo;
		novo->bef=q;
		novo->next=NULL;
		return HEAD;
	}
	else{//o elemento ficara entre dois nós
		novo->bef=p->bef;
		p->bef=novo;
		novo->bef->next=novo;
		novo->next=p;
		return HEAD;
	}
}
int main(){
	lista *H=NULL;
	H=add(H, 12);
	H=add(H, 6);
	H=add(H, 10);
	H=add(H, 18);
	H=add(H, 27);
	H=add(H, 21);
	H=add(H, 5);
	H=add(H, 14);
	printIdades(H);
	return 0;
}
 
