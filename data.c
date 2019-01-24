#include "header.h"
#include <math.h>



/**
@file data.c Este ficheiro contém um conjunto de funções bastante elementares, que
	se revelam úteis numa grande variedade de partes do projeto.
*/


/**
	\brief Testa se um dado conjunto de coordenadas representam uma posição válida.
	@param x 1ª coordenada
	@param y 2ª coordenada

	@returns 1 se verdadeiro, 0 se falso
*/
int posicao_valida(int x, int y) {
	if (y < 0 || x < 0)
		return 0;

	if (y <= TAM)
		if (x > y)
			return 0;

	if (y <= 3 * TAM) {
		if (y%2 == 1) {
			if (x > TAM)
				return 0;
		}
		else
			if (x > TAM -1)
				return 0;
	}

	if (x > TAM*4 - y)
		return 0;

	return 1;
}


/**
	\brief Testa se um dado conjunto de coordenadas representam uma dada posição.
	@param a posição
	@param x 1ª coordenada
	@param y 2ª coordenada

	@returns 1 se verdadeiro, 0 se falso
*/
int posicao_igual(POSICAO a, int x, int y) {
	return a.x == x && a.y == y;
}



/**
	\brief Testa se um dado conjunto de coordenadas representam a posição
		ocupada pelo jogador.
	@param e Apontador para o estado do jogo.
	@param x 1ª coordenada
	@param y 2ª coordenada

	@returns 1 se verdadeiro, 0 se falso
*/
int tem_jogador(ESTADO *e, int x, int y) {
	return posicao_igual(e->jog.pos, x, y);
}



/**
	\brief Testa se um dado conjunto de coordenadas representam uma posição
		ocupada por um inimigo.
	@param e Apontador para o estado do jogo.
	@param x 1ª coordenada
	@param y 2ª coordenada

	@returns 1 se verdadeiro, 0 se falso
*/
int tem_inimigo(ESTADO *e, int x, int y) {
	int i;
	for (i = 0; i < e->num_inimigos; i++)
		if (posicao_igual(e->inimigo[i].pos, x, y))
			return 1;
	return 0;
}


/**
	\brief Testa se um dado conjunto de coordenadas representam uma posição
		ocupada por um obstáculo.
	@param e Apontador para o estado do jogo.
	@param x 1ª coordenada
	@param y 2ª coordenada

	@returns 1 se verdadeiro, 0 se falso
*/
int tem_obstaculo(ESTADO *e, int x, int y) {
	int i;
	for (i = 0; i < e->num_obstaculos; i++)
		if (posicao_igual(e->obstaculo[i].pos, x, y))
			return 1;
	return 0;
}


/**
	\brief Testa se um dado conjunto de coordenadas representam a posição
		ocupada pela trapdoor.
	@param e Apontador para o estado do jogo.
	@param x 1ª coordenada
	@param y 2ª coordenada

	@returns 1 se verdadeiro, 0 se falso
*/
int tem_trapdoor(ESTADO *e, int x, int y) {
	return (e->trapdoor.x == x && e->trapdoor.y == y);
}


/**
	\brief Testa se um dado conjunto de coordenadas representam uma posição
		ocupada.
	@param e Apontador para o estado do jogo.
	@param x 1ª coordenada
	@param y 2ª coordenada

	@returns 1 se verdadeiro, 0 se falso
*/
int posicao_ocupada(ESTADO *e, int x, int y) {
	return tem_jogador(e, x, y)
		|| tem_inimigo(e, x, y)
		|| tem_obstaculo(e, x, y)
		|| tem_trapdoor(e, x, y);

}



/**
	\brief Testa se um dado conjunto de coordenadas se encontram num raio
		de 5 casas do jogador.
	@param e Apontador para o estado do jogo.
	@param x 1ª coordenada
	@param y 2ª coordenada

	@returns 1 se verdadeiro, 0 se falso
*/
int jogador_perto(ESTADO *e, int x, int y) {
	return (e->jog.pos.x - x)*(e->jog.pos.x - x) +
	       (e->jog.pos.y - y)*(e->jog.pos.y - y)
	       		<= 25;
}


/**
	\brief Devolve, a partir de um conjunto de coordenadas, o número identificador
		de um obstáculo
	@param e Apontador para o estado do jogo.
	@param x 1ª coordenada
	@param y 2ª coordenada

	@returns índice do obstáculo na estrutura
*/
int obstaculo_cord(ESTADO *e, int x, int y) {
	int i;
	for (i = 0; i< e->num_obstaculos; i++)
		if (x == e->obstaculo[i].pos.x && y == e->obstaculo[i].pos.y)
			return i;
	return 0;
}



