//Incluindo bibliotecas gráficas
#include <GL/glew.h>
#include <GL/freeglut.h>
//Incluindo bibliotecas do C/C++ que serão úteis
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
//Incluindo bibliotecas minhas no projeto
#include "util.hpp"
#include "world.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "tela.hpp"

#ifndef VELOCIDADE_BULLET
#define VELOCIDADE_PLAYER 15
#endif 

#define RELOAD_ENEMY_BULLET 3000

#define POSITION_ENEMYS 6 //Controla a disposição dos inimigos na posicao (fileiras e linhas) na tela.

using namespace std;

int ordemAnimacaoPlayer = 0; //Controla a ordem das sprites dentro de uma animacao
player jogador;
vector<enemy> inimigo;
windowSettings dadosJanela(WORLD_SIZE_W, WORLD_SIZE_H, 50);
colorPalette corDoTexto(1.000, 0.855, 0.725, 0.000);
GLint aleatorio, fase = 0, pontuacao = 0;
vector<string> texturaPlayer; //Nomes dos pokemons disponiveis para escolha
string nomeTexturasPlayer[] = { "charizard", "Tropios" };
string nomeTexturasEnemy[] = { "Pideot" };
string texturaMapa[] = { "PrimeiraFase", "SegundaFase", "TerceiraFase", "QuartaFase" };
int spritePlayerSelecionada = 0, inimigoLigeirinho = 0;
bool balaDisparada = false, jogoPausado = false, menuAtivado = true, posicao[POSITION_ENEMYS][POSITION_ENEMYS], menuSelecao = false, mudouLado = false, venceu = false;
Tela screens = Tela(dadosJanela, corDoTexto);
Tela mainMenu = Tela(dadosJanela, corDoTexto);


void atualizaSpriteCenario(int valor) {
	if (!venceu) {
		atualizaCenario(fase, texturaMapa[fase - 1]);
		glutTimerFunc(valor, atualizaSpriteCenario, valor);
	}
}

void atualizaSpritePersonagens(int valor, int inimigoPos = 0) { //Se valor == 0 significa que vamos atualizar a sprite do player, caso seja 1 vamos atualizar de um inimigo

	char numString[3];
	char caminho[100];

	if (ordemAnimacaoPlayer > 2)
	{
		ordemAnimacaoPlayer = 1;
	}

	strcpy_s(caminho, "res/SpritePlayer/");

	if (valor == 0) {
		strcat_s(caminho, texturaPlayer[spritePlayerSelecionada].c_str()); //indice do array texturaPlayer sera de acordo com o pokemon que o usuario selecionar

		if (jogador.getDireita()) {
			strcat_s(caminho, "Direita");

			jogador.setDireita(false);
		}
		else if (jogador.getEsquerda()) {
			strcat_s(caminho, "Esquerda");

			jogador.setEsquerda(false);
		}
		else
		{
			ordemAnimacaoPlayer = 1;
		}
	}


	sprintf_s(numString, sizeof(numString), "%d", ordemAnimacaoPlayer++);
	strcat_s(caminho, numString);
	strcat_s(caminho, ".png");

	jogador.setTextura(caminho);
}

int* numeroAleatorio(int op) {

	if (op == 0) { // Parametro 0: Escolhe um inimigo aleatorio, que nao esteja morto, para atirar.
		int random = 0;
		random = rand() % inimigo.size();
		int valor[] = { random };

		return valor;

	}
	else if (op == 1) { //Escolhe uma posicao (coluna Y e linha X), que esteja vazia, para o inimigo nascer
		int linha = rand() % 6;
		int coluna = rand() % 6;
		int valores[] = { linha, coluna };

		if (!posicao[linha][coluna]) {			//Se a posicao verificada for TRUE, significa que ja ha um inimigo ali alocado
			posicao[linha][coluna] = true; //Caso nao tenha, eh marcado com o identificador TRUE no qual significa que agora ha um inimigo ali
			return valores;
		}
		else {
			return numeroAleatorio(op);
		}
	}

}

void recarregarTiroPlayer(int valor) {
	jogador.recarregar();
}

