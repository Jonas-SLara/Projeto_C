/*
	Objetivo de implementar ttf, eventos com mouses, renderizar imagens com angulos diferentes
e outras maneiras de obter a entrada do teclado
	Novos recursos: SDL_GetMouseState() SDL_GetKeyboardState() SDL_GetModState()
	SDL_Keycode, SDL_MOUSEMOTION SDL_MOUSEBUTTON_DOWN SDL_MOUSEBUTTON_UP 
	SDLK_CAPSLOCK, SDLK_BACKSPACE, SDLK_RETURN, SDL_Color, SDL_MapRGB(), SDL_Point
	SDL_RENDERER_ACCELERATED SDL_TRUE  SDL_WINDOW_SHOWN SDL_RenderCopyEx()
	TTF_Font TTF_CloseFont TTF_GetError TTF_Init TTF_OpenFont TTF_Quit TTF_RenderText_Solid()

	O Desafio final é criar uma entrada de texto clicavel
*/

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <cctype>

#define LARGURA 640
#define ALTURA	480

enum Sprites_folha1{
	BURACO_NEGRO,
	CORACAO,
	TOTAL_FOLHA1
};

class SDL{//depende das constantes LARGURA E ALTURA para funcionar
	private:
		SDL_Window *janela;
		SDL_Renderer *renderUnico;
	public:
		SDL(){
			janela=nullptr;
			renderUnico=nullptr;
			if(SDL_Init(SDL_INIT_VIDEO)<0){
				std::cout<<"falha ao iniciar "<<SDL_GetError()<<'\n';
				exit(0);
			}
			if(TTF_Init()== -1){
				std::cout<<"falha ao iniciar "<<TTF_GetError()<<'\n';
				exit(0);
			}
		}
		
	bool CriarJanelaRender(const char *titulo, int x, int y, Uint32 flagJ, Uint32 flagR){
		if(janela==nullptr && renderUnico==nullptr){
			janela = SDL_CreateWindow(titulo, x, y, LARGURA, ALTURA, flagJ);
			if(janela==nullptr){
				std::cout<<"erro ao criar janela "<<SDL_GetError()<<'\n';
				return false;
			}
			renderUnico=SDL_CreateRenderer(janela, -1, flagR);
			if(renderUnico==nullptr){
				std::cout<<"erro ao criar render "<<SDL_GetError()<<'\n';
				return false;
			}
			std::cout<<"janela criada"<<'\n';
			return true;
		}
		std::cout<<"nao pode sobescrevelos"<<'\n';
		return false;
	}
	
	SDL_Renderer *GetRender(){
		return renderUnico;
	}
	
	SDL_Window *GetJanela(){
		return janela;
	}
	~SDL(){
		SDL_DestroyRenderer(renderUnico);
		SDL_DestroyWindow(janela);
		janela=nullptr;
		renderUnico=nullptr;
		TTF_Quit();
		SDL_Quit();
		std::cout<<"destruidor de SDL"<<'\n';
	}
};
//classe texto contera um vector de ponteiros dinamicos de linhas de texto
//os quais possuem informaçoes como fonte, textura da frente e do fundo para sombra, dimensoe w y
//estes atributos ficam privados dentro da classe e so podem ser manipulados com funções da classe
typedef struct LinhaDeTexto{
		SDL_Texture *textura;
		SDL_Texture *sombra;//serve para criar o fundo mas por padrao é null
		TTF_Font *fonte;
		int largura;
		int altura;
}LinhaDeTexto;

class Texto{
	private:
		std::vector<LinhaDeTexto *> linhas;
	public:
		bool CriarLinhaDeTexto(const char *conteudo, const char *caminho_fonte, int tam,
		SDL_Color *cor, SDL_Renderer *renderizador){
			//criar nova linha de texto com conteudo
			LinhaDeTexto *novo= new LinhaDeTexto;
			novo->fonte=nullptr;
			novo->textura=nullptr;
			novo->sombra=nullptr;
			novo->fonte=TTF_OpenFont(caminho_fonte, tam);
			if(novo->fonte==nullptr){
				delete novo;
				std::cout<<"falha ao abrir ttf fonte "<<TTF_GetError()<<'\n';
				return false;
			}
			SDL_Surface *tempo =TTF_RenderText_Solid(novo->fonte, conteudo, *cor);
			if(!tempo){
				delete novo;
				std::cout<<"falha ao criar surface de ttf "<<TTF_GetError()<<'\n';
				return false;
			}
			novo->textura=SDL_CreateTextureFromSurface(renderizador, tempo);
			if(novo->textura==nullptr){
				SDL_FreeSurface(tempo);
				delete novo;
				std::cout<<"falha ao criar textura da surface de ttf "<<SDL_GetError()<<'\n';
				return false;
			}
			novo->largura=tempo->w;
			novo->altura=tempo->h;
			SDL_FreeSurface(tempo);
			linhas.push_back(novo);
			std::cout<<"nova linha criada: "<<novo<<" largura: "<<novo->largura<<
			" altura: "<<novo->altura<<'\n';
			return true;
		}
		