/**
	\brief Devolve, a partir de um conjunto de coordenadas, o número identificador
		de um inimigo
	@param e Apontador para o estado do jogo.
	@param x 1ª coordenada
	@param y 2ª coordenada

	@returns índice do inimigo na estrutura
*/
int inimigo_cord(ESTADO *e, int x, int y) {
	int i;
	for (i = 0; i< e->num_inimigos; i++)
		if (x == e->inimigo[i].pos.x && y == e->inimigo[i].pos.y)
			return i;

	return 0;
}



/**
	\brief Devolve o quadrado da distância entre posições definidas por depois
		dados pares de coordenadas. (útil apenas para comparações)
	@param x1 1ª coordenada
	@param y1 2ª corodenada
	@param x2 1ª coordenada
	@param y2 2ª coordenada

	@returns quadrado da distância entre as posições
*/
int dist(int x1, int y1, int x2, int y2) {
	return (x1-x2)*(x1-x2) + (y1 - y2)*(y1 - y2);
}


/**
	\brief Devolve a distância (em casas do mapa) que separa duas dadas
		posições.
	@param x1 1ª coordenada
	@param y1 2ª corodenada
	@param x2 1ª coordenada
	@param y2 2ª coordenada

	@returns distância entre as posições
*/
int dist_casas(int x1, int y1, int x2, int y2) {
	int a = get_posx(x1, y1);
	int b = get_posy( y1);
	int c = get_posx(x2, y2);
	int d = get_posy( y2);
	float l = dist(a, b, c, d);
	l = sqrt(l)/(sqrt(3)*0.5*ESCALA);
	return round(l);
}


/**
	\brief Função que averigua se duas casas são vizinhas uma da outra
	@param x1 1ª coordenada
	@param y1 2ª corodenada
	@param x2 1ª coordenada
	@param y2 2ª coordenada

	@returns 1 se verdadeiro, 0 se falso
*/
int short_range(int x1, int y1, int x2, int y2) {
	int a = get_posx(x1, y1);
	int b = get_posy( y1);
	int c = get_posx(x2, y2);
	int d = get_posy( y2);

	if ( dist(a, b, c, d) < ESCALA*ESCALA )
		return 1;

	return 0;
}


/**
	\brief Averigua se duas casas estão são "semi-vizinhas", ou seja
		se entre elas há apenas uma casa.
	@param x1 1ª coordenada
	@param y1 2ª corodenada
	@param x2 1ª coordenada
	@param y2 2ª coordenada

	@returns 1 se verdadeiro, 0 se falso
*/
int double_range(int x1, int y1, int x2, int y2) {
	int a = get_posx(x1, y1);
	int b = get_posy( y1);
	int c = get_posx(x2, y2);
	int d = get_posy( y2);

	if ( dist(a, b, c, d) < 4*ESCALA*ESCALA)
		return 1;

	return 0;
}


/**
	\brief Função que testa se duas casas estão alinhadas de forma oblíqua.
	@param x1 1ª coordenada
	@param y1 2ª corodenada
	@param x2 1ª coordenada
	@param y2 2ª coordenada

	@returns 1 se verdadeiro, 0 se falso
*/
int cords_obliqua(int x1, int y1, int x2, int y2) {
	int a = get_posx(x1, y1);
	int b = get_posy(y1);
	int c = get_posx(x2, y2);
	int d = get_posy(y2);
	float tang = (float)(d - b)/(c - a);
	return (tang*tang*3 - 1 < 0.1 && tang*tang*3  - 1 > -0.1);
}

/**
	\brief Testa se duas casas estão alinhadas verticalmente.
	@param x1 1ª coordenada
	@param y1 2ª corodenada
	@param x2 1ª coordenada
	@param y2 2ª coordenada

	@returns 1 se verdadeiro, 0 se falso
*/
int cords_vertical(int x1, int y1, int x2, int y2) {
	int a = get_posx(x1, y1);
	int c = get_posx(x2, y2);
	return (a - c > -5 && a - c < 5);
}

/**
	\brief Função que testa se duas casas estão alinhadas nas direções
		perpendiculares aos lados do hexágono (vertical ou obliquamente)
	@param x1 1ª coordenada
	@param y1 2ª corodenada
	@param x2 1ª coordenada
	@param y2 2ª coordenada

	@returns 1 se verdadeiro, 0 se falso
*/
int cords_line(int x1, int y1, int x2, int y2) {
	return ( cords_vertical(x1, y1, x2, y2) ||
		 cords_obliqua( x1, y1, x2, y2) );
}


