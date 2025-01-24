#include <iostream>
#include <SDL.h>
#define TELA_LARGURA 800
#define TELA_ALTURA 500

typedef struct Linha{
	int xp1;
	int yp1;
	int xp2;
	int yp2;
}Linha;

void DefinirRet(SDL_Rect *r, int x, int y, int w, int h){
	r->x=x;
	r->y=y;
	r->w=w;
	r->h=h;
}

Linha *criarLinha(int x1, int y1, int x2, int y2){
	Linha *l=nullptr;
	l=(Linha*)malloc(sizeof(Linha));
	l->xp1=x1;
	l->yp1=y1;
	l->xp2=x2;
	l->yp2=y2;
	return l;
}


int main(int argc, char *argv[]){
	SDL_Window *tela = nullptr;
	SDL_Renderer *renderizador = nullptr;
	//iniciar sdl
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		return 1;
	}
	//criar tela
	tela = SDL_CreateWindow("", 100, 200, TELA_LARGURA, TELA_ALTURA, SDL_WINDOW_SHOWN);
	if(tela==nullptr){
		std::cout << "falha ao iniciar janela " << SDL_GetError() <<'\n';
		return 1;
	}
	//criar renderizador
	renderizador = SDL_CreateRenderer(tela, -1, SDL_RENDERER_ACCELERATED);
	if(renderizador == nullptr){
		std::cout << "falha ao criar renderizador" << SDL_GetError() <<'\n';
		return 1;
	}
	//criando o loop principal
	SDL_Event e;
	bool continuar = true, diminuirR=true, diminuirLinha=true;
	int R=50, fimLinha = TELA_LARGURA;
	//formas geometricas
	SDL_Rect r1;
	Linha* l=criarLinha(0, TELA_ALTURA/2, TELA_LARGURA, TELA_ALTURA/2);
	
	while(continuar){
			while(SDL_PollEvent(&e)!=0){
				if(e.type==SDL_QUIT){
					continuar = false;
				}
			}
			//desenhar fundo branco
			SDL_SetRenderDrawColor(renderizador, R, 30, 100, 255);
			SDL_RenderClear(renderizador);
			//desenhar quadrado escuro no meio da tela
			SDL_SetRenderDrawColor(renderizador, R, R, R, 255);
			DefinirRet(&r1, TELA_LARGURA/2 - 50, TELA_ALTURA/2 -50, 100, 100);
			SDL_RenderFillRect(renderizador, &r1);
			//desenha borda braca nele
			SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 255);
			SDL_RenderDrawRect(renderizador, &r1);
			//desenhar linha branca
			SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 255);
			SDL_RenderDrawLine(renderizador, l->xp1, l->yp1, fimLinha, l->yp2);
			SDL_Delay(10);
			SDL_RenderPresent(renderizador);
			//realizar transiçoes do roxo
			R = (diminuirR)? R-1:R+1;
			diminuirR = (R==0 || R==100)? !diminuirR: diminuirR;
			fimLinha = (diminuirLinha)? fimLinha-1:fimLinha+1;
			diminuirLinha = (fimLinha==0 || fimLinha==TELA_LARGURA)? !diminuirLinha: diminuirLinha;
	}
	//fechar sdl
	SDL_DestroyRenderer(renderizador);
	SDL_DestroyWindow(tela);
	SDL_Quit();
	return 0;
}