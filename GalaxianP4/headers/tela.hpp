#ifndef TELA_H
#define TELA_H
#include "util.hpp"

class Tela {
private:
	windowSettings dadosWindow;
	colorPalette	paletaDeCores;

public:
	Tela() {
		dadosWindow = windowSettings(WORLD_SIZE_W, WORLD_SIZE_H);
		paletaDeCores = colorPalette(0, 0, 0, 0);
	}
	Tela(windowSettings dadosJanela, colorPalette cor) {
		dadosWindow = dadosJanela;
		paletaDeCores = cor;
	}
	void desenhaMenu(windowSettings dadosJanela, colorPalette corFundo)
	{
		glClearColor(corFundo.getColorR(), corFundo.getColorG(), corFundo.getColorB(), 0);
		std::string titulo = "GALAXIAN - P4";
		std::string texto1 = "[ P ] START GAME";
		std::string texto2 = "[ S ] SELECT CHARACTER";
		std::string texto3 = "[ ESC ] EXIT GAME";

		int i = 0;

		glColor3f(paletaDeCores.getColorR(), paletaDeCores.getColorG(), paletaDeCores.getColorB());
		glRasterPos3f(150, dadosJanela.getHeight() - 75, 1);
		glPushMatrix();
		glLineWidth(5);
		glTranslatef(135, dadosJanela.getHeight() - 100, 1);
		glScalef(0.5, 0.5, 1);

		for (int i = 0; i < titulo.size(); i++) {
			if (titulo[i] <= 127 && titulo[i] >= 32) {
				glutStrokeCharacter(GLUT_STROKE_ROMAN, titulo[i]);
			}
			else {
				cout << "Caracter nao suportado:    " << (int)titulo[i] << endl;
			}
		}
		glPopMatrix();

		glPushMatrix();
		glRasterPos3f((dadosJanela.getWidth() / 2) - 110, 375, 1);

		for (int i = 0; i < texto1.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto1.at(i));
		}
		glRasterPos3f((dadosJanela.getWidth() / 2) - 110, 275, 1);
		for (int i = 0; i < texto2.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto2.at(i));
		}
		glRasterPos3f((dadosJanela.getWidth() / 2) - 110, 175, 1);
		for (int i = 0; i < texto3.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto3.at(i));
		}
		glPopMatrix();

	}

	void desenhaTelaSelecao(windowSettings dadosJanela, colorPalette corFundo, player jogador) {
		glColor3f(paletaDeCores.getColorR(), paletaDeCores.getColorG(), paletaDeCores.getColorB());
		std::string titulo = "SELECIONE SEU PERSONAGEM:";
		std::string textoB = "[B] - Voltar";
		std::string textoSetas = "Selecionar Anterior [<-]    |    [->] Selecionar Posterior";

		glRasterPos3f(150, dadosJanela.getHeight() - 75, 1);
		glPushMatrix();
		glLineWidth(5);
		glTranslatef(100, dadosJanela.getHeight() - 75, 1);
		glScalef(0.3, 0.3, 1);

		for (int i = 0; i < titulo.size(); i++) {
			if (titulo[i] <= 127 && titulo[i] >= 32) {
				glutStrokeCharacter(GLUT_STROKE_ROMAN, titulo[i]);
			}
			else {
				cout << "Caracter nao suportado:    " << (int)titulo[i] << endl;
			}
		}
		glPopMatrix();
		glPushMatrix();

		//--------------------


		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, jogador.getTextura());

		glBegin(GL_POLYGON);

		glTexCoord2f(0, 0);
		glVertex3f(jogador.getPosX(), jogador.getPosY() + (dadosJanela.getSpacingBlackBars() * 4), 1);
		glTexCoord2f(1, 0);
		glVertex3f(jogador.getPosX() + jogador.getLarguraX(), jogador.getPosY() + (dadosJanela.getSpacingBlackBars() * 4), 1);
		glTexCoord2f(1, 1);
		glVertex3f(jogador.getPosX() + jogador.getLarguraX(), jogador.getPosY() + jogador.getAlturaY() + (dadosJanela.getSpacingBlackBars() * 4), 1);
		glTexCoord2f(0, 1);
		glVertex3f(jogador.getPosX(), jogador.getPosY() + jogador.getAlturaY() + (dadosJanela.getSpacingBlackBars() * 4), 1);

		glEnd();

		glDisable(GL_TEXTURE_2D);

		//--------------------
		glRasterPos3f((dadosJanela.getWidth() / 2) - 200, dadosJanela.getSpacingBlackBars(), 1);

		for (int i = 0; i < textoB.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, textoB.at(i));
		}
		glPopMatrix();
		glPushMatrix();
		//--------------------

		glRasterPos3f((dadosJanela.getWidth() / 2) - 200, dadosJanela.getSpacingBlackBars() + 100, 1);

		for (int i = 0; i < textoSetas.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, textoSetas.at(i));
		}

		glPopMatrix();
		glPushMatrix();
	}

	void desenhaTelaPause(windowSettings dadosJanela, colorPalette corFundo) {
		glClearColor(corFundo.getColorR(), corFundo.getColorG(), corFundo.getColorB(), 0);
		//std::string titulo = "GALAXIAN - P4";
		std::string texto1 = "[ P ] RESUME";
		std::string texto2 = "[ ESC ] EXIT GAME";

		int i = 0;

		glColor3f(paletaDeCores.getColorR(), paletaDeCores.getColorG(), paletaDeCores.getColorB());
		glPushMatrix();
		glRasterPos3f((dadosJanela.getWidth() / 2) - 110, 325, 1);

		for (int i = 0; i < texto1.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto1.at(i));
		}
		glRasterPos3f((dadosJanela.getWidth() / 2) - 110, 225, 1);
		for (int i = 0; i < texto2.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto2.at(i));
		}
		glPopMatrix();
	}

	void desenhaTelaGameOver(windowSettings dadosJanela, colorPalette corFundo) {
		glClearColor(corFundo.getColorR(), corFundo.getColorG(), corFundo.getColorB(), 0);
		std::string titulo = "GAME OVER";
		std::string texto1 = "[ P ] PLAY AGAIN";
		std::string texto2 = "[ ESC ] EXIT GAME";

		int i = 0;

		glColor3f(paletaDeCores.getColorR(), paletaDeCores.getColorG(), paletaDeCores.getColorB());
		glRasterPos3f(150, dadosJanela.getHeight() - 75, 1);
		glPushMatrix();
		glLineWidth(5);
		glTranslatef(200, dadosJanela.getHeight() - 100, 1);
		glScalef(0.5, 0.5, 1);

		for (int i = 0; i < titulo.size(); i++) {
			if (titulo[i] <= 127 && titulo[i] >= 32) {
				glutStrokeCharacter(GLUT_STROKE_ROMAN, titulo[i]);
			}
			else {
				cout << "Caracter nao suportado:    " << (int)titulo[i] << endl;
			}
		}
		glPopMatrix();
		glPushMatrix();
		glRasterPos3f((dadosJanela.getWidth() / 2) - 110, 325, 1);

		for (int i = 0; i < texto1.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto1.at(i));
		}
		glRasterPos3f((dadosJanela.getWidth() / 2) - 110, 225, 1);
		for (int i = 0; i < texto2.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto2.at(i));
		}
		glPopMatrix();
	}

	void desenhaHUD(windowSettings dadosJanela, int vidas, int pontuacao) {
		if (vidas > 1) {
			glColor3f((GLfloat)1.0, (GLfloat)1.0, (GLfloat)1.0);
		}
		else {
			glColor3f((GLfloat)1.0, (GLfloat)0.0, (GLfloat)0.0);
		}
		std::string textoVidas = "VIDAS :  ";
		std::string vidasAtuais = to_string(vidas);
		std::string pontAtual = to_string(pontuacao);
		glPushMatrix();

		glColor3f((GLfloat)1.0, (GLfloat)1.0, (GLfloat)0.0);
		glRasterPos3f(100, dadosJanela.getSpacingBlackBars() / 2 - 10, 1);
		glLineWidth(2);
		glTranslatef(100, dadosJanela.getSpacingBlackBars() / 2 - 10, 1);

		glScalef(0.2, 0.2, 1);
		for (int i = 0; i < pontAtual.size(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, pontAtual.at(i));
		}
		glPopMatrix();

		glPushMatrix();
		glColor3f((GLfloat)1.0, (GLfloat)1.0, (GLfloat)1.0);
		glRasterPos3f(dadosJanela.getWidth() - 125, dadosJanela.getSpacingBlackBars() / 2 - 10, 1);
		glLineWidth(2);
		glTranslatef(dadosJanela.getWidth() - 250, dadosJanela.getSpacingBlackBars() / 2 - 10, 1);
		glScalef(0.2, 0.2, 1);

		for (int i = 0; i < textoVidas.size(); i++) {
			if (textoVidas[i] <= 127 && textoVidas[i] >= 32) {
				glutStrokeCharacter(GLUT_STROKE_ROMAN, textoVidas[i]);
			}
		}

		for (int i = 0; i < vidasAtuais.size(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, vidasAtuais[i]);
		}

		glPopMatrix();
	}

	void desenhaTelaVitoria(windowSettings dadosJanela, int pontuacao) {

		std::string textoVitoria = "VITORIA";
		std::string textoVitoria2 = "VOCE VENCEU!";
		std::string textoVitoria3 = "PARABENS!!!!"; 
		std::string texto1 = "[ P ] PLAY AGAIN";
		std::string texto2 = "[ ESC ] EXIT GAME";
		std::string textoVitoria4 = "Pontuacao:		";
		std::string pontAtual = to_string(pontuacao);
		
		glPushMatrix();
		glColor3f((GLfloat)1.0, (GLfloat)1.0, (GLfloat)0.0);
		glRasterPos3f(150, dadosJanela.getHeight() - 75, 1);
		glLineWidth(5);
		glTranslatef(200, dadosJanela.getHeight() - 100, 1);
		glScalef(0.5, 0.5, 1);
		for (int i = 0; i < textoVitoria.size(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, textoVitoria.at(i));
		}
		glPopMatrix();

		glPushMatrix();
		glRasterPos3f(200, dadosJanela.getHeight() - 200, 1);
		glLineWidth(4);
		glTranslatef(200, dadosJanela.getHeight() - 200, 1);
		glScalef(0.2, 0.2, 1);
		for (int i = 0; i < textoVitoria2.size(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, textoVitoria2.at(i));
		}
		glPopMatrix();
		
		glPushMatrix();
		glRasterPos3f(200, dadosJanela.getHeight() - 300, 1);
		glLineWidth(4);
		glTranslatef(200, dadosJanela.getHeight() - 300, 1);
		glScalef(0.2, 0.2, 1);
		for (int i = 0; i < textoVitoria3.size(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, textoVitoria3.at(i));
		}
		glPopMatrix();

		glPushMatrix();
		glRasterPos3f(200, dadosJanela.getHeight() - 400, 1);
		glTranslatef(200, dadosJanela.getHeight() - 400, 1);
		for (int i = 0; i < textoVitoria4.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, textoVitoria4.at(i));
		}
		for (int i = 0; i < pontAtual.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pontAtual.at(i));
		}
		glPopMatrix();

		glPushMatrix();
		glRasterPos3f(200, dadosJanela.getHeight() - 500, 1);
		glTranslatef(200, dadosJanela.getHeight() - 500, 1);
		for (int i = 0; i < texto1.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto1.at(i));
		}
		glPopMatrix();

		glPushMatrix();
		glRasterPos3f(200, dadosJanela.getHeight() - 550, 1);
		glTranslatef(200, dadosJanela.getHeight() - 550, 1);
		for (int i = 0; i < texto2.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto2.at(i));
		}
		glPopMatrix();



	}


};

#endif