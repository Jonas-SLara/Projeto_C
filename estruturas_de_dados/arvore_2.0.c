#include <stdio.h>
#include <stdlib.h>
/* 
	arvore com todas as funções de implementação 
	mais switch case pase testar
*/
typedef struct arvore{
	int info;
	struct arvore *esq;
	struct arvore *dir;
}arv;
/* 
	todas as funções estão composta abaixo da main
*/
void adiciona(arv **r, int num);

void printa(arv *r);

arv *busca(arv *raiz, int x);

arv *busca2(arv *raiz, int x);

int altura(arv *raiz);

int tamanho(arv *r);

int folhas(arv *a);

arv *menor_no(arv *raiz);

arv *maior_no(arv *raiz);

arv *remover(arv *raiz, int x);

int main(){
	arv *raiz=NULL;
	int num;
	char acao;
	do{
		do{	
			printf("***** arvores c++ *****\n\n");
			printf("a(adiciona) h(altura) p(printa) b(buscar)\n");
			printf("t(tamanho) r(remover) x(sair)\n");
			fflush(stdin);
			scanf("%c", &acao);
			system("cls");	
		}while(acao != 'a'&& acao!='h'&&acao!='p'&& acao!='x'
		&&acao!='b'&&acao!='t' && acao!='r');
		
		switch(acao){
			case 'a':
				scanf("%d", &num);
				adiciona(&raiz, num);
				break;	
			case 'p':
				printa(raiz);
				break;
			case 'h':
				printf("\na altura da arvore: %d\n", altura(raiz));
				break;
			case 'b':
				scanf("%d", &num);
				arv *aux=busca(raiz, num);
				if(aux==NULL){
					printf("nao encontrado\n");
				}
				else{
					printf("valor encontrado em: %x\n", aux);
				}
				break;
			case 't':
				printf("quantidade de elementos: %d\n", tamanho(raiz));
				break;
			case 'r':
				scanf("%d", &num);
				raiz=remover(raiz, num);
				break;	
		}
		system("pause");
		system("cls");
	}while(acao!='x');
	return 0;
}

void adiciona(arv **r, int num){//recursiva sem retorno
	if(*r==NULL){
		 *r=(arv*)malloc(sizeof(arv));
		(*r)->dir=NULL;
		(*r)->esq=NULL;
		(*r)->info=num;
	}
	else{
		if(num < (*r)->info)
			adiciona(&((*r)->esq), num);
		else
			adiciona(&((*r)->dir), num);
	}
}

void printa(arv *r){
	if(r!=NULL){
		printf("%d ", r->info);
		printf("<");
		printa(r->esq);
		printf(">");
		printa(r->dir);
	}
}

arv *busca(arv *raiz, int x){
//versão de busca recursiva sem menor ou maior
	if(raiz==NULL)
		return NULL;
	if(raiz->info==x)
		return raiz;
	arv *aux=busca(raiz->esq, x);
	if(aux!=NULL){
		return aux;
	}else{
		return busca(raiz->dir, x);
	}
}

arv *busca2(arv *raiz, int x){
//versão de busca recursiva com menor ou maior
	if(raiz==NULL)
		return NULL;
	if(x==raiz->info)
		return raiz;
	if(x<raiz->info)
		return busca2(raiz->esq, x);
	if(x>raiz->info)
		return busca2(raiz->dir, x);
}

int altura(arv *raiz){
	if(raiz==NULL){
		return -1;
	}
	int sub_esq=altura(raiz->esq);
	int sub_dir=altura(raiz->dir);
	if(sub_esq>sub_dir)
		return sub_esq + 1;
	else
		return sub_dir + 1;
}

int tamanho(arv *r){//retorna  a quantidade de nos
	if(r==NULL)
		return 0;
	else
		return 1+tamanho(r->esq)+tamanho(r->dir);
}

int folhas(arv *a){//numero de nós folhas
	if(a==NULL)
		return 0;
	if(a->dir==NULL && a->esq==NULL)
		return 1;
	return folhas(a->esq)+folhas(a->dir);
}

arv *menor_no(arv *raiz){//encontrar o menor nó recursiva
	if(raiz->esq==NULL)//caso base
		return raiz;
	else
		return menor_no(raiz->esq);
}

arv *maior_no(arv *raiz){//encontrar o maior nó
	if(raiz->dir==NULL)//caso base
		return raiz;
	else
		return maior_no(raiz->dir);
}

arv *remover(arv *r, int x){
	if(r==NULL)
		return NULL;
	else if(x < r->info)
		r->esq=remover(r->esq, x);
	else if(x > r->info)
		r->dir=remover(r->dir, x);
	else{//x==raiz->info
		//caso não tenha filhos ou tem 1 filho
		if(r->dir==NULL || r->esq==NULL){
			arv *temp=(r->esq!=NULL)? r->esq: r->dir;
			free(r);
			return temp; //se for no folha temp=NULL=r->dir
		}
		else{
			arv *temp=r->dir;
			temp=menor_no(temp);
			r->info=temp->info;
			r->dir=remover(r->dir, x);
		}
	}
	return r;
}

