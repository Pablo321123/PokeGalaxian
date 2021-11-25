#ifndef PLAYER_H
#define PLAYER_H

#define MARGINHORIZONTAL 20

#include <SOIL2/SOIL2.h>
//
//#include "enemy.hpp" 
#include "bullet.hpp" 

/*Autor: Pablo Vasconcelos da Cruz*/

using namespace std;
class player {

private:

	GLfloat posX, posY, larguraX, alturaY, posZ, tamanhoTelaXini, tamanhoTelaXfim;
	GLuint idTextura, vidas;
	string endTextura;
	GLboolean morto, direita, esquerda;
	bullet bala;
	//enemy* inimigos;

	bool carregaTextura2D(string arquivo) {
		const char* teste = arquivo.c_str();
		idTextura = SOIL_load_OGL_texture(arquivo.c_str(), SOIL_LOAD_AUTO, idTextura, SOIL_FLAG_INVERT_Y);

		if (idTextura == 0)
		{
			printf("Erro ao carregar textura: '%s'\n", SOIL_last_result());
			return false;
		}

		return true;
	}


public:

	player() {

		posX = 0.0f;
		posY = 0.0f;
		posZ = 0.0f;
		larguraX = 0.0f;
		alturaY = 0.0f;
		endTextura = "";

	}

	player(windowSettings janelaPrincipal, GLfloat variacaoX, GLfloat larguraX, GLfloat alturaY, string  endTextura, int spritePlayerSelecionada) { //GLfloat variacaoX eh utilizado para detectar o movimento no eixo X do player
																																		// Aposicoes iniciais sao montadas a partir das dimensoes da tela, controloda pela classe windowSettings.

		this->posX = ((janelaPrincipal.getWidth() - 30) / 2);
		this->posY = (janelaPrincipal.getSpacingBlackBars() * 1.6);
		this->posZ = 1;
		this->larguraX = larguraX;
		this->alturaY = alturaY;
		this->endTextura = endTextura;
		direita = esquerda = false;
		morto = false;

		if (endTextura != "")
		{
			carregaTextura2D(endTextura);
		}

		vidas = 3;

		tamanhoTelaXini = janelaPrincipal.getSpacingBlackBars() + 10;
		tamanhoTelaXfim = janelaPrincipal.getWidth() - janelaPrincipal.getSpacingBlackBars() - 75 - MARGINHORIZONTAL;

		bala = bullet(posX, posY, janelaPrincipal.getHeight() - janelaPrincipal.getSpacingBlackBars(), janelaPrincipal.getSpacingBlackBars(), spritePlayerSelecionada); //O spawn da bala do player acontece por meio das posições de X e Y atuais do player na qual, 
	}																																		//essa, tem uma velocidade vertical positiva

	bool desenha() {

		//if (bala.getBalaDisparada()) { // Temporario, indicador para saber quando a bala foi recarregada!
		//	glColor3f(1, 0, 0);
		//}
		//else {
		//	glColor3f(0, 0, 1);
		//}		

		//SOIL_free_image_data();

		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, idTextura);
		glBegin(GL_POLYGON);

		glTexCoord2f(0, 0);
		glVertex3f(posX, posY, posZ);
		glTexCoord2f(1, 0);
		glVertex3f(posX + larguraX, posY, posZ);
		glTexCoord2f(1, 1);
		glVertex3f(posX + larguraX, posY + alturaY, posZ);
		glTexCoord2f(0, 1);
		glVertex3f(posX, posY + alturaY, posZ);

		glEnd();
		glDisable(GL_TEXTURE_2D);

		return true;
	}

	void mover(GLfloat variacaoX) {

		GLfloat valor = variacaoX + posX; //Primeira verificacao para saber se a nova posicao do player estará dentro dos limites da tela.

		if ((valor < tamanhoTelaXfim) && valor > tamanhoTelaXini) { //Caso esteja, ele adicionara a variação da posição em X, normalmente;
			posX += variacaoX;
		}
		else if ((valor > tamanhoTelaXfim - MARGINHORIZONTAL)) { //Caso contrario, a posição do player será  igual ao limite da tela
			posX = tamanhoTelaXfim - MARGINHORIZONTAL;
		}
		else if ((valor < tamanhoTelaXini)) {
			posX = tamanhoTelaXini;
		}

	}

	bool atirar() {

		bala.setBalaPosX(posX + (larguraX / 3)); //Dividido por 3 para a bala "nascer" no meio do player, pois, dividindo o jogador em 3 partes, vamos pegar a pos inicial em x (0) + a terça parte da largura.
		bala.setBalaPosY(posY);
		bala.desenha(posX, posY, false);

		/*	for (int i = 0; i < 10; i++)
			{
				cout << "Y: " << inimigos[i].getPosY() << " " << "X: " << inimigos[i].getPosX() << endl;
			}
			cout << "=================================" << endl;*/

		return true;

	}

	void recarregar() {
		bala.recarregarBala();
	}

	void desenhaTrajetoBala() {
		bala.desenha(bala.getBalaPosX(), bala.getBalaPosY(), false); //Metodo criado para atualizar a bala durante sua trajetoria.

	}

	GLboolean verificaColisaoBala(bullet* balaInimigo) { //Verifica se a bala disparada pelo INIMIGO atingiu o PLAYER


		if (posY + alturaY < balaInimigo->getBalaPosY() + balaInimigo->getVariacaoY()) {
			return false;
		}
		else if (posY > balaInimigo->getBalaPosY() + balaInimigo->getVariacaoY()) {
			return false;
		}
		else if (posX + larguraX < balaInimigo->getBalaPosX()) {
			return false;
		}
		else if (posX > balaInimigo->getBalaPosX() + balaInimigo->getLarguraX()) {
			return false;
		}
		else {

			vidas--;

			if (!vidas) {
				morto = true;
			}

			return true;
		}
	}

	void resetVidas() {
		this->vidas = 3;
		this->morto = false;
	}


#pragma region Getters

	GLfloat getPosX() {
		return posX;
	}

	GLfloat getPosY() {
		return posY;
	}

	GLfloat getLarguraX() {
		return larguraX;
	}

	GLfloat getAlturaY() {
		return alturaY;
	}

	GLuint getTextura() {

		return idTextura;
	}

	GLboolean getBalaDisparada() {
		return bala.getBalaDisparada();
	}

	GLboolean getMorto() {
		return morto;
	}
	GLboolean getDireita() {
		return direita;
	}
	GLboolean getEsquerda() {
		return esquerda;
	}

	bullet getBalaPlayer() {
		return bala;
	}

	GLuint getVidas() {
		return vidas;
	}



#pragma endregion

#pragma region Setters

	void setPosX(GLfloat posX) {
		this->posX = posX;
	}

	void setPosY(GLfloat posY) {
		this->posY = posY;
	}

	void setLarguraX(GLfloat larguraX) {
		this->larguraX = larguraX;
	}

	void setAlturaY(GLfloat alturaY) {
		this->alturaY = alturaY;
	}

	void setTextura(string endTextura) {
		carregaTextura2D(endTextura);
		this->endTextura = endTextura;

	}

	void setBalaDisparada(GLboolean balaDisparada) {
		bala.setBalaDisparada(balaDisparada);
	}

	void setDireita(GLboolean direita) {
		this->direita = direita;
	}

	void setEsquerda(GLboolean esquerda) {
		this->esquerda = esquerda;
	}


#pragma endregion


};

#endif