void recarregarTiroInimigo(int valor) {

	if (!jogoPausado && !menuAtivado) { //Caso o jogo esteja com o pause desligado e fora de algum menu, significa que o player esta jogando, logo os eventos de jogo estao acontecendo

		aleatorio = numeroAleatorio(0)[0];

		if (!inimigo[aleatorio].getBalaDisparada()) { //Verifico se houve um ataque pelo inimigo
			inimigo[aleatorio].setBalaDisparada(inimigo[aleatorio].atirar(aleatorio));//Caso nao tenha, aleatoriamente um inimigo eh selecionado para atacar
		}

	}
	glutTimerFunc(RELOAD_ENEMY_BULLET, recarregarTiroInimigo, valor);
}

void animacaoInimigos(int valor) {
	for (int i = 0; i < inimigo.size(); i++)
	{
		inimigo[i].atualizaSpritePersonagens(valor);
	}
	glutTimerFunc(valor, animacaoInimigos, valor);
}

void spawnInimigos() {

	if (inimigo.empty()) {
		fase > 4 ? fase = 1 : fase++; //Será um total de 4 fases
	}
	else {
		fase = 1; //Se o array de inimigos estiver vazio, significa que todos os inimigos foram mortos e player venceu a fase, caso contrario segnifica que o player foi derrotado!
		pontuacao = 0;
		inimigo.clear();
	}

	if (inimigo.size() < 10)
	{
		for (int i = 0; i < POSITION_ENEMYS; i++)
		{
			for (int j = 0; j < POSITION_ENEMYS; j++)
			{
				posicao[i][j] = false;
			}
		}

		for (int i = 0; i < 10; i++)
		{
			int* valor = numeroAleatorio(1);
			int linha = valor[0];
			int coluna = valor[1];
			//inimigo[i] = enemy(dadosJanela, linha, coluna, 30, 30, ""); //Fazer verificao para que nao repita posicoes

			inimigo.push_back(enemy(dadosJanela, linha, coluna, 50, 50, "", nomeTexturasEnemy[0]));
			inimigo[i].setSpriteEnemySelecionada(0);

			/*atualizaSpritePersonagens(1, i);*/
			//inimigosVivos.erase(inimigosVivos.bFegin() + 5);

		}
	}




}

void desenhaInimigo() {

	bullet balaPlayer = jogador.getBalaPlayer();
	int inimigoMorto = -1;

	for (int i = 0; i < inimigo.size(); i++)
	{
		/*	atualizaSpritePersonagens(1, i);*/

		if (!inimigo[i].getMorto()) {
			inimigo[i].desenha();

			if (inimigo[i].getBalaDisparada()) {

				bullet balaInimigo = inimigo[i].getBalaInimigo(); //Ponteiro que armazena, dinamicamente, a posição da bala durante sua trajetoria.

				if (jogador.verificaColisaoBala(&balaInimigo)) { //Verifica se a cada Y que a bala DESCE, durante sua trajetoria, encotrou o player VIVO e se o projetil colidiu com ele
					cout << "=================================" << endl;
					cout << "Vidas: " << jogador.getVidas() << endl; //Relatorio de vida do player
					cout << "=================================" << endl;
					inimigo[i].recarregar();
				}
				if (inimigo[i].getBalaInimigo().getBalaDisparada()) {
					inimigo[i].desenhaTrajetoBala();
				}
			}

			if (inimigo[i].verificaColisaoBala(&balaPlayer)) { //Verifica se a cada Y que a bala SOBE, durante sua trajetoria, encotrou algum inimigo VIVO e se o projetil colidiu com ele
				cout << "=================================" << endl;
				cout << "Inimigo: " << i << "morreu!\n" << endl; //Relatorio de morte do inimigo
				cout << "=================================" << endl;
				recarregarTiroPlayer(0);
				inimigoMorto = i;
				pontuacao += 100;
			}
		}
		else {
			inimigo.erase(inimigo.begin() + i);
		}
	}
	if (inimigoMorto >= 0)
	{
		inimigo.erase(inimigo.begin() + inimigoMorto); //Removemos os inimigos mortos *******Nova Implementação, com essa melhoria, poderemos remover o atributo 'getmorto' da classe dos inimigos
	}
}