		bool CriarLinhaDeTexto_Sombreada(const char *conteudo, const char *caminho_fonte, int tam,
		SDL_Color *cor_texto, SDL_Color *cor_sombra, SDL_Renderer *renderizador){
				LinhaDeTexto *novo=new LinhaDeTexto; 
				novo->textura=nullptr;
				novo->sombra=nullptr;
				novo->fonte=nullptr;
				novo->fonte=TTF_OpenFont(caminho_fonte, tam);
				if(novo->fonte==nullptr){
					std::cout<<TTF_GetError()<<'\n';
					delete novo;
					return false;
				}
				SDL_Surface *s1=nullptr;
				SDL_Surface *s2 = nullptr;
				s1=TTF_RenderText_Solid(novo->fonte, conteudo, *cor_texto);
				s2=TTF_RenderText_Solid(novo->fonte, conteudo, *cor_sombra);
				if(s1==nullptr || s2==nullptr){
					std::cout<<TTF_GetError()<<'\n';
					SDL_FreeSurface(s1);
					SDL_FreeSurface(s2);
					delete novo;
					return false;
				}
				novo->textura=SDL_CreateTextureFromSurface(renderizador, s1);
				novo->sombra=SDL_CreateTextureFromSurface(renderizador, s2);
				if(novo->sombra==nullptr || novo->textura==nullptr){
					std::cout<<SDL_GetError()<<'\n';
					SDL_FreeSurface(s1);
					SDL_FreeSurface(s2);
					delete novo;
					return false;
				}
				novo->largura=s1->w;
				novo->altura=s2->h;
				SDL_FreeSurface(s1);
				SDL_FreeSurface(s2);
				std::cout<<"nova linha criada: "<<novo<<" largura: "<<novo->largura<<" altura: "<<novo->altura<<'\n';
				linhas.push_back(novo);
				return true;
		}
		
		void RemoverLinhaDeTexto(){//remove tanto as simples com as com sombra 
			if(!linhas.empty()){
				LinhaDeTexto *ultima=linhas.back();
				std::cout<<"linha "<<ultima<<" sera deletada"<<'\n';
				if(ultima->textura!=nullptr){
					SDL_DestroyTexture(ultima->textura);
				}
				if(ultima->sombra!=nullptr){
					SDL_DestroyTexture(ultima->textura);
				}
				if(ultima->fonte!=nullptr){
					TTF_CloseFont(ultima->fonte);
				}
				delete ultima;
				linhas.pop_back();
			}
			else{
				std::cout<<"nao ha mais linhas para serem deletadas"<<'\n';
			}
		}
		
		void RemoverTudo(){
			while(!linhas.empty()){
				RemoverLinhaDeTexto();
			}
			std::cout<<"vector de linhas esta vazio"<<'\n';
		}
		
		int GetLargura_Index(int i){
				if(i < linhas.size() && i > -1){
					return linhas.at(i)->largura;
				}
				return -1;
		}
		int GetAltura_Index(int i){
			if(i < linhas.size() && i > -1){
				return linhas.at(i)->altura;
			}
			return -1;
		}
		
		void Renderizar_Index(int i=0, SDL_Renderer *r=nullptr, int x=0, int y=0){
			if(i<linhas.size() && i>-1){
				//desloca a sombra 2px para a direita e para baixo
				SDL_Rect destino = {x+2, y+2, linhas.at(i)->largura, linhas.at(i)->altura};
				SDL_RenderCopy(r, linhas.at(i)->sombra, nullptr, &destino);
				destino.x=x;
				destino.y=y;
				SDL_RenderCopy(r, linhas.at(i)->textura, nullptr, &destino);
			}
			else{
				std::cout<<"esse index ainda nao tem nenhum objeto"<<'\n';
			}
		}
		~Texto(){
			RemoverTudo();
		}
};

class Imagem{
	protected://a classe Botao precis accesae estes metodos
	SDL_Texture * imagem;
	int largura_imagem;
	int altura_imagem;
	
