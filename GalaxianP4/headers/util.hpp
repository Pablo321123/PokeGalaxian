#ifndef UTIL_H
#define UTIL_H

#define WORLD_SIZE_W  800
#define WORLD_SIZE_H  600
/*
Autor : Paulo Lopes Do Nascimento
*/
//Struct com as variáveis pertinentes à janela

class windowSettings {
	GLfloat width, height, spacingBlackBars;
	
	public:
		windowSettings(GLfloat w, GLfloat h, GLfloat sbb) {
			width = w;
			height = h;
			spacingBlackBars = sbb;
		}
		windowSettings(int w, int h) {
			width = (GLfloat)w;
			height = (GLfloat)h;
		}
		windowSettings() {}
		GLfloat getWidth() { return width; }
		GLfloat getHeight() { return height; }
		GLfloat getSpacingBlackBars() { return spacingBlackBars; }
		void setWidth(GLfloat w) { width = w; }
		void setHeight(GLfloat h) { height = h; }
		void setSpacingBlackBars(GLfloat sbb) { spacingBlackBars = sbb; }
};
//Struct com as variáveis pertinentes à paleta de cores
class colorPalette {
	GLclampf clearColorR;
	GLclampf clearColorG;
	GLclampf clearColorB;
	GLclampf clearColorAlpha;

	public:
		colorPalette(GLclampf r, GLclampf g, GLclampf b, GLclampf alpha) {
			clearColorR = r;
			clearColorG = g;
			clearColorB = b;
			clearColorAlpha = alpha;
		}
		colorPalette() {}
		GLclampf getColorR() { return clearColorR; }
		GLclampf getColorG() { return clearColorG; }
		GLclampf getColorB() {	 return clearColorB; }
		GLclampf getColorAlpha() { return clearColorAlpha; }
		void setColorR(GLclampf r) { clearColorR = r; }
		void setColorG(GLclampf g) { clearColorG = g; }
		void setColorB(GLclampf b) { clearColorB = b; }
		void setColorAlpha(GLclampf alpha) { clearColorAlpha = alpha; }
};
//Função que retorna o tamanho de uma string definida como const char*
int stringSize(const char* string1){
	int aux = 0;
	while (string1[aux] != '\0') {
		aux++;
	}
	return aux;
}
#endif