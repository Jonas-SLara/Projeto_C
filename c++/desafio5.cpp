#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

//level tem as mesmas dimensoe da imagem de fundo E tela tera 1/4 do level
typedef enum Dimensoes{
	LARGURA_LEVEL = 1280,
	ALTURA_LEVEL = 960,
	LARGURA_TELA = 320, 
	ALTURA_TELA = 240
}Dimensoes;

//variaveis globais
SDL_Window* G_JANELA = nullptr;
SDL_Renderer* G_RENDERIZADOR = nullptr;

class Textura{
	
	private:
		
		SDL_Texture *texturaImg;
		int larguraImg;
		int alturaImg;	
	
	public:
		
		Textura():texturaImg(nullptr), larguraImg(0), alturaImg(0){
			std::cout<<"instancia de Textura criada "<<texturaImg<<' '<<larguraImg<<' '<<alturaImg<<'\n';
		}
		
		~Textura(){limpar();}
		
		void limpar(){
			
			if(texturaImg!=nullptr){
				SDL_DestroyTexture(texturaImg);
				larguraImg=0;
				alturaImg=0;
			}
			
			std::cout<<"textura de imagem limpa\n";
		}
		
		bool carregarImagem(std::string caminho){
			
			SDL_Surface *surfaceTemporaria = nullptr;
			surfaceTemporaria = SDL_LoadBMP(caminho.c_str());
			
			if(surfaceTemporaria==nullptr){
				std::cout<<"falha ao criar surface de "<<caminho<<" "<<SDL_GetError()<<'\n';
				return false;
			}
			
			SDL_SetColorKey(surfaceTemporaria, SDL_TRUE, SDL_MapRGB(surfaceTemporaria->format, 255, 255, 255));
			texturaImg = SDL_CreateTextureFromSurface(G_RENDERIZADOR, surfaceTemporaria);
			
			if( texturaImg == nullptr ){
				std::cout<<"falha ao criar textura de "<<caminho<<" "<<SDL_GetError()<<'\n';
			}
			
			else{
				larguraImg=surfaceTemporaria->w;
				alturaImg=surfaceTemporaria->h;
				std::cout<<"textura: "<<texturaImg<<" W:"<<larguraImg<<" H:"<<alturaImg<<" criada\n";
			}
			
			SDL_FreeSurface(surfaceTemporaria);
			return (texturaImg!=nullptr)? true : false;
		}
		
		void renderizarImg(int x, int y, SDL_Rect *clip){//clip é a parte da imagem renderizada
			
			SDL_Rect areaNaTela = {x, y, obterLargura(), obterAltura()};//mesmo tamanho da imagem
			
			if(clip!=nullptr){//para definir uma parte da textura a ser renderizada e mostrada 
				areaNaTela.w=clip->w;
				areaNaTela.h=clip->h;
			}
			
			SDL_RenderCopy(G_RENDERIZADOR, texturaImg, clip, &areaNaTela);
		}
		
		int obterAltura(){return alturaImg;}
		
		int obterLargura(){return larguraImg;}
};

//basicamente o scroll consiste em mover uma 'camera' que acompanha o jogador e o conteudo é mostrado nela
//tanto a camera como o jogador tem coordenadas no level e limites de alcance
class Jogador{
	
	private:
		
		int jogadorX, jogadorY;//posição do jogado na tela(camera) nao no level
		int levelX, levelY, deslocamentoX, deslocamentoY;//coordenadas do jogador no level
		Textura * imgJogador;
		Textura * imgLevel;
		SDL_Rect camera;
	
	public:
		
		Jogador(Textura *imgJ, Textura *imgLv):imgJogador(imgJ), imgLevel(imgLv), deslocamentoX(0), deslocamentoY(0){
			//o o jogador sempre estara posicionado no centro da tela(da sua camera)
			jogadorX=(LARGURA_TELA - imgJogador->obterLargura())/2;
			jogadorY=(ALTURA_TELA - imgJogador->obterAltura())/2;
			levelX=jogadorX;
			levelY=jogadorY;
			camera.w = LARGURA_TELA;
			camera.h = ALTURA_TELA;
			obterPosicaoCamera();
			std::cout<<"camera x "<<camera.x<<" y "<<camera.y<<" w "<<camera.w<<" h "<<camera.h<<'\n';
			std::cout<<"level x "<<levelX<<"level y "<<levelY<<'\n';
		} 
		