/**
	\brief Função que devolve a menor das diferenças entre a reta que passa
	 	por estas duas casas e uma reta vertical ou uma reta oblíqua
		(com inclinação de 30º em relação à horizontal)
	@param x1 1ª coordenada
	@param y1 2ª corodenada
	@param x2 1ª coordenada
	@param y2 2ª coordenada

	@returns ângulo mínimo que separa a linha entre as duas casas da uma linha
		vertical ou oblíqua (30 ou -30º)
*/
float diff_angular(int x1, int y1, int x2, int y2) {
	int a = get_posx(x1, y1);
	int b = get_posy(y1);
	int c = get_posx(x2, y2);
	int d = get_posy( y2);
	float tang = (float)(d - b)/(c - a);
	float ang = atan(tang);
	float dif1 = PI/2 > ang ? PI/2 - ang : ang - PI/2;
	float dif2 = PI/6 > ang ? PI/6 - ang : ang - PI/6;

	if (dif1 < dif2)
		return dif1;
	else
		return dif2;

}


/**
	\brief Esta função preenche um dado array de posições com as casas
		vizinhas da casa representada por umas dadas coordenadas.
	@param nbrs array de posições a serem preenchidas com os vizinhos
	@param x2 1ª coordenada
	@param y2 2ª coordenada
*/
void neighbours(POSICAO* nbrs, int x, int y) {

	int i, j, arraypos = 0;
	for (i = -2; i <= 2; i++)
		for (j = -2; j <= 2; j++)
			if ( short_range(x, y, x + i, y + j) && (i != 0 || j != 0) &&
			      posicao_valida(x+i, y+j)) {
				      nbrs[arraypos].x = x+i;
				      nbrs[arraypos].y = y+j;
				      arraypos++;
			      }

	for(;arraypos < 6; arraypos++)
		nbrs[arraypos].x = nbrs[arraypos].y = -1; /*coloca uma posição inválida nos elementos do array desnecessários*/


}




/**
	\brief Esta função preenche um dado array de posições com as casas
		a duas casas de distância da casa representada por umas dadas coordenadas.
	@param nbrs array de posições a serem preenchidas com os vizinhos
	@param x2 1ª coordenada
	@param y2 2ª coordenada
*/
void halfneighbours(POSICAO* nbrs, int x, int y) {

	int i, j, arraypos = 0;
	for (i = -4; i <= 4; i++)
		for (j = -4; j <= 4; j++)
			if ( double_range(x, y, x + i, y + j) && !short_range(x, y, x +i, y + j)
			&& (i != 0 || j != 0) && posicao_valida(x+i, y+j)) {
				      nbrs[arraypos].x = x+i;
				      nbrs[arraypos].y = y+j;
				      arraypos++;
			      }

	for(;arraypos < 12; arraypos++)
		nbrs[arraypos].x = nbrs[arraypos].y = -1; /*coloca uma posição inválida nos elementos do array desnecessários*/


}








/**
	\brief Esta função indica se uma dada posição pode ser atacada por um
		inimigo.
	@param e Apontador para a estrutura do estado do jogo.
	@param a 1ª coordenada
	@param b 2ª coordenada

	@returns 1 se é atacada, 0 caso contrário
*/
int isattckable(ESTADO* e, int a, int b) {
	int id, x, y;

	for (id = 0; id < e->num_inimigos;id++) {
		x = e->inimigo[id].pos.x;
		y = e->inimigo[id].pos.y;

		if (e->inimigo[id].type == 'm') {
			if(short_range(x, y, a, b))
				return 1;
		}
		else {
			if(dist_casas(x, y, a, b) < 6 && cords_line(x, y, a, b)
			&& dist_casas(x, y, a, b) > 1)
				return 1;
		}

	}

	return 0;
}


/**
	\brief Esta função indica se uma dada posição pode ser atacada por um
		arqueiro (enão qualquer inimigo).
	@param e Apontador para a estrutura do estado do jogo.
	@param a 1ª coordenada
	@param b 2ª coordenada

	@returns 1 se é atacada, 0 caso contrário
*/
int archer_range ( ESTADO* e, int a, int b) {
	int id, x, y;

	for (id = 0; id < e->num_inimigos;id++) {
		x = e->inimigo[id].pos.x;
		y = e->inimigo[id].pos.y;

		if (e->inimigo[id].type == 'a')
			if(dist_casas(x, y, a, b) < 6 && cords_line(x, y, a, b)
			&& dist_casas(x, y, a, b) > 1)
				return 1;

	}

	return 0;
}