	public:
	virtual void limpar(){
		if(imagem!=nullptr){
			SDL_DestroyTexture(this->imagem);
			largura_imagem=0;
			altura_imagem=0;
		}
	}
	virtual ~Imagem(){
		limpar();
		std::cout<<"instancia de Imagem foi deletada"<<'\n';
	}
	Imagem(): imagem(nullptr), altura_imagem(0), largura_imagem(0){
		std::cout<<"instancia de Imagem criada"<<'\n';
	}
	bool CarregarImagem(const char *caminho_imagem, SDL_Renderer *r){
		limpar();
		SDL_Surface *s = SDL_LoadBMP(caminho_imagem);
		if(!s){
			std::cout<<"erro ao carregar "<<caminho_imagem<<" "<<SDL_GetError()<<'\n';
			return false;
		}
		SDL_SetColorKey(s, SDL_TRUE, SDL_MapRGB(s->format, 255, 255, 255));//cor branca nao sera lida
		imagem=SDL_CreateTextureFromSurface(r, s);
		if(!imagem){
			std::cout<<"erro ao criar textura de "<<caminho_imagem<<" "<<SDL_GetError()<<'\n';
			return false;
		}
		altura_imagem=s->h;
		largura_imagem=s->w;
		SDL_FreeSurface(s);
		std::cout<<"textura "<<imagem<<" criada com sucesso"<<'\n';
		return true;
	}
	virtual void Renderizar(SDL_Renderer *r, SDL_Rect *origem=nullptr, SDL_Rect *destino=nullptr){
		SDL_RenderCopy(r, imagem, origem, destino);
	}
	virtual void RenderizarComAngulo(SDL_Renderer *r, SDL_Rect *origem, SDL_Rect *destino, double angulo, SDL_Point * centro, SDL_RendererFlip modo=SDL_FLIP_NONE){
		//o tipo SDL_RendererFlip indica a maneira que sera espelhado pode ser SDL_FLIP_NONE SDL_FLIP_HORIZONTAL SDL_FLIP_VERTICAL
		//o tipo SDL_Point indica o ponto no qual a textura sera rotacionada, quando null se torna o ponto inferior esquerdo por padrao
		SDL_RenderCopyEx(r, imagem, origem, destino, angulo, centro, modo);
	}

};

//criar uma classe Botao para gerenciar evento do mouse 
class Botao : public Imagem{
	private:
	SDL_Rect *area;//area onde a textura sera renderizada,
	SDL_Point ponto;
	bool borda;
	SDL_Color *corBorda;
	public:
	Botao():Imagem(), area(nullptr), borda(false){
		std::cout<<"instancia de Botao criada"<<'\n';
	}
	~Botao(){
		LimparArea();
		std::cout<<"instancia de Botao destruida"<<'\n';
	}
	void Renderizar(SDL_Renderer *r, SDL_Rect *origem=nullptr){
		//embora seja parecido, ela sempre renderiza na mesma area clicavel do botao
		SDL_RenderCopy(r, imagem, origem, area);
		if(borda){
			SDL_SetRenderDrawColor(r, corBorda->r, corBorda->g, corBorda->b, corBorda->a);
			SDL_RenderDrawRect(r, area);
		}
	}
	void DefinirArea(int x, int y, int w, int h){
		LimparArea();
		SDL_Rect *novo = new SDL_Rect;
		area=novo;
		area->x=x;
		area->y=y;
		area->w=w;
		area->h=h;
		std::cout<<"nova area "<<w<<"X"<<h<<" criada"<<'\n';
	}
	void LimparArea(){
		if(area!=nullptr){
			delete area;
			area=nullptr;
		}
	}
	bool GerenciarMouse(SDL_Event *e){//retorna true se estiver na area clicavel e false se nao
		int px, py;
		if(this->area==nullptr){
			return false;
		}
		else if(e->type == SDL_MOUSEMOTION || e->type==SDL_MOUSEBUTTONDOWN || e->type==SDL_MOUSEBUTTONUP){
			SDL_GetMouseState(&px, &py);
			bool estaNaAreaClicavel = ((px > area->x && px < (area->w + area->x)) && (py > area->y && py < (area->h + area->y)))? true: false;
			return estaNaAreaClicavel;
		}
		return false;
	}
	void SetBorda(SDL_Color *cor){
		if(cor==nullptr){
			borda=false;
			corBorda=cor;
		}else{
			corBorda=cor;
			borda=true;
		}
	}
	void RenderizarComAngulo(SDL_Renderer *r, SDL_Rect *origem, double angulo, SDL_Point * p,
		SDL_RendererFlip modo=SDL_FLIP_NONE){
		SDL_RenderCopyEx(r, imagem, origem, area, angulo, p, modo);
		if(borda){
			SDL_SetRenderDrawColor(r, corBorda->r, corBorda->g, corBorda->b, corBorda->a);
			SDL_RenderDrawRect(r, area);
		}
	}
};

