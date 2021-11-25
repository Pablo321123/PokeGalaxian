#ifndef ENEMY_H
#define ENEMY_H
#define MARGINHORIZONTAL 20

#include <chrono>
#include "player.hpp"
#include "bullet.hpp" 

using namespace std;

class enemy {

private:

	GLfloat posX, posY, larguraX, alturaY, posZ, tamanhoTelaXini, tamanhoTelaXfim, velY = 5, velX = 4, limiteTelaHorizontalIni, limiteTelaHorizontalFim;
	string endTextura, nomePokemon;
	GLuint idTextura, spriteEnemySelecionada, ordemAnimacaoPlayer = 1;
	bullet bala;
	player p;
	GLboolean emMovimento, morto, direita, esquerda, mudouLado = false;

	bool carregaTextura2D(string arquivo) {
		idTextura = SOIL_load_OGL_texture(arquivo.c_str(), SOIL_LOAD_AUTO, idTextura, SOIL_FLAG_INVERT_Y);

		if (idTextura == 0)
		{
			printf("Erro ao carregar textura: '%s'\n", SOIL_last_result());
			return false;
		}

		return true;
	}




public:

	enemy() {
		posX = 0.0f;
		posY = 0.0f;
		posZ = 0.0f;
		larguraX = 0.0f;
		alturaY = 0.0f;
		endTextura = "";
	}

	enemy(windowSettings janelaPrincipal, GLfloat fileiraY, GLint fileiraX, GLfloat larguraX, GLfloat alturaY, string endTextura, string nomePokemon) {

		limiteTelaHorizontalIni = janelaPrincipal.getSpacingBlackBars() + MARGINHORIZONTAL + 20;
		limiteTelaHorizontalFim = janelaPrincipal.getWidth() - janelaPrincipal.getSpacingBlackBars() - MARGINHORIZONTAL;

		this->posX = (limiteTelaHorizontalIni) * (fileiraX + 1);
		this->posY = (janelaPrincipal.getHeight() - (janelaPrincipal.getSpacingBlackBars() * (2 + fileiraY)) - 20); // variante altura de 0 a 5
		this->posZ = 1;
		this->larguraX = larguraX;
		this->alturaY = alturaY;
		this->endTextura = endTextura;
		this->nomePokemon = nomePokemon;

		idTextura = SOIL_load_OGL_texture(endTextura.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

		atualizaSpritePersonagens(0);
		carregaTextura2D(this->endTextura);

		tamanhoTelaXini = janelaPrincipal.getSpacingBlackBars() + 10;
		tamanhoTelaXfim = janelaPrincipal.getWidth() - janelaPrincipal.getSpacingBlackBars() - 55;

		bala = bullet(posX, posY, janelaPrincipal.getHeight() - janelaPrincipal.getSpacingBlackBars(), janelaPrincipal.getSpacingBlackBars(), 2);
		morto = false; //Variavel que controla o estado entre a vida e a morte do inimigo;

	}


	void atualizaSpritePersonagens(int valor) { //Se valor == 0 significa que vamos atualizar a sprite do player, caso seja 1 vamos atualizar de um inimigo

		char numString[3];
		char caminho[100];

		if (ordemAnimacaoPlayer > 2)
		{
			ordemAnimacaoPlayer = 1;
		}

		strcpy_s(caminho, "res/SpriteEnemy/");


		strcat_s(caminho, nomePokemon.c_str());

		if (direita) {
			strcat_s(caminho, "Direita");

			//inimigo.setDireita(false);
		}
		else if (esquerda) {
			strcat_s(caminho, "Esquerda");
			//inimigo.setEsquerda(false);
		}
		else
		{
			ordemAnimacaoPlayer = 1;
		}

		sprintf_s(numString, sizeof(numString), "%d", ordemAnimacaoPlayer++);
		strcat_s(caminho, numString);
		strcat_s(caminho, ".png");


		endTextura = caminho;
		carregaTextura2D(endTextura);

		/*glutTimerFunc(valor, atualizaSpritePersonagens, valor);*/
	}

	bool desenha() {

		if (bala.getBalaDisparada()) { // Temporario, indicador para saber quando a bala foi recarregada!
			glColor3f(1, 0, 0);
		}
		else {
			glColor3f(1, 1, 0);
		}

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

		movimentoInimigo();

		return true;
	}

	void movimentoInimigo() {

		posX += velX;

		if ((posX + larguraX <= limiteTelaHorizontalIni + MARGINHORIZONTAL)) {
			velX = velX * -1;
			direita = true;
			esquerda = false;

			//mudouLado = true;
		}
		else if (posX + larguraX >= limiteTelaHorizontalFim - MARGINHORIZONTAL) {
			velX = velX * -1;
			direita = false;
			esquerda = true;

			//mudouLado = true;
		}

	}

	bool atirar(GLint indice) {

		bala.setBalaPosX(posX + (larguraX / 3)); //Dividido por 3 para a bala "nascer" no meio do player, pois, dividindo o jogador em 3 partes, vamos pegar a pos inicial em x (0) + a terça parte da largura.
		bala.setBalaPosY(posY);
		bala.desenha(posX, posY, true); // LEMBRETE: **********Simplificar adicionando um metodo atirar em bullet*******

		esquerda = false;
		direita = false;

		return true;

	}

	void desenhaTrajetoBala() {

		bala.desenha(bala.getBalaPosX(), bala.getBalaPosY(), true);

	}

	void recarregar() {
		bala.recarregarBala();
	}

	GLboolean verificaColisaoBala(bullet* balaPlayer) { //Verifica se a bala disparada pelo player atingiu um inimigo

		if (posY + alturaY < balaPlayer->getBalaPosY() + balaPlayer->getVariacaoY()) {
			return false;
		}
		else if (posY > balaPlayer->getBalaPosY() + balaPlayer->getAlturaY() + balaPlayer->getVariacaoY()) {
			return false;
		}
		else if (posX + larguraX < balaPlayer->getBalaPosX()) {
			return false;
		}
		else if (posX > balaPlayer->getBalaPosX() + balaPlayer->getLarguraX()) {
			return false;
		}
		else {

			morto = true;

			return true;
		}
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

	bullet getBalaInimigo() {
		return bala;
	}

	GLboolean getDireita() {
		return direita;
	}

	GLboolean getEsquerda() {
		return esquerda;
	}

	GLint getSpriteEnemySelecionada() {
		return spriteEnemySelecionada;
	}

	GLfloat getVelX() {
		return velX;

	}

	GLfloat getMudouLado() {
		return mudouLado;

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

	void setSpriteEnemySelecionada(GLint spriteEnemySelecionada) {
		this->spriteEnemySelecionada = spriteEnemySelecionada;
	}

	void setNomePokemon(string nomePokemon) {
		this->nomePokemon = nomePokemon;

	}

	void setVelX(GLfloat velX) {
		this->velX = velX;

	}
	void setDireita(GLboolean direita) {
		this->direita = direita;

	}
	void setEsquerda(GLboolean esquerda) {
		this->esquerda = esquerda;

	}

	void setMudouLado(GLboolean mudouLado) {
		this->mudouLado = mudouLado;
	}
	void setMorto(GLboolean morto) {
		this->morto = morto;
	}


#pragma endregion



};
#endif