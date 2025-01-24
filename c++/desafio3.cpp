//usar colorkey setcolormode e explorar o uso de sprites para criar uma animaçao
//usar classes e objetos para o algoritmo
//deve haver um fade out com uma transição de imagens ao pressionar uma tecla
//devera ter color mode com alguma leitura de teclado

#include <iostream>
#include <SDL.h>
#include <string>

#define ALTURA 640
#define LARGURA 384
class Janela{
	private:
		SDL_Window *janela;
		SDL_Renderer *render;
	public:
		Janela(); //inicia o SDL e uma janela e o render
		~Janela(); //desaloca a memoria e encerra o SDL
		SDL_Renderer *ObterRender();
		SDL_Window *ObterJanela();
};

Janela::Janela(){
	janela = nullptr;
	render = nullptr;
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		std::cout<<"falha ao iniciar sdl "<<SDL_GetError()<<'\n';
	}
	else{
		janela = SDL_CreateWindow("",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGURA, ALTURA, SDL_WINDOW_SHOWN);
		if(janela==nullptr){
			std::cout<<"falha ao criar janela "<< SDL_GetError()<<'\n';
		}
		else{
			render = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);
		}
	}
	std::cout<<"construtor da Janela"<<'\n';
}

Janela::~Janela(){
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(janela);
	SDL_Quit();
	std::cout<<"Destruidor de Janela"<<'\n';
}

SDL_Window * Janela::ObterJanela(){
	return janela;
}
SDL_Renderer * Janela::ObterRender(){
	return render;
}

class Textura{
	private:
		SDL_Texture *textura;
		int A_imagem;
		int L_imagem;
	public:
		Textura();
		~Textura();
		bool carregarNovaTextura(std::string path, SDL_Renderer *r);//cria um ponteiro para uma textura de uma imagem no caminho tal
		void renderizarTextura(SDL_Renderer *r, SDL_Rect *orig, SDL_Rect *dest);//renderizar textura nas coordenadas x e y
		void limpar();
		int ObterAlturaImagem();
		int ObterLarguraImagem();
		void escolherCor(Uint8 r, Uint8 g, Uint8 b);
		void setarBlendMode(SDL_BlendMode modo);
		//escolhe o modo de mesclagem pode ser SDL_BLENDMODE_NONE SDL_BLENDMODE_BLEND por exemplo
		void escolherAlpha(Uint8 alpha);
		//escolhe valor alpha para textura que esta mesclada
};

Textura::Textura(){
	A_imagem=0;
	L_imagem=0;
	textura=nullptr;
	std::cout<<"construtor de Textura"<<'\n';
}

void Textura::limpar(){
		if(textura != nullptr){
			L_imagem=0;
			A_imagem=0;
			SDL_DestroyTexture(textura);
			textura=nullptr;
		}
}

Textura::~Textura(){
	limpar();
	std::cout<<"destruidor de textura"<<'\n';
}

int Textura::ObterAlturaImagem(){
	return A_imagem;
}
int Textura::ObterLarguraImagem(){
	return L_imagem;
}

bool Textura::carregarNovaTextura(std::string path, SDL_Renderer *r){
	//limpar a antiga textura para não haver vazamento de memoria
	limpar();
	SDL_Surface *s=nullptr;
	s=SDL_LoadBMP(path.c_str());
	if(s==nullptr){
		std::cout<<"falha ao carregar imagem de: "<<path<<" "<<SDL_GetError()<<'\n';
		return false;
	}
	//usar o color key para limpar pixels na cor branca de fundo
	//esta função define um pixel como transparente quando houver o blit
	SDL_SetColorKey(s, SDL_TRUE, SDL_MapRGB(s->format, 255, 255, 255));
	textura = SDL_CreateTextureFromSurface(r, s);
	if(textura==nullptr){
		std::cout<<"falha ao carregar textura "<<SDL_GetError()<<'\n';
		SDL_FreeSurface(s);
		return false;
	}
	A_imagem=s->h;
	L_imagem=s->w;
	SDL_FreeSurface(s);
	std::cout<<"textura criada no end: "<<textura<<'\n';
	return true;
}
	
void Textura::renderizarTextura(SDL_Renderer *r, SDL_Rect *orig, SDL_Rect *dest){
	//caso o ponteiro para o quadro de origem seja nulo, toda imagem sera renderizada no dest
	SDL_RenderCopy(r, textura, orig, dest);
}

