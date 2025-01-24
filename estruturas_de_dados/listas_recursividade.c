//função recursiva para verificar se não há elementos repetidos em uma lista
//ao inserir sera analisado caso ha um já existente
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct nomes{
	char nome[20];
	struct nomes *next;
	struct nomes *bef;
};
typedef struct nomes nomes;

nomes *busca(nomes *HEAD, char x[20]){
	nomes *p =HEAD;
	//quando encontrar ou quando chegar em NULL para de procurar
	if(p==NULL || strcmp(p->nome, x)==0){
		return p;
	}
	else{
		p=busca(p->next, x);
		return p;
	}
}

nomes *add(nomes *HEAD){
	system("cls");
	printf("***inserindo dados***\n\n");
	nomes *novo=NULL;
	novo=(nomes*)malloc(sizeof(nomes));
	novo->next=HEAD;
	novo->bef=NULL;
	//alocando un endereço e dando um nome
	fflush(stdin);
	gets(novo->nome);
	//buscar se há elemento repetidos, 
	nomes *q =busca(HEAD, novo->nome);
	if(q!=NULL){
		printf("este elemento já foi inserido\n");
		free(novo);
		return HEAD;//para aqui
	}
	if(HEAD!=NULL){
		HEAD->bef=novo;
	}
	HEAD=novo;
	char option;
	printf("s(inserir) n(parar)\n");
	scanf("%c", &option);
	if(option=='s'){
		HEAD=add(HEAD);
		return HEAD;
	}
	return HEAD;
}

void print(nomes *HEAD){
	nomes *p = HEAD;
	if(p!=NULL){
		printf("endereco: %x\n", p);
		printf("nome: %s\n", p->nome);
		printf("next: %x\n", p->next);
		printf("bef: %x\n\n", p->bef);
		print(p->next);//recursividade
	}
}

nomes *del(nomes *HEAD){
	system("cls");
	printf("***deletanto dados***\n\n");
	printf("nome do elemento: ");
	fflush(stdin);
	char nome[20];
	gets(nome);
	nomes *q =busca(HEAD, nome);
	if(q==NULL){
		printf("\nnenhum encontrado\n");
		system("pause");
		system("cls");
		return HEAD;
	}
	else if(q==HEAD){//primeiro elemento vai ser deletado
		HEAD=q->next;
		free(q);
		HEAD->bef=NULL;
	}
	else if(q->next==NULL){//ultimo
		q->bef->next=NULL;
		free(q);
	}
	else{//aleatorio
		q->next->bef=q->bef;
		q->bef->next=q->next;
		free(q);
	}
	char option;
	printf("continuar deletando? s(sim) n(nao)");
	fflush(stdin);
	scanf("%c", &option);
	if(option=='s'){
		HEAD=del(HEAD);
		return HEAD;
	}
	system("cls");
	return HEAD;
}
int main(){
	nomes *H=NULL;
	char option;
	//
	printf("s(inserir) n(parar)\n");
	fflush(stdin);
	scanf("%c", &option);
	H = (option=='s')? add(H): H;
	//
	print(H);
	//
	printf("s(deletar) n(parar)\n");
	fflush(stdin);
	scanf("%c", &option);
	H = (option=='s')? del(H): H;
	//
	print(H);
	
	return 0;
}