void desenhaPlayer() {

	if (!jogador.getMorto()) {

		jogador.desenha();

		if (jogador.getBalaDisparada()) {
			jogador.desenhaTrajetoBala();
		}
	}
}

void atualizaCena(int valor) {
	if (inimigo.size() <= 0) {
		cout << "VOCE VENCEU!\nPARABENS!!!!\n" << "Bem vindo a proxima fase!\n" << endl;
		spawnInimigos();
	}

	glutPostRedisplay();

	glutTimerFunc(valor, atualizaCena, valor);


}

//Método que fará as operações de desenho na cena
void desenhaMundo()
{	//Declarando objetos gerais da janela e de paleta de cores que estão no util.hpp
	//windowSettings dadosJanela(WORLD_SIZE_W, WORLD_SIZE_H, 50);
	//Cor das barras superiores e inferiores
	colorPalette corBlackBars(0.000, 0.000, 0.000, 0.000);
	//Cor do fundo
	colorPalette corPrincipal(0.000, 1.000, 0.400, 0.000);
	//Cor do texto superior
	//colorPalette corDoTexto(1.000, 0.855, 0.725, 0.000);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!jogoPausado) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Chamo as funções de desenho
		if (menuAtivado) {

			if (menuSelecao) {
				mainMenu.desenhaTelaSelecao(dadosJanela, corDoTexto, jogador);
			}
			else {
				mainMenu.desenhaMenu(dadosJanela, corBlackBars);
			}
		}
		else {

			if (!jogador.getMorto()) {
				if (fase != 5) {

					desenhaBlackBars(dadosJanela, corBlackBars);
					screens.desenhaHUD(dadosJanela, jogador.getVidas(), pontuacao);
					desenhaTelaPrincipal(dadosJanela, corPrincipal);
					string title = "2021Atari";
					desenhaTexto(dadosJanela, corDoTexto, title, -1);

					desenhaPlayer();
					desenhaInimigo();
				}
				else {
					screens.desenhaTelaVitoria(dadosJanela, pontuacao);
					venceu = true;
				}
			}
			else {
				screens.desenhaTelaGameOver(dadosJanela, corBlackBars);
			}
		}

		glutSwapBuffers();
	}
	else {
		screens.desenhaTelaPause(dadosJanela, corBlackBars);
		glutSwapBuffers();
	}

}

void carregaSpritePlayer() {
	for (int i = 0; i < 2; i++)
	{
		texturaPlayer.push_back(nomeTexturasPlayer[i]);
	}
}

void inicializa()
{
	//Inicializa a semente para numero aleatorio
	srand(time(NULL));

	//Função que define a cor de fundo
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// desenho preenchido 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Permite mesclagem de cores e suporte ha texturas com tranparencia
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Inicializa o jogador
	carregaSpritePlayer();
	jogador = player(dadosJanela, jogador.getPosX(), 100, 100, "", spritePlayerSelecionada);
	atualizaSpritePersonagens(0);
	//inicializa os inimigos primarios
	spawnInimigos();
	glutTimerFunc(250, animacaoInimigos, 250);
	glutTimerFunc(RELOAD_ENEMY_BULLET, recarregarTiroInimigo, 0);
}

