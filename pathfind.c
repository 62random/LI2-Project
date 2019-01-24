
#include "header.h"


/**
	@file pathfinder.c Este ficheiro contém o sistema de pathfinding.
		Este sistema á baseado no algorimto  de Dijkstra, que consiste
		em preencher nodos de uma rede com grandes números, e, a partir
		do destino, indo preencher os nodos contíguos com números crescentes
		representando o número de passos a que estão do destino, de modo
		a, a partir de qualquer nodo da rede, saber se é possível chegar
		ao destino e, se possível, qual o caminho mais curto.
		Para representar a rede que é o mapa do nosso jogo utilizámos
		uma matriz de inteiros, já que o inteiro pode ser a distância ao
		destino, e as suas "coordenadas" na matriz podem corresponder às
		do jogo.
*/


/**
	\brief Esta função descobre, a partir da matriz já preenchida, da origem, e do
	 	destino do movimento, qual o próximo passo a tomar.
	@param e matriz preenchida segundo o algoritmo de dijkstra
	@param a 1ª coordenada da posição de origem
	@param b 2ª coordenada da posição de origem
	@param x 1ª coordenada da posição de destino
	@param y 1ª coordenada da posição de destino

	@returns a posição do passo a ser tomado
*/
POSICAO visit_step(int matriz[6][21], int a, int b, int x, int y) {
	POSICAO vizinho[6];
	POSICAO fret = {a, b};
	neighbours(vizinho, x, y);
	int i, x1, y1;
	for ( i = 0; i < 6; i++) {
		x1 = vizinho[i].x;
		y1 = vizinho[i].y;
		if (matriz[x1][y1] == 1){
			fret.x = x1;
			fret.y = y1;
			return fret;
		}
		if (matriz[x1][y1] == matriz[x][y] - 1 )
			return visit_step(matriz, a, b, x1, y1);
	}

	return fret;
}



/**
	\brief Esta função preenche recursivamente a matriz utilizada neste sistema
	 	de pathfinding de acordo com o algoritmo mencionado na descrição do módulo.
	@param e Apontador para o estado do jogo.
	@param e matriz preenchida segundo o algoritmo de dijkstra
	@param a 1ª coordenada da posição de origem
	@param b 2ª coordenada da posição de origem
	@param d distância a que o nodo a ser preenchido se encontra do destino
	@param x 1ª coordenada da posição de destino
	@param y 1ª coordenada da posição de destino
*/
void preenche_vizinhos(ESTADO * e, int matriz[6][21], int a, int b, int d, int x, int y) {

	if (d > 15)
		return;


	POSICAO vizinho[6];
	neighbours(vizinho, a, b);

	int i, a1, b1;
	matriz[a][b] = d;

	for ( i = 0; i < 6; i++) {
		a1 = vizinho[i].x;
		b1 = vizinho[i].y;
		if (posicao_valida(a1, b1) && (!posicao_ocupada(e, a1, b1) || tem_trapdoor(e, a1, b1) || tem_jogador(e, a1, b1))  && matriz[a1][b1] > d && d < 15)
			preenche_vizinhos(e, matriz, a1, b1, d + 1, x, y);

	}

}




/**
	\brief Esta função inicializa a matriz utilizada neste sistema
	 	de pathfinding e chama a função que a preenche.
	@param e Apontador para o estado do jogo.
	@param e matriz preenchida segundo o algoritmo de dijkstra
	@param a 1ª coordenada da posição de origem
	@param b 2ª coordenada da posição de origem
	@param x 1ª coordenada da posição de destino
	@param y 1ª coordenada da posição de destino
*/
void preenche_matriz(ESTADO * e, int matriz[6][21], int a, int b, int x, int y) {
	int i, j;
	for (i = 0; i< 6; i++)
		for (j = 0; j < 21; j++)
			matriz[i][j] = 1000;

	preenche_vizinhos(e, matriz, a, b, 0, x, y);

}







/**
	\brief Esta função condiciona a  matriz do algoritmo de pathfinding de acordo
		com as casas que podem ser atacadas por inimigos. Estas casas deixam
		de ser selecináveis como próximo passo a tomar.
	@param e Apontador para o estado do jogo.
	@param e matriz preenchida segundo o algoritmo de dijkstra
*/
void matriz_condicionada_ataques(ESTADO * e, int matriz[6][21]) {
	int id, i, j, x, y;

	for (id = 0; id < e->num_inimigos;id++) {
		x = e->inimigo[id].pos.x;
		y = e->inimigo[id].pos.y;

		if (e->inimigo[id].type == 'm') {
			for (i = -2; i <= 2; i++)
				for (j = -2; j <= 2; j++)
					if( posicao_valida(x+i, y+ j) && short_range(x, y, x + i, y + j)
					&& ( i!= 0 || j != 0) && ((x + i) != e->jog.pos.x || (y + j) != e->jog.pos.y))
						matriz[x + i][y + j] = 1000;
		}
		else {
			for (i = -10; i<=10; i++)
				for(j = -10; j <= 10; j++)
					if(posicao_valida(x+i, y+ j) && ( i!= 0 || j != 0)
					&& dist_casas(x, y, x + i, y + j) < 6
					&& cords_line(x, y, x + i, y + j) && ((x + i) != e->jog.pos.x || (y + j) != e->jog.pos.y))
						matriz[x + i][y + j] = 1000;
		}
	}
}





/**
	\brief Esta função, a partir do estado do jogo, uma origem e um destino,
		averigua qual o primeiro passo do caminho mais curto a tomar
		para chegar ao destino.
	@param e Apontador para o estado do jogo.
	@param a 1ª coordenada da posição de origem
	@param b 2ª coordenada da posição de origem
	@param x 1ª coordenada da posição de destino
	@param y 1ª coordenada da posição de destino

	@returns a posição do passo a ser tomado
*/
POSICAO step(ESTADO *e, int a, int b, int x, int y) {
	int matriz[6][21];
	preenche_matriz(e, matriz, a, b, x, y);


	return visit_step(matriz, a, b, x, y);
}



/**
	\brief Esta função implementa o algoritmo de pathfinding condicionado
		pelas casas que podems er atacadas por inimigos.
	@param e Apontador para o estado do jogo.
	@param a 1ª coordenada da posição de origem
	@param b 2ª coordenada da posição de origem
	@param x 1ª coordenada da posição de destino
	@param y 1ª coordenada da posição de destino

	@returns a posição do passo a ser tomado
*/
POSICAO step_condicionado(ESTADO *e, int a, int b, int x, int y) {
	int matriz[6][21];
	preenche_matriz(e, matriz, a, b, x, y);

	matriz_condicionada_ataques(e, matriz);

	return visit_step(matriz, a, b, x, y);
}
