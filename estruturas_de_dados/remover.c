#include <stdio.h>
#include <stdlib.h>

typedef struct arvore{
	int info;
	struct arvore *esq;
	struct arvore *dir;
}arv;

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
		printa(r->esq);
		printa(r->dir);
	}
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

arv *remover(arv *r, int x){//r é a raiz e x o valor a ser removido
	if(r==NULL)
		return NULL;
		
	else if(x < r->info)
		r->esq=remover(r->esq, x);
		
	else if(x > r->info)
		r->dir=remover(r->dir, x);
		
	else{//r->info==x
		//caso1 no folha
		if(r->dir==NULL && r->esq==NULL){
			free(r);
			return NULL;
		}
		//caso2 com 1 filho a esquerda
		if(r->esq!=NULL && r->dir==NULL){
			arv *temp=r->esq;
			free(r);
			return temp;
		}
		//caso3 com 1 filho a direita
		if(r->dir!=NULL && r->esq==NULL){
			arv *temp=r->dir;
			free(r);
			return temp;
		}
		//caso 4 com 2 filhos
		else{
			arv *sub_esq=r->esq;//sub arvore da esquerda
			arv *sub_dir=r->dir;//sub arvore da direita
			if(sub_esq->dir!=NULL){
				//encontrar o nó mais a direita da sub-arvore da esquerda
				arv *temp=sub_esq;
				while(temp->dir!=NULL){
					temp=temp->dir;
				}
				r->info=temp->info;
				r->esq=remover(r->esq, temp->info);
			}
			else if(sub_dir->esq!=NULL){
				//econcontrar o nó mais a esquerda da subarvore da direita
				arv *temp=sub_dir;
				while(temp->esq!=NULL){
					temp=temp->esq;
				}
				r->info=temp->info;
				r->dir=remover(r->dir, temp->info);
			}
			else{
				//substitui pela subarvore a esquerda da raiz
				r->info=sub_esq->info;
				r->esq=remover(r->esq, sub_esq->info);
			}
		}
	}
	return r;
}

arv *remover2(arv *r, int x){
	if(r==NULL)
		return NULL;
	else if(x < r->info)
		r->esq=remover2(r->esq, x);
	else if(x > r->info)
		r->dir=remover2(r->dir, x);
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
			r->dir=remover2(r->dir, temp->info);
		}
	}
	return r;
}

int main(){
	arv *r=NULL;
	adiciona(&r, 10);
	adiciona(&r, 7);
	r=remover2(r, 7);
	printa(r);
	return 0;
}