		~Jogador(){
			imgJogador=nullptr;
			imgLevel=nullptr;
		}
		//obtem ou atualiza a posiçao da camera no level em relação aonde esta o jogador cada vez que ele se move
		
		void obterPosicaoCamera(){
			//toma como medida que o jogador esta no centro da camera
			this->camera.x = levelX - ( LARGURA_TELA - imgJogador->obterLargura() )/2;
			this->camera.y = levelY - ( ALTURA_TELA - imgJogador->obterAltura() )/2; 
		}
		
		void mover(SDL_Event &e){//move o jogador pelo mapa e a camera junto, mas nao altera as coordenas dele na tela
			
			if(e.type==SDL_KEYDOWN && e.key.repeat==0){//o campo repeat de SDL_KeyBoardEvent verifica se o evento atual do teclado nao é repetido, só repetindo 1 vez
				switch(e.key.keysym.sym){//o campo SDL_Keysym tem informaçoes como o codigo da tecla no campo sym (SDL_Keycode)
					case SDLK_LEFT:deslocamentoX = -5;break;
					case SDLK_RIGHT:deslocamentoX = 5;break;
					case SDLK_DOWN:deslocamentoY = 5;break;
					case SDLK_UP:deslocamentoY = -5;
				}
			}
			
			else if(e.type==SDL_KEYUP && e.key.repeat==0){
					switch(e.key.keysym.sym){
					case SDLK_LEFT:deslocamentoX = 0;break;
					case SDLK_RIGHT:deslocamentoX = 0;break;
					case SDLK_DOWN:deslocamentoY = 0;break;
					case SDLK_UP:deslocamentoY = 0;
				}
			}
			
			levelX += deslocamentoX;
			if( levelX < ( LARGURA_TELA/2 - imgJogador->obterLargura()/2 ) ) levelX -= deslocamentoX;
			if( levelX > ( LARGURA_LEVEL - LARGURA_TELA/2 - imgJogador->obterLargura()/2 ) ) levelX -= deslocamentoX;
			
			levelY += deslocamentoY;
			if( levelY < ( ALTURA_TELA/2 - imgJogador->obterAltura()/2 ) ) levelY -= deslocamentoY;
			if( levelY > ( ALTURA_LEVEL - ALTURA_TELA/2 - imgJogador->obterAltura()/2 ) ) levelY -= deslocamentoY;
			
			obterPosicaoCamera();
			//std::cout<< "levelX: "<<levelX<<"  levelY: "<<levelY<<"  cameraX: "<<camera.x<<"  cameraY: "<<camera.y<<'\n';
		}
		
		void mostrarJogador(){
			imgJogador->renderizarImg(jogadorX, jogadorY, nullptr);
		}
		
		void mostrarCamera(){//renderiza a partir de onde a camera esta dentro da imagem do lv
			imgLevel->renderizarImg(0, 0, &camera);
		}
};

class Musica{
	
	private:
		bool pause;
		Mix_Music * musica;
		
		//metos privados para gerenciar o estado da musica, implementado por um metodo publico da classe
		void pausarMusica(){
			if(!pause){
				pause=true;
				Mix_PauseMusic();
			}
		}
		
		void retomarMusica(){
			if(pause){
				pause=false;
				Mix_ResumeMusic();
			}
		}
		
	public:
	
		Musica(): pause(false), musica(nullptr){}
		
		bool carregarMusica(std::string caminho){
			musica = Mix_LoadMUS(caminho.c_str());
			
			if (musica==nullptr) {
				std::cout << "Erro ao carregar música: " << Mix_GetError() <<'\n';
				return false;
			}
			
			std::cout<<"musica carregada: "<<caminho<<" ->"<<musica<<'\n';
			return true;
		}
		
