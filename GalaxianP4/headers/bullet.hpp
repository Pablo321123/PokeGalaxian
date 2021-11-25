#ifndef BULLET_H
#define BULLET_H

#include <SOIL2/SOIL2.h>

#ifndef VELOCIDADE_BULLET
#define VELOCIDADE_BULLET 6
#endif 

#ifndef LARGURAX_BULLET
#define LARGURAX_BULLET 25
#endif 

#ifndef ALTURAY_BULLET
#define ALTURAY_BULLET 25
#endif 



/*Autor: Pablo Vasconcelos da Cruz*/

using namespace std;
class bullet {

private:

	GLfloat  posX, posY, posYini, posZ, tamanhoTelaYfim, tamanhoTelaYini, variacaoY;
	string endTextura;
	string nomeTexturasEnemy[3] = { "Fogo", "Grama", "Gelo" };
	int tipoTiro;
	GLuint idTextura;
	GLint ordemAnimacaoBala = 1;
	GLboolean balaDisparada = false;


	bool carregaTextura2D(string arquivo) {
		idTextura = SOIL_load_OGL_texture(arquivo.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

		if (idTextura == 0)
		{
			printf("Erro ao carregar textura: '%s'\n", SOIL_last_result());
			return false;
		}

		return true;
	}

	void atualizaSpriteTiro(int valor) { //Se valor == 0 significa que vamos atualizar a sprite do player, caso seja 1 vamos atualizar de um inimigo

		char numString[3];
		char caminho[100];

		if (ordemAnimacaoBala > 3)
		{
			ordemAnimacaoBala = 1;
		}

		strcpy_s(caminho, "res/SpriteTiro/");


		strcat_s(caminho, nomeTexturasEnemy[tipoTiro].c_str());

		sprintf_s(numString, sizeof(numString), "%d", ordemAnimacaoBala++);
		strcat_s(caminho, numString);
		strcat_s(caminho, ".png");


		endTextura = caminho;
		carregaTextura2D(endTextura);

		/*glutTimerFunc(valor, atualizaSpritePersonagens, valor);*/
	}


public:

	bullet() {

		posX = 0.0f;
		posY = 0.0f;
		posYini = 0.0f;
		posZ = 0.0f;
		endTextura = "";

	}

	bullet(GLfloat posX, GLfloat posY, GLfloat tamanhoTelaYfim, GLfloat tamanhoTelaYini, int tipoTiro) { //GLfloat variacaoX eh utilizado para detectar o movimento no eixo X do player

		this->posX = posX;
		this->posY = posY;
		this->tamanhoTelaYfim = tamanhoTelaYfim - 30;
		this->tamanhoTelaYini = tamanhoTelaYini + 20;
		this->tipoTiro = tipoTiro;
		posZ = 0.0f;
		variacaoY = 0;
		posYini = posY;
	}

	GLboolean verificaColisaoParedes() {

		GLfloat valor = posY + variacaoY; //Verificacao para saber se o projetil ainda esta dentre os limites da tela!

		if (valor >= tamanhoTelaYfim) { //Caso nao esteja, ele recarregara o projetil;

			recarregarBala();
			posY = posYini;

			return false;
		}
		else if (valor <= tamanhoTelaYini) {
			recarregarBala();
			posY = posYini;

			return false;
		}

		return true;
	}

	bool desenha(GLfloat posX, GLfloat posY, bool balaCaindo) { //Variavewl para controlar tiros disparados por inimigos e pelo player

		posY += variacaoY;


		glColor3f(1, 0.5, 0.4);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTextura);

		glBegin(GL_POLYGON);

		glTexCoord2f(0, 0);
		glVertex3f(posX, posY, posZ);
		glTexCoord2f(1, 0);
		glVertex3f(posX + LARGURAX_BULLET, posY, posZ);
		glTexCoord2f(1, 1);
		glVertex3f(posX + LARGURAX_BULLET, posY + ALTURAY_BULLET, posZ);
		glTexCoord2f(0, 1);
		glVertex3f(posX, posY + ALTURAY_BULLET, posZ);

		glEnd();
		glDisable(GL_TEXTURE_2D);

		if (verificaColisaoParedes()) {
			variacaoY += balaCaindo ? (VELOCIDADE_BULLET * -1) : VELOCIDADE_BULLET;
		}

		atualizaSpriteTiro(0);

		return true;
	}

	void recarregarBala() {
		balaDisparada = false;
		variacaoY = 0;
	}



#pragma region Getters

	GLfloat getBalaPosX() {
		return posX;
	}

	GLfloat getBalaPosY() {
		return posY;
	}

	GLboolean getBalaDisparada() {
		return balaDisparada;
	}


	GLfloat getLarguraX() {
		return LARGURAX_BULLET;
	}

	GLfloat getAlturaY() {
		return ALTURAY_BULLET;
	}

	GLfloat getVariacaoY() {
		return variacaoY;
	}

	GLfloat getPosYini() {
		return posYini;
	}




#pragma endregion

#pragma region Setters

	void setBalaPosX(GLfloat posX) {
		this->posX = posX;
	}

	void setBalaPosY(GLfloat posY) {
		this->posY = posY;
	}

	void setBalaVsariacaoY(GLfloat variacaoY) {
		this->variacaoY = variacaoY;
	}


	void setBalaDisparada(GLboolean balaDisparada) {
		this->balaDisparada = balaDisparada;
	}


#pragma endregion


};
#endif