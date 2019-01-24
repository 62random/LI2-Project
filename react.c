#include "header.h"

/**
	@file react.c Este ficheiro contém o conjunto de funções que são chamadas
		ao aplicar ao estado do jogo o movimento que o jogador pretende
		efetuar. Ou seja, efetua-se o movimento do jogador, e de seguida
		chama-se a função react (e as outras funções deste módulo, consequentemente).
*/


/**
	\brief Esta função efetua o movimento dos arqueiros inimigos.
	@param e Apontador para o estado do jogo.
	@param n Número identificador do inimigo, na estrutura do estado do jogo.
*/
void move_inimigo_a(ESTADO *e, int n) {
	int i, j;
	int x1 = e->jog.pos.x;
	int y1 = e->jog.pos.y;
	int x2 = e->inimigo[n].pos.x;
	int y2 = e->inimigo[n].pos.y;
	float m = diff_angular(x1, y1, x2, y2);
	int a = x2, b = y2;


	if (!short_range(x1, y1, x2, y2)) {
		for (i = -2; i<= 2; i++)
			for (j = -2; j <= 2; j++)
				if (short_range(x2, y2, x2 + i, y2 + j)
				&&  posicao_valida(x2 + i, y2 + j)
				&& !posicao_ocupada(e, x2 + i, y2 + j)
				&&  diff_angular(x1, y1, x2 + i, y2 + j) < m ) {
					m = diff_angular(x1, y1, x2 + i, y2 + j);
					a = x2 + i;
					b = y2 + j;
				}
	}
	else {
		m = 1;
		for (i = -2; i<= 2; i++)
			for (j = -2; j <= 2; j++)
				if (short_range(x2, y2, x2 + i, y2 + j)
				&&  posicao_valida(x2 + i, y2 + j)
				&& !posicao_ocupada(e, x2 + i, y2 + j)
				&& !short_range(x1, y1, x2 + i, y2 + j)
				&&  diff_angular(x1, y1, x2 + i, y2 + j) < m) {
					m = diff_angular(x1, y1, x2 + i, y2 + j);
					a = x2 + i;
					b = y2 + j;
				}

	}

	e->inimigo[n].prevpos = e->inimigo[n].pos;
	e->inimigo[n].pos.x = a;
	e->inimigo[n].pos.y = b;
	e->inimigo[n].last = 'm';

}





/**
	\brief Esta função gere a próxima ação de uma dado arqueiro inimigo.
	@param e Apontador para o estado do jogo.
	@param n Número identificador do inimigo, na estrutura do estado do jogo.
*/
void react_inimigo_a(ESTADO *e, int n) {
	int x1 = e->jog.pos.x;
	int y1 = e->jog.pos.y;
	int x2 = e->inimigo[n].pos.x;
	int y2 = e->inimigo[n].pos.y;
	if ( !short_range(x1, y1, x2, y2) && cords_line(x1, y1, x2, y2) && dist_casas(x1, y1, x2, y2) < 6) {
		e->jog.hp--;
		e->inimigo[n].last = 'a';
		e->inimigo[n].prevpos = e->inimigo[n].pos;
	}
	else
		move_inimigo_a(e, n);
}


/**
	\brief Esta função efetua o movimento dos inimigos melee.
	@param e Apontador para o estado do jogo.
	@param n Número identificador do inimigo, na estrutura do estado do jogo.
*/
void move_inimigo_m(ESTADO *e, int n) {
	int x, y, a, b;
	x = e->jog.pos.x;
	y = e->jog.pos.y;
	a = e->inimigo[n].pos.x;
	b = e->inimigo[n].pos.y;

	e->inimigo[n].prevpos = e->inimigo[n].pos;
	e->inimigo[n].pos = step(e, a, b, x, y);
	e->inimigo[n].last = 'm';

}




/**
	\brief Esta função gere a próxima ação de um dado inimigo melee.
	@param e Apontador para o estado do jogo.
	@param n Número identificador do inimigo, na estrutura do estado do jogo.
*/
void react_inimigo_m(ESTADO *e, int n) {
	int x1 = e->jog.pos.x;
	int y1 = e->jog.pos.y;
	int x2 = e->inimigo[n].pos.x;
	int y2 = e->inimigo[n].pos.y;
	if ( short_range(x1, y1, x2, y2) ) {
		e->jog.hp--;
		e->inimigo[n].last = 'a';
		e->inimigo[n].prevpos = e->inimigo[n].pos;
	}
	else
		move_inimigo_m(e, n);

}


/**
	\brief Esta função gere as ações que os inimigos terão em resposta ao
		movimento ou ataque do jogador.
	@param e Apontador para o estado do jogo.
*/
void react_inimigos(ESTADO *e) {
	int i;
	for(i = 0; i < e->num_inimigos;i++) {
		if (e->inimigo[i].type == 'm')
			react_inimigo_m(e, i);
		if (e->inimigo[i].type == 'a')
			react_inimigo_a(e, i);
	}


}

/**
	\brief Esta função gere a atualização, ou reação, como sugere o nome,
		do estado do jogo após uma jogada.
	@param e Apontador para o estado do jogo.

*/
void react(ESTADO *e) {

	react_inimigos(e);
}
