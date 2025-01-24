#include <stdio.h>
#include <stdlib.h>
/*lista duplamente encadeada com funcoes para adicionar elementos, 
buscar na lista, imprimir na ordem normal ou inversa, remover elementos
da lista, concatenar 2 listas*/
struct dados{
	int value;
	struct dados* next;
	struct dados* ant;
};
typedef struct dados dados;
dados* buscaDL(dados* L, int y){//retorna o primeiro endereço onde ha este valor y
	dados* p=L;
	while(p!=NULL && p->value!=y){
		p=p->next;
	}
	if(p==NULL){
		return NULL;
	}
	else{
		return p;
	}
}
dados* addDL(dados* L, int x){
	dados* novo=NULL;
	novo=(dados*)malloc(sizeof(dados));//aloca
	novo->next=L;//aponta para o nó cabeçã anterior
	novo->value=x;
	novo->ant=NULL;
	if(novo->next==NULL){//apenas o primeiro sera inicializado assim
		novo->ant=NULL;
		return novo;//sera guardodo no ponteiro para o head da lista
	}
	L->ant=novo;//o nó anterior aponta para novo nó
	return novo;
}
void printDL(dados* L){//imprime na ordem normal
	dados* p=L;
	while(p!=NULL){
		printf("endereco: %x\n", p);
		printf("proximo: %x\n", p->next);
		printf("anterior: %x\n", p->ant);
		printf("value: %d\n\n", p->value);
		p=p->next;
	}
	system("pause");
	system("cls");
}
void printDL_(dados* L){//imprime na ordem inversa
	dados* q=L;
	while(q->next!=NULL){//achou o ultimo elemento
		q=q->next;
	}
	while(q!=NULL){
		printf("endereco: %x\n", q);
		printf("proximo: %x\n", q->next);
		printf("anterior: %x\n", q->ant);
		printf("value: %d\n\n", q->value);
		q=q->ant;
	}
	system("pause");
	system("cls");	
}
dados* delDL(dados*L, int x){//deleta o primeiro a ser encontrado
	dados* p=buscaDL(L, x);
	if(p==NULL){//nao esta na lista
		return L;
	}
	if(p==L){//esta no primeiro nó da lista
		L=L->next;
		L->ant=NULL;
		free(p);
		return L;
	}
	else{//entre dois nós
		p->ant->next=p->next;
		p->next->ant=p->ant;
		free(p);
		return L;
	}
}
void catList(dados* destino, dados* origem){
	//busca o ultimo elemento de onde sera colado
	dados* p=destino;
	while(p->next!=NULL){
		p=p->next;
	}
	//faz o ultimo apontar para o inicio da outra lista e o inicio  da outra para o ultimo
	p->next=origem;
	origem->ant=p;
}

int main(){
	dados* Head=NULL;
	Head=addDL(Head, 1);
	Head=addDL(Head, 2);
	Head=addDL(Head, 3);
	Head=addDL(Head, 4);
	Head=addDL(Head, 5);
	//deleta 2elementos
	Head=delDL(Head, 3);
	Head=delDL(Head, 5);
	printDL(Head);
	printDL_(Head);
	dados* EX=NULL;
	EX=addDL(EX, 20);
	EX=addDL(EX, 30);
	EX=addDL(EX, 40);
	printDL(EX);
	catList(Head, EX);
	printDL(Head);
	printDL_(Head);
	return 0;
}