void MoverAngulo(double *ang, bool horario){
	*ang = (horario)? *ang+0.2: *ang -0.2;
	*ang = (*ang>360)? 0 : *ang;
	*ang = (*ang < 0)? 360 : *ang;
}

void carregarSprites_folha1(SDL_Rect *quadros){//imagem bmp com 2quardros 32X32px cada em 2linhas e 1coluna
	int x=0, y=0, i=0;
	while(y<64){
		while(x<32){
			quadros[i]={x, y, 32, 32};
			x=x+32;
			i++;
		}
		x=0; //volta para o inicio da coluna
		y=32+y; //vai para a proxima linha
	}
	std::cout<<"sprites carregados"<<'\n';
}

int main(int argc, char *argv[]){
	//criando texturas e janela e nossa area clicavel(botao)
	SDL tela;
	if(tela.CriarJanelaRender("caixa de texto", 200, 200, SDL_WINDOW_SHOWN,
	SDL_RENDERER_ACCELERATED)==false){
		std::cout<<"nao carregou janela"<<'\n';
		return 1;
	}
	
	Botao img1;
	if(img1.CarregarImagem("bmp/3.bmp", tela.GetRender())==false){
		std::cout<<"nao carregou imagem"<<'\n';
		return 1;
	}
	SDL_Rect Vimg[TOTAL_FOLHA1];
	carregarSprites_folha1(Vimg);
	double angulo=45;
	int I=BURACO_NEGRO;
	SDL_Rect area1 = {(LARGURA - Vimg[I].w*10)/2, (ALTURA - Vimg[I].h*10)/2, Vimg[I].w * 10, Vimg[I].h * 10};
	img1.DefinirArea(area1.x, area1.y, area1.w, area1.h);//toda a area da imagem se torna clicavel
	
	//criando os textos com sombra
	SDL_Color cores[4];
	cores[0]={255, 255, 255, 255};//branco
	cores[1]={0, 0, 0, 255};//preto
	cores[2]={255, 0, 0, 255};//vermelho
	std::string msg = "Buracos Negros estao no centro das Galaxias...";
	std::string msg2 = "No antigo Egito o coracao era o centro do corpo";
	Texto t1;
	if(t1.CriarLinhaDeTexto_Sombreada(msg.c_str(), "ttf/Minecraft.ttf", 18,
	&cores[0], &cores[1], tela.GetRender())== false){
		return 1;
	}
	if(t1.CriarLinhaDeTexto_Sombreada(msg2.c_str(), "ttf/Minecraft.ttf", 18,
	&cores[0], &cores[1], tela.GetRender())==false){
		return 1;
	}
	int J=0;
	
	//renderizando
	bool sair=false;
	SDL_Event e;
	
	//obtento o estado das teclas sem usar eventos
	const Uint8 *listaEstadoAtualDoTeclado= SDL_GetKeyboardState(nullptr);
	while(!sair){
		while(SDL_PollEvent(&e)!=0){
			switch(e.type){//tipo Uint32
				case SDL_QUIT:
					sair=true;
				break;
				case SDL_KEYDOWN:
					
				break;
			}
			
			if(img1.GerenciarMouse(&e)){//caso o mouse esteje sobre
				I=CORACAO;
				J=1;//mostrara o segundo texto
				img1.SetBorda(&cores[0]);
				if(e.type==SDL_MOUSEBUTTONDOWN){
					img1.SetBorda(&cores[2]);
					
				}
			}
			else{//caso o mouse esteje fora
				I=BURACO_NEGRO;
				J=0;//voltara para o texto original
				img1.SetBorda(nullptr);
			}
			
		}
		listaEstadoAtualDoTeclado= SDL_GetKeyboardState(nullptr);
		if(listaEstadoAtualDoTeclado[SDL_SCANCODE_LEFT]){
			SDL_SetRenderDrawColor(tela.GetRender(), 10, 10, 10, 255);
			MoverAngulo(&angulo, false);
		}
		else if(listaEstadoAtualDoTeclado[SDL_SCANCODE_RIGHT]){
			SDL_SetRenderDrawColor(tela.GetRender(), 30, 30, 30, 255);
			MoverAngulo(&angulo, true);
		}
		else{
			SDL_SetRenderDrawColor(tela.GetRender(), 20, 20, 20, 255);
		}
				
		SDL_RenderClear(tela.GetRender());
		t1.Renderizar_Index(J, tela.GetRender(), (LARGURA - t1.GetLargura_Index(J))/2,20);
		img1.RenderizarComAngulo(tela.GetRender(), &Vimg[I], angulo, nullptr);
		SDL_RenderPresent(tela.GetRender());
	}
	return 0;
}