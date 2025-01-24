#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*listas encadeadas (sequencial)*/
//imprimente uma função que copie uma lista encadeada
//uma funcão que adicione elementos no fim da lista
//uma função que concatene 2 listas encadeadas
//remova itens desta lista e sempre apresente dados na tela com uma função
struct Livros{
	int paginas;
	char nome[20];
	int code;
	struct Livros* next;	
};
typedef struct Livros lista;
lista* add(lista* L){
	lista *novo;
	novo=(lista*)malloc(sizeof(lista));
	printf("\nnome do livro: ");
	fflush(stdin);
	gets(novo->nome);
	printf("paginas do livro: ");
	scanf("%d", &novo->paginas);
	printf("\ncodigo do livro: ");
	scanf("%d", &novo->code);
	novo->next = L;
	system("cls");
	return novo;
}
void printL(lista* L){
	lista* p;
	p=L;
	while(p!=NULL){
		printf("nome: %s\n", p->nome);
		printf("paginas: %d\n", p->paginas);
		printf("codigo: %d\n", p->code);
		printf("endereco: %x\n", p);
		printf("aponta para: %x\n\n", p->next);
		p=p->next;
	}
	system("pause");
	system("cls");
}
lista* del(lista* L, int code){
	lista* p=L;//p(endereco atual)
	lista* q=NULL;//q(endereco anterior)
	while(p!=NULL && p->code!=code){
		q=p;
		p=p->next;
	}
	printf("\n%x foi achado\n", p);
	if(p==NULL){//nenhum
		return L;
	}
	if(p==L){//primeiro(cabeca)
		L=p->next;
		free(p);
	}
	else{//do meio ou fim
		q->next=p->next;
		free(p);
	}
	return L;
}
lista* cpy(lista* L, lista* cpyL){//L é origem e cpyL é o destino, é cpy que sera retornado como nó cabeça
	lista *p=L;
	lista *novo=NULL;
	while(p!=NULL){//enquanto estiver lendo elementos de L apartir de p copie para novo
		novo=(lista*)malloc(sizeof(lista));
		novo->code= p->code;
		novo->paginas= p->paginas;
		strcpy(novo->nome, p->nome);//nescessaria para copiar strings de um endereço para outro
		novo->next=cpyL;//no primeiro elemento cpyL é NULL, defina na main
		cpyL=novo;
		p=p->next;
	}
	return cpyL;
}
void addLast(lista* Head){
	lista* end=Head;//objetivo é procurar o endereço do ultimo elemento e guardalo em l
	while(end->next!=NULL){
		end=end->next;
	}
	lista* novo=NULL;
	novo=(lista*)malloc(sizeof(lista));
	printf("\nnome do livro: ");
	fflush(stdin);
	gets(novo->nome);
	printf("paginas do livro: ");
	scanf("%d", &novo->paginas);
	printf("\ncodigo do livro: ");
	scanf("%d", &novo->code);
	//apos etapa de criação do nó o ultimo elemento passa a aponta para novo e não para NULL
	end->next=novo;
	novo->next=NULL;
}
void catList(lista*L, lista*cola){//cola se refere a um no head de outra lista
	//achar o ultimo nó de L e fazelo apontar para o nó cola
	lista*p=L;
	while(p->next!=NULL){
		p=p->next;
	}
	p->next=cola;
}
int main(){
	lista* L=NULL;
	char insere, remove;
	int code;
	printf("deseja adicionar um livro s(sim) n(nao)");
	scanf("%c", &insere);	
	while(insere=='s' || insere=='l'){//testando a funcão add e addLast
		if(insere=='s'){
			L=add(L);	
		}
		else{
			addLast(L);
		}
		printf("deseja adicionar novo livro no inico s(sim) no final l(last) n(nao)\n");
		fflush(stdin);
		scanf("%c", &insere);
	}
	printL(L);//exibe  todos os adicionados
	printf("deseja remover elementos da lista: s(sim) !s(nao)\n");
	fflush(stdin);
	scanf("%c", &remove);
	while(remove=='s'){//testando a função del (deleta um nó)
		printf("codigo do livro:   ");
		scanf("%d", &code);
		L=del(L, code);
		printL(L);//a cada remoção é mostrado os nós restantes
		printf("deseja remover elementos da lista: s(sim) !s(nao)\n");
		fflush(stdin);
		scanf("%c", &remove);
	}
	lista* cpyL=NULL;//copia a lista restante com a função cpy e exibe
	cpyL=cpy(L, cpyL);
	printL(cpyL);
	catList(L, cpyL);
	printL(L);
	return 0;
}

