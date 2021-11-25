//#include "tela.hpp"
//#include <string>
////#include <SOIL2/SOIL2.h>
//
//void Tela::desenhaMenu(windowSettings dadosJanela)
//{
//	std::string texto1 = "[ P ] START GAME";
//	std::string texto2 = "[ S ] SELECT CHARACTER";
//	std::string texto3 = "[ ESC ] EXIT GAME";
//
//	int i = 0;
//
//	glColor3f(0, 0, 0);
//	//glEnable(GL_TEXTURE_2D);
//	//glBindTexture(GL_TEXTURE_2D, idTexturaCena);
//
//	glBegin(GL_POLYGON);
//	//glTexCoord2f(0, 0);
//		glVertex3f(0.0, 0.0, 0.0);
//		//glTexCoord2f(1, 0);
//		glVertex3f(dadosJanela.getWidth(),0.0, 0.0);
//		//glTexCoord2f(1, 1);
//		glVertex3f(dadosJanela.getWidth(), dadosJanela.getHeight(), 0.0);	
//		//glTexCoord2f(0, 1);
//		glVertex3f(0.0, dadosJanela.getHeight(), 0.0);
//	glEnd();
//
//	glRasterPos2f(350, 350, 1);
//	for (i; i < texto1.size(); i++) {
//		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,texto1.at(i));
//	}
//
//	//glDisable(GL_TEXTURE_2D); //encerra o "desenha da textura"
//}
