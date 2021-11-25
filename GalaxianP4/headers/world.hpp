#ifndef WORLD_H
#define WORLD_H
#include "util.hpp"
#include <iostream>
#include <SOIL2/SOIL2.h>
using namespace std;

GLuint idTexturaCena = 0;
GLint ordemAnimacaoCenario = 1;

GLuint carregaTextura2D(string arquivo) {
	idTexturaCena = SOIL_load_OGL_texture(arquivo.c_str(), SOIL_LOAD_AUTO, idTexturaCena, SOIL_FLAG_INVERT_Y);

	if (idTexturaCena == 0)
	{
		printf("Erro ao carregar textura: '%s'\n", SOIL_last_result());
		return idTexturaCena;
	}

	return idTexturaCena;
}

void atualizaCenario(int fase, string texturaFase) {
	char numString[3];
	char caminho[100];
	int limite = 0;
	strcpy_s(caminho, "");
	sprintf_s(numString, sizeof(numString), "%d", ordemAnimacaoCenario++);

	strcat_s(caminho, "res/SpriteCenario/"); //Atualizar o caminho de acordo com a fase
	strcat_s(caminho, texturaFase.c_str());
	strcat_s(caminho, "/frame-");

	switch (fase)
	{
	case 1:

		limite = 24;

		break;

	case 2:

		limite = 4;

		break;
	case 3:

		limite = 8;

		break;

	case 4:

		limite = 8;
		break;

	default:
		break;
	}

	if (ordemAnimacaoCenario > limite)
	{
		ordemAnimacaoCenario = 1;
	}

	strcat_s(caminho, numString);
	strcat_s(caminho, ".gif");
	carregaTextura2D(caminho);

	return;
}

void desenhaBlackBars(windowSettings dadosJanela, colorPalette corBlackBars) {
	glColor3f(corBlackBars.getColorR(), corBlackBars.getColorG(), corBlackBars.getColorB());

	glBegin(GL_POLYGON);
	glVertex3f(0.0, dadosJanela.getHeight(), 0.0);
	glVertex3f(dadosJanela.getWidth(), dadosJanela.getHeight(), 0.0);
	glVertex3f(dadosJanela.getWidth(), (dadosJanela.getHeight() - dadosJanela.getSpacingBlackBars()), 0.0);
	glVertex3f(0.0, (dadosJanela.getHeight() - dadosJanela.getSpacingBlackBars()), 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(dadosJanela.getWidth(), 0.0, 0.0);
	glVertex3f(dadosJanela.getWidth(), dadosJanela.getSpacingBlackBars(), 0.0);
	glVertex3f(0.0, dadosJanela.getSpacingBlackBars(), 0.0);
	glEnd();

}

void desenhaTelaPrincipal(windowSettings dadosJanela, colorPalette corPrincipal) {
	//Definindo uma paleta de cores para o fundo da tela, no caso é amarelo dourado
	colorPalette corDeFundo(1.000, 0.843, 0.000, 0.000);
	glClearColor(corDeFundo.getColorR(),
		corDeFundo.getColorG(),
		corDeFundo.getColorB(),
		corDeFundo.getColorAlpha());

	glColor3f(1, 1, 1);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, idTexturaCena);

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(50.0, dadosJanela.getSpacingBlackBars() + 10.0, 1.0);
	glTexCoord2f(1, 0);
	glVertex3f((dadosJanela.getWidth() - dadosJanela.getSpacingBlackBars() - 10.0), dadosJanela.getSpacingBlackBars() + 10.0, 1.0);
	glTexCoord2f(1, 1);
	glVertex3f((dadosJanela.getWidth() - dadosJanela.getSpacingBlackBars() - 10.0),
		(dadosJanela.getHeight() - dadosJanela.getSpacingBlackBars() - 10.0), 1.0);
	glTexCoord2f(0, 1);
	glVertex3f(50.0, (dadosJanela.getHeight() - dadosJanela.getSpacingBlackBars() - 10.0), 1.0);
	glEnd();

	glDisable(GL_TEXTURE_2D); //encerra o "desenha da textura"
}

void desenhaTexto(windowSettings dadosJanela, colorPalette corDoTexto, string input, int tipo) {
	glColor3f(corDoTexto.getColorR(),
		corDoTexto.getColorG(),
		corDoTexto.getColorB());
	//Texto @2021 Atari
	if (tipo == -1) {
		glRasterPos3f(dadosJanela.getWidth() / 2 - 125.0, dadosJanela.getHeight() - (dadosJanela.getSpacingBlackBars() / 2) - 5.0, 1);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '@');
		glPushMatrix();
		glLineWidth(5);
		glTranslatef(dadosJanela.getWidth() / 2 - 100, dadosJanela.getHeight() - (dadosJanela.getSpacingBlackBars() / 2) - 10, 1);
		glScalef(0.3, 0.3, 1);

		for (int i = 0; i < input.size(); i++) {
			if (input[i] <= 127 && input[i] >= 32) {
				glutStrokeCharacter(GLUT_STROKE_ROMAN, input[i]);
			}
			else {
				cout << "Caracter nao suportado:    " << (int)input[i] << endl;
			}
		}
		glPopMatrix();
	}

}
#endif