#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct pilha{
	char info;
	struct pilha *prox;
};

typedef struct pilha pilha;

void push(pilha **base, char info){
	
	pilha *novo =(pilha*)malloc(sizeof(pilha));
	novo->info=info;
	novo->prox=NULL;
	
	if(*base==NULL){//primeiro elemento
		*base=novo;
	}
	else{//demais elementos inseridos no final
		pilha *topo = *base;
		while(topo->prox!=NULL){
			topo=topo->prox;
		}
		topo->prox=novo;
	}
}

void pop(pilha **base){//remove o ultimo elemento da pilha
	pilha *topo = *base;
	pilha *temp;//se refere ao elemento abaixo do topo
	
	if(*base!=NULL){//remove somente se a pilha não estiver vazia
		while(topo->prox!=NULL){
			temp=topo;
			topo=topo->prox;
		}
		
		if(*base==topo){//caso a pilha só tem 1 elemento
			free(topo);
			*base=NULL;
		}
		else{//o topo esta acima de pelo menos 1 elemento
			free(topo);
			temp->prox=NULL;
		}
	}
}

int valida(char conta[30]){//função para validar expressões algebricas
	pilha *base = NULL;
	int tamanho = strlen(conta), i;
	for(i=0; i<tamanho; i++){
		if(conta[i]==')' && base==NULL){
			return 1;//false
		}
		if(conta[i]=='('){
			push(&base, '(');
		}
		if(conta[i]==')'){
			pop(&base);
		}
	}
	if(base==NULL){
		return 0;//true
	}
	return 1;
}

void inv_pilha(){//ler e inverter uma pilha

}
void print_pilha(pilha *base){
	pilha *temp = base;
	while(temp!=NULL){
		printf("%c", temp->info);
		temp = temp->prox;
	}
}
int main(){
	char conta[30];
	gets(conta);
	int res = valida(conta);
	printf("\n%d", res);
	return 0;
}

