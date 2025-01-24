#include <stdio.h>
#include <stdlib.h>
struct pilha{
	int num;
	struct pilha *acima;
};
typedef struct pilha pilha;

void push(pilha**base, int num){
	pilha *novo=(pilha*)malloc(sizeof(pilha));
	novo->acima=NULL;
	novo->num=num;
	pilha *topo = *base;
	//
	if(topo==NULL){
		*base=novo;
	}else{
		while(topo->acima!=NULL){
			topo=topo->acima;
		}
		topo->acima=novo;
	}
}

void printa(pilha *base){
	pilha *temp = base;
	while(temp!=NULL){
		printf("%d\n", temp->num);
		temp=temp->acima;
	}
}

pilha *inverter(pilha *base){
	pilha *nova_base=NULL;
	pilha *topo;
	pilha *sub_topo;
	pilha *topo2;
	while(base!=NULL){//enquanto haver elementos na pilha, muda-los
		//inicializando variaveis a cada execução
		topo=base;
		sub_topo=NULL;
		
		while(topo->acima!=NULL){
			sub_topo=topo;
			topo=topo->acima;
		}
		//primeiro elemento
		if(nova_base==NULL){
			nova_base=topo;//inicia a nova pilha com o topo da outra
			topo2=nova_base;
			sub_topo->acima=NULL;//tira o ultimo elemento da outra
			
		}else{
			if(topo!=base){//então o subtopo não é NULL
				sub_topo->acima=NULL;
				topo2->acima=topo;
				topo2=topo;
			}
			if(topo==base){
				topo2->acima=topo;
				base=NULL;
			}
		}
		
	}
	return nova_base;
}

int main(){
	pilha *base = NULL;
	push(&base, 7);
	push(&base, 20);
	push(&base, 31);
	push(&base, 43);
	push(&base, 6);
	push(&base, 15);
	push(&base, 38);
	base = inverter(base);
	printa(base);
	return 0;
}