void Textura::escolherCor(Uint8 r, Uint8 g, Uint8 b){//modular textura com setColor
	SDL_SetTextureColorMod(textura, r, g, b);
}

void Textura::setarBlendMode(SDL_BlendMode modo){
	SDL_SetTextureBlendMode(textura, modo);
}

void Textura::escolherAlpha(Uint8 alpha){
	SDL_SetTextureAlphaMod(textura, alpha);
}

Uint8 transicaoAlpha(Uint8 a, bool aumentar, int variacao){
		if(aumentar){
			a = (a+variacao > 255)? 255 : a+variacao ;
		}
		else{
			a = (a-variacao < 0)? 0 : a-variacao ;
		}
		return a;
}

int main(int argc, char *argv[]){
	Janela tela;
	Textura fundo;
	Textura outro_fundo;
	Textura ob1;
	SDL_Rect quadro[4];
	//dividir os quadros de acordo com a imagem 64X64 0.bmp
	quadro[0].x=0;//linha 1 coluna 1
	quadro[0].y=0;
	quadro[0].w=32;
	quadro[0].h=32;
	quadro[1].x=32;//linha 1 coluna 2
	quadro[1].y=0;
	quadro[1].w=32;
	quadro[1].h=32;
	quadro[2].x=0;//linha 2 coluna1
	quadro[2].y=32;
	quadro[2].w=32;
	quadro[2].h=32;
	quadro[3].x=32;//linha 2 coluna 2
	quadro[3].y=32;
	quadro[3].w=32;
	quadro[3].h=32;
	
	fundo.carregarNovaTextura("bmp/1.bmp", tela.ObterRender());
	//cria e mescla com uma outra textura de fundo
	outro_fundo.carregarNovaTextura("bmp/5.bmp", tela.ObterRender());
	outro_fundo.setarBlendMode(SDL_BLENDMODE_BLEND);
	ob1.carregarNovaTextura("bmp/0.bmp", tela.ObterRender());
	//area para quadro de destino
	SDL_Rect dest = {LARGURA/2 -16, ALTURA -96, 64, 64};
	
	bool sair = false;
	SDL_Event e;
	int frame=0;
	//criar variaveis para definir a modulaçao de cores e o valor alpha para a mesclagem
	Uint8 r=0, g=0, b=0, a=255;
	bool adFrame=true, adAlpha=false;
	if(tela.ObterJanela()==nullptr || tela.ObterRender()==nullptr ){
		sair=true;
	}
	
	while(!sair){
		while(SDL_PollEvent(&e)!=0){
			if(e.type==SDL_QUIT){
				sair=true;
			}
			//capturar entradas das teclas para aumentar ou dimuir cores do fundo
			else if(e.type=SDL_KEYDOWN){
				switch(e.key.keysym.sym){
					case SDLK_r:
						if(SDL_GetModState() & KMOD_SHIFT){
							r--;
						}
						else{
							r++;
						}
					break;
					case SDLK_g:
						if(SDL_GetModState() & KMOD_SHIFT){
							g--;
						}
						else{
							g++;
						}
					break;
					case SDLK_b:
						if(SDL_GetModState() & KMOD_SHIFT){
							b--;
						}
						else{
							b++;
						}
					break;
					case SDLK_a:
						a=transicaoAlpha(a, adAlpha, 5);
						if(a==0 || a==255){
							adAlpha=!adAlpha;
						}
						
					break;
				}
			}
		}
		SDL_SetRenderDrawColor(tela.ObterRender(), 10, 20, 35, 255);
		SDL_RenderClear(tela.ObterRender());
		//renderizar fundo 
		fundo.renderizarTextura(tela.ObterRender(), nullptr, nullptr);
		fundo.escolherCor(r, g, b);
		outro_fundo.escolherAlpha(a);
		outro_fundo.renderizarTextura(tela.ObterRender(), nullptr, nullptr);
		//selecionar qual parte (quadro) do sprite sera renderizado
		ob1.renderizarTextura(tela.ObterRender(), &quadro[frame], &dest);
		SDL_RenderPresent(tela.ObterRender());
		SDL_Delay(100);
		
		frame = (adFrame)? frame+1 : frame-1;
		adFrame = (frame==0 || frame==3)? !adFrame: adFrame;
	}
	return 0;
}