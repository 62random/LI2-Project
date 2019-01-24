#include "header.h"

/**
	@file battle.c Este ficheiro contém a implementação do sistema de combate
		(unilateral, dado que este apenas gere ataques feitos pelo jogador
		a NPC's)
*/


/**
	\brief Apaga um obstáculo da estrutura do estado.
	@param e Apontador para o estado do jogo.
	@param n número identificador do obstáculo na estrutura do jogo
*/
void delete_obstaculo(ESTADO *e, int n) {
	int i;
	for (i = n; i < e->num_obstaculos; i++)
		e->obstaculo[i] = e->obstaculo[i+1];
	e->num_obstaculos--;
}

/**
	\brief Apaga um inimigo da estrutura do estado.
	@param e Apontador para o estado do jogo.
	@param n número identificador do inimigo na estrutura do jogo
*/
void delete_inimigo(ESTADO *e, int n) {
	int i;
	for (i = n; i < e->num_inimigos; i++)
		e->inimigo[i] = e->inimigo[i+1];
	e->num_inimigos--;
}


/**
	\brief Gere o ataque ao NPC numa casa (i.e. inimigo, obstáculo)
	@param e Apontador para o estado do jogo.
	@param x 1ª coordenada
	@param y 2ª coordenada
*/
void attack(ESTADO *e, int x, int y) {
	int index;
	if (tem_inimigo(e, x, y)) {
		index = inimigo_cord(e, x, y);
		e->jog.exp += e->inimigo[index].exp;
		e->inimigo[index].hp--;
		if (e->inimigo[index].hp == 0)
			delete_inimigo(e, index);
	}
	else if (tem_obstaculo(e, x, y)) {
		index = obstaculo_cord(e, x, y);
		e->obstaculo[index].hp--;
		if (e->obstaculo[index].hp == 0)
			delete_obstaculo(e, index);
	}
		if(e->jog.last != 'b')
			e->jog.last = 'a';
}