//Função responsável por alterar a visão ao redimensionar a janela
void redimensionada(int width, int height)
{
	// left, bottom, right, top
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Defino as coordenadas do mundo utilizando as constantes definidas
	glOrtho(0.0, WORLD_SIZE_W, 0.0, WORLD_SIZE_H, -1.0, 3.0);

	//Nova proporção da janela depois de ser redimensionada
	float windowRatioAspect = ((float)width) / height;
	//Proporção base do mundo
	float worldAspectRatio = ((float)WORLD_SIZE_W) / WORLD_SIZE_H;
	cout << "raj: " << windowRatioAspect << " ram " << worldAspectRatio << endl;
	//Se a proporção do mundo for maior, significa que a tela ficou menor que o mundo, e tratamos como necessário
	if (windowRatioAspect < worldAspectRatio) {

		float hViewport = width / worldAspectRatio;
		float yViewport = (height - hViewport) / 2;
		glViewport(0, yViewport, width, hViewport);

	}
	else if (windowRatioAspect > worldAspectRatio) {
		//Se a proporção da janela for maior, significa que a tela ficou maior que o mundo, e tratamos como necessário		
		float wViewport = ((float)height) * worldAspectRatio;
		float xViewport = (width - wViewport);
		glViewport(0, 0, xViewport + wViewport, height);
	}
	else {
		//Se não houve alteração, apenas defina o viewport com os novos tamanhos
		glViewport(0, 0, width, height);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//Função que opera as entradas do teclado
void teclaPressionada(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 27:      // Tecla "ESC"
		exit(0);  // Sai da aplicação
		break;

	case 32: // Tecla "SPACE"
		if (!jogador.getBalaDisparada() && !jogoPausado) {
			jogador.setBalaDisparada(jogador.atirar());
			atualizaSpritePersonagens(0);

			//glutTimerFunc(1000, recarregarTiroPlayer, 0); //Temporario
		}
		break;

	case 82:
	case 114: //R
		if (!menuAtivado && !menuSelecao) {
			spawnInimigos();
			jogador.resetVidas();
			venceu = false;
			pontuacao = 0;
		}
		break;

	case 83:
	case 115: //S
		menuSelecao = menuAtivado ? true : false;
		break;

	case 66:
	case 98:
		menuSelecao = menuSelecao ? false : true;
		break;

	case 80: // 'P;
	case 112: //'p'
		if (menuAtivado) {
			menuAtivado = false;
		}
		else {
			if (jogoPausado) {
				jogoPausado = false;
			}
			else {
				if (jogador.getMorto()) {
					menuAtivado = true;
					jogador.resetVidas();
					venceu = false;
					spawnInimigos();
				}
				else {
					if (fase == 5) {
						menuAtivado = true;
						jogador.resetVidas();
						venceu = false;
						spawnInimigos();
					}
					else {
						jogoPausado = true;
					}
				}

			}
		}
		break;
	default:
		break;
	}
}

void teclaEspecialPressionada(int key, int x, int y)
{
	int tamanho = texturaPlayer.size();


	if (!jogoPausado) {
		switch (key)
		{
		case GLUT_KEY_RIGHT:   // Tecla "Seta Direita"

			if (menuSelecao) {

				spritePlayerSelecionada++;

				if (spritePlayerSelecionada >= tamanho)
				{
					spritePlayerSelecionada = 0;
				}

				// jogador.setTextura(texturaPlayer[0] + "1");
				mainMenu.desenhaTelaSelecao(dadosJanela, corDoTexto, jogador);//Atualizo a tela de seleção

			}
			else {
				jogador.mover(20);
				jogador.setDireita(true);
			}
			atualizaSpritePersonagens(0);
			break;

		case GLUT_KEY_LEFT:   // Tecla "Seta Direita"

			if (menuSelecao) {
				spritePlayerSelecionada--;

				if (spritePlayerSelecionada < 0)
				{
					spritePlayerSelecionada = (tamanho - 1);
				}

				mainMenu.desenhaTelaSelecao(dadosJanela, corDoTexto, jogador); //Atualizo a tela de seleção
			}
			else {
				jogador.mover(-20);
				jogador.setEsquerda(true);
			}
			atualizaSpritePersonagens(0);

			break;
		default:
			break;
		}
	}
}

// Função principal
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(1, 1);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	//Definindo um objeto de janela para fixar o tamanho da janela inicial
	windowSettings janela(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize((int)janela.getWidth(), (int)janela.getHeight());
	glutInitWindowPosition(275, 50);

	glutCreateWindow("Galaxian - MonXtraO e Phourzin, os Altruístas");

	// Registra callbacks para eventos
	glutDisplayFunc(desenhaMundo);
	glutReshapeFunc(redimensionada);
	glutKeyboardFunc(teclaPressionada); //Usado para capturar os eventos de teclas especiais (aquelas que nao geram um valor ASCII)
	glutSpecialFunc(teclaEspecialPressionada);

	glutTimerFunc(0, atualizaCena, 16);

	/*glutTimerFunc(0, atualizaSpritePersonagens, 500);*/


	glutTimerFunc(244, atualizaSpriteCenario, 122);

	inicializa();

	glutMainLoop();

	return 0;
}