		void tocarMusica(){
			if( Mix_PlayMusic( musica, -1 ) == -1 ){
				std::cout<< "Erro ao tocar música: " << Mix_GetError() <<'\n';
			}
		}
		
		void gerenciaEstado(SDL_Event &e){
			if(e.type==SDL_KEYDOWN && e.key.repeat==0 && e.key.keysym.sym == SDLK_p){
				this->pausarMusica();
			}
			else if(e.type==SDL_KEYDOWN && e.key.repeat==0 && e.key.keysym.sym == SDLK_r ){
				this->retomarMusica();
			}
		}
		
		~Musica(){
			Mix_FreeMusic(musica);
			musica=nullptr;
			std::cout<<"destruidor de musica\n";
		}
		
};

//funçoes para gerenciar o sdl
bool iniciar(){
	
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		std::cout<<"erro ao iniciar SDL "<<SDL_GetError()<<'\n';
		return false;
	}
	
	// Inicializa o áudio com os parametros (int frequency, Uint16 format, int channels, int chunksize)
    //int 	frequency 	the frequency to playback audio at (in Hz).
	//Uint16 	format 	audio format, one of SDL's AUDIO_* values.
	//int 	channels 	number of channels (1 is mono, 2 is stereo, etc).
	//int 	chunksize 	audio buffer size in sample FRAMES (total samples divided by channel count).
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        std::cerr << "Erro ao inicializar o áudio: " << Mix_GetError() << std::endl;
        return false;
    }
	
	G_JANELA = SDL_CreateWindow("tutorial de scroll", 500, 200, LARGURA_TELA, ALTURA_TELA, SDL_WINDOW_SHOWN);
	
	if(G_JANELA==nullptr){
		std::cout<<"falha ao criar janela "<<SDL_GetError()<<'\n';
		return false;
	}
	
	G_RENDERIZADOR = SDL_CreateRenderer(G_JANELA, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	if(G_RENDERIZADOR==nullptr){
		std::cout<<"falha ao criar renderizadoe "<<SDL_GetError()<<'\n';
		return false;
	}
	
	std::cout<<"janela: " << G_JANELA << "  renderizador: " << G_RENDERIZADOR<<'\n';
	return true;
}

void fechar(){
	SDL_DestroyRenderer(G_RENDERIZADOR);
	SDL_DestroyWindow(G_JANELA);
	G_JANELA = nullptr;
	G_RENDERIZADOR = nullptr;
	Mix_CloseAudio();
	SDL_Quit();
	std::cout<<"fim de execucao sdl\n";
}

int main(int argc, char *argv[]){
	
	if(!iniciar()){
		fechar();
		return -1;
	}
	
	Textura fundo;
	Textura personagem;
	Musica mp3;
	
	if(!fundo.carregarImagem("bmp/bg.bmp")){
		fechar();
		return -1;
	}
	
	if(!personagem.carregarImagem("bmp/dot.bmp")){
		fechar();
		return -1;
	}
	
	if(!mp3.carregarMusica("mp3/faixa0.mp3")){
		fechar();
		return -1;
	}
	
	Jogador j1(&personagem, &fundo);//cria as posiçoes para um jogador e seu campo de visão para serem usados
	
	//variaveis de controle
	SDL_Event e;
	bool sair = false;
	Uint32 inicio;//usado para fins de medição e perfomance, obtem o tempo de processamento em milisegundos
	
	//iniciar a musica
	mp3.tocarMusica();
	
	while(!sair){
		inicio=SDL_GetTicks();
		
		while(SDL_PollEvent(&e)!= 0){
			if(e.type==SDL_QUIT)sair=true;
			j1.mover( e );
			mp3.gerenciaEstado( e );
		}
		
		SDL_SetRenderDrawColor(G_RENDERIZADOR, 20, 20, 35, 255);
		SDL_RenderClear(G_RENDERIZADOR);
		j1.mostrarCamera();
		j1.mostrarJogador();
		SDL_RenderPresent(G_RENDERIZADOR);
		std::cout<< SDL_GetTicks()  - inicio<<'\n';
	}
	
	fechar();
	return 0;
}