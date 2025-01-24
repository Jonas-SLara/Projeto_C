#include <iostream>
#include <SDL.h>
#include <string>
#define W 600
#define H 400
//g++ ./render_texture.cpp -I SDL2/x86_64-w64-mingw32/include/SDL2/ -L SDL2/x86_64-w64-mingw32/lib/ -lmingw32 -lSDL2main -lSDL2

bool iniciar(SDL_Window **janela, SDL_Renderer **renderizador)
{
	*janela=SDL_CreateWindow("renderizador e texturas", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN);
	if(janela==nullptr){
		return false;
	}
	*renderizador = SDL_CreateRenderer(*janela, -1, SDL_RENDERER_ACCELERATED);
	//-1 indica que o sdl escolhera o driver grafico e o ultimo parametro usara aceleraçao de hardware
	if(renderizador==nullptr){
		return false;
	}
	//iniciar uma cor para o renderizador
	SDL_SetRenderDrawColor(*renderizador, 18, 59, 66, 255);
	return true;
}

SDL_Texture *CarregarTexturaImagem(std::string caminho, SDL_Renderer *renderizador){
	SDL_Surface *surface = nullptr;
	surface = SDL_LoadBMP(caminho.c_str());
	if(surface == nullptr){
		return nullptr;
	}
	SDL_Texture *Imagem_Fundo = nullptr;
	Imagem_Fundo = SDL_CreateTextureFromSurface(renderizador, surface);
	SDL_FreeSurface(surface);
	return Imagem_Fundo;
}

void DefinirRect(SDL_Rect *r, int x, int y, int w, int h){
	r->x=x;
	r->y=y;
	r->w=w;
	r->h=h;
}


void terminar(SDL_Window **janela, SDL_Renderer **renderizador, SDL_Texture **fundo){
		SDL_DestroyTexture(*fundo);
		*fundo=nullptr;
		SDL_DestroyRenderer(*renderizador);
		*renderizador = nullptr;
		SDL_DestroyWindow(*janela);
		*janela = nullptr;
		SDL_Quit();
}

int main(int argc, char *argv[])
{	
	SDL_Window *janela = nullptr;
	SDL_Renderer *renderizador = nullptr;
	SDL_Texture *fundo = nullptr;
	
	if(!(iniciar(&janela, &renderizador))){
		std::cout << "erro ao iniciar o programa, " << SDL_GetError() << '\n';
		return 1;
	}
	
	fundo = CarregarTexturaImagem("bmp/6.bmp", renderizador);
	if(fundo==nullptr){
		std::cout<<"erro ao carregar imagem, " << SDL_GetError() << '\n';
		return 1;
	}
	
	SDL_Rect ret;
	DefinirRect(&ret, W-300, H-300, 300, 300);
	
	//ciclo principal
	SDL_Event e;
	bool sair = false;
	while(!sair)
	{
		while(SDL_PollEvent(&e)!=0){
			if(e.type==SDL_QUIT){
				sair=true;
			}
		}
		
		SDL_RenderClear(renderizador);
		SDL_RenderCopy(renderizador, fundo, nullptr, &ret);
		SDL_RenderPresent(renderizador);
	}
	terminar(&janela, &renderizador, &fundo);
	return 0;
}