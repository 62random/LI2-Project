/**
@file cgi.h
Macros úteis para gerar CGIs
*/

#include <stdio.h>




/**
* Caminho para as imagens
*/
#define IMAGE_PATH							"http://localhost/images/"

/**
\brief Macro para começar o html
*/
#define COMECAR_HTML						printf("Content-Type: text/html\n\n")

/**
\brief Macro para abrir um svg
@param tamx O comprimento do svg
@param tamy A altura do svg
*/
#define ABRIR_SVG(tamx, tamy)				printf("<svg width=%d height=%d>\n", tamx, tamy)
/**
\brief Macro para fechar um svg
*/
#define FECHAR_SVG							printf("</svg>\n")


/**
\brief Macro para criar uma imagem
@param X A coordenada X do canto superior esquerdo
@param Y A coordenada Y do canto superior esquerdo
@param ESCALA A escala da imagem
@param FICHEIRO O caminho para o link do ficheiro
*/
#define IMAGEM(X, Y, ESCALA, FICHEIRO)		printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", \
												ESCALA * X, ESCALA* Y, ESCALA, ESCALA, IMAGE_PATH FICHEIRO)


/**
\brief Macro para criar uma imagem quadrada cuja posição não está relacionada com o lado
@param X A coordenada X do canto superior esquerdo
@param Y A coordenada Y do canto superior esquerdo
@param TAM A escala da imagem
@param FICHEIRO O caminho para o link do ficheiro
*/
#define IMAGEM_1(X, Y, TAM, FICHEIRO)	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", \
												X, Y, TAM, TAM, IMAGE_PATH FICHEIRO)

/**
\brief Macro para criar uma imagem retangular
@param X A coordenada X do canto superior esquerdo
@param Y A coordenada Y do canto superior esquerdo
@param TAMX A escala da imagem
@param TAMY A escala da imagem
@param FICHEIRO O caminho para o link do ficheiro
*/
#define IMAGEM_2(X, Y, TAMX, TAMY, FICHEIRO)	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", \
												X, Y, TAMX, TAMY, IMAGE_PATH FICHEIRO)


/**
\brief Macro para criar um retangulo
@param X A coordenada X do canto superior retangulo
@param Y A coordenada Y do canto superior retangulo
@param LAR A largura do retangulo
@param AL A altura do retangulo
@param COR A cor de preenchimento do retangulo
*/
#define QUADRADO(X, Y, ESCALA, COR)			printf("<rect x=%d y=%d width=%d height=%d fill=%s />\n", \
												ESCALA * X, ESCALA* Y, ESCALA, ESCALA, COR)
/**
\brief Macro para criar um quadrado
@param X A coordenada X do canto superior esquerdo
@param Y A coordenada Y do canto superior esquerdo
@param ESCALA A escala do quadrado
@param COR A cor de preenchimento do quadrado
*/
#define RECTANGULO(X, Y, LAR, AL, COR)				printf("<rect x=%d y=%d width=%d height=%d fill=%s />\n", \
												X,  Y, LAR, AL, COR)







/**
\brief Macro para abrir um link
@param link O caminho para o link
*/
#define ABRIR_LINK(link, id)					printf("<a id=\"%s\" xlink:href=%s>\n", id, link)

/**
\brief Macro para fechar o link
*/
#define FECHAR_LINK							printf("</a>\n")
