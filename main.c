#include <time.h>

#include "header.h"

/**
	@file main.c Este ficheiro contém o "fluxo" principal do programa, ou seja,
	uma vista geral de todo o processamento feito para gerar a página do jogo.
*/



/*+++++++++++++++++++++++++++++++INICIALIZAR ESTADO ++++++++++++++++++++++++++++*/

/*
	Abaixo encontra-se o código que gere a inicialização do estado do jogo
	a cada nível.
*/


/**
	\brief Gera a informação sobre cada inimigo, no início de cada nível.
	@param e Apontador para o estado do jogo.
	@param type Char que representa o tipo de inimigo.(i.e. melee, archer)
*/
void inicializar_inimigo(ESTADO *e, char type) {
	int x, y;
	do {
		x = random() % 5;
		y = random() % 17;
	} while(!posicao_valida(x, y) || posicao_ocupada(e, x, y));

	e->inimigo[(int)e->num_inimigos].type = type;
	e->inimigo[(int)e->num_inimigos].pos.x = x;
	e->inimigo[(int)e->num_inimigos].pos.y = y;
	e->inimigo[(int)e->num_inimigos].hp    = 1;
	e->inimigo[(int)e->num_inimigos].dmg   = 1;
	e->inimigo[(int)e->num_inimigos].exp   = 1;
	e->inimigo[(int)e->num_inimigos].prevpos = e->inimigo[(int)e->num_inimigos].pos;
	e->inimigo[(int)e->num_inimigos].last   = 'm';
	(e->num_inimigos)++;

}




/**
	\brief Gera inimigos de acordo com o nível do jogo.
		com zeros.
	@param e Apontador para o estado do jogo.
*/
void inicializar_inimigos(ESTADO *e) {
	int i;
	e->num_inimigos = 0;
	for(i = 0; i < e->lvl + 1; i++)
		inicializar_inimigo(e, 'm');
	for(i = 0; i < e->lvl / 3 + 1;i++)
		inicializar_inimigo(e, 'a');
}


/**
	\brief Gera semi-aleatoriamente a posição da trapdoor para o próximonível.
		(tem de ficar no topo do mapa)
	@param e Apontador para o estado do jogo.

*/
void inicializar_trapdoor (ESTADO *e) {
	int x, y;
	do {
		x = random() % 3;
		y = random() % 4;
	} while(!posicao_valida(x, y) || posicao_ocupada(e,x,y) || jogador_perto(e, x, y));

	e->trapdoor.x = x;
	e->trapdoor.y = y;

}



/**
	\brief Gera informação relativa a cada obstáculo.
	@param e Apontador para o estado do jogo.
*/
void inicializar_obstaculo(ESTADO *e) {
	int x, y;
	do {
		x = random() % 5;
		y = random() % 18;
	} while(!posicao_valida(x, y) || posicao_ocupada(e, x, y));

	e->obstaculo[(int)e->num_obstaculos].pos.x = x;
	e->obstaculo[(int)e->num_obstaculos].pos.y = y;
	e->obstaculo[(int)e->num_obstaculos].hp    = 2;
	e->obstaculo[(int)e->num_obstaculos].dmg   = 0;
	e->obstaculo[(int)e->num_obstaculos].exp   = 0;
	e->obstaculo[(int)e->num_obstaculos].prevpos = e->obstaculo[(int)e->num_obstaculos].pos;
	e->obstaculo[(int)e->num_obstaculos].exp   = 'm';
	(e->num_obstaculos)++;

}

/**
	\brief Gera obstáculos no mapa do jogo.
	@param e Apontador para o estado do jogo.
	@param num número de obstáculos a gerar
*/
void inicializar_obstaculos(ESTADO *e, int num) {
	int i;
	e->num_obstaculos = 0;

	for(i = 0; i < num; i++)
		inicializar_obstaculo(e);
}


/**
	\brief Gera inforação semi-aleatoria sobre o jogador no início do jogo.
	@param e Apontador para o estado do jogo.
*/
void inicializar_jogador(ESTADO *e) {
	int x, y;
	do {
		x = rand() % 3;
		y = 18 + rand() % 3;
	} while (!posicao_valida(x,y));
	e->jog.pos.x = x;
	e->jog.pos.y = y;
	e->jog.hp    = 3;
	e->jog.jump  = 3;
	e->jog.flames  = 1;
	e->jog.exp   = 0;
	e->jog.mode  = 'n';
	e->jog.last  = 'm';
	e->jog.prevpos = e->jog.pos;
}


/**
	\brief Esta função retorna uma estrutura de estado do jogo preenchida totalmente
		com zeros.

	@returns Estado preenchido com 0's.
*/
ESTADO estadozero() {
	ESTADO e = {0};
	return e;
}



/**
	\brief  Função que, no início do jogo, preenche semi-aleatoriamente o estado do
		jogo com a informação dos inimigos, obstáculos, jogador e trapdoor.
		O campo "screen" é preenchido com o caracter 'g' a fim de o programa
		imprimir o ecrã de jogo e não o "homescreen".
	@param e Apontador para o estado do jogo.

*/
void inicializar(ESTADO *e) {
	*e = estadozero();

	e->screen = 'g';
	e->lvl = 1;
	e->bot = '0';
	inicializar_jogador(e);
	inicializar_inimigos(e);
	inicializar_obstaculos(e, MAX_OBSTACULOS);
	inicializar_trapdoor(e);
}



/**
	\brief 	Gera informação sobre o jogador, incluindo posição aleatória (condicionada),
		quando começa um novo nível.
	@param e Apontador para o estado do jogo.

*/
void reinicializar_jogador(ESTADO *e) {
	int x, y;
	do {
		x = rand() % 3;
		y = 18 +rand() % 3;
	} while (!posicao_valida(x,y));
	e->jog.pos.x = x;
	e->jog.pos.y = y;
	e->jog.prevpos = e->jog.pos;
	e->jog.mode = 'n';
	e->jog.last = 'm';
	e->jog.jump = 3;
	e->jog.flames  = e->lvl / 5 + 1;
	if (e->lvl % 4 == 0)
		e->jog.hp++;
}




/**
	\brief Incrementa o nível e volta a gerar aleatoriamente um nível.
	@param e Apontador para o estado do jogo.
*/
void reinicializar(ESTADO * e) {
	e->lvl++;
	reinicializar_jogador(e);
	inicializar_inimigos(e);
	inicializar_obstaculos(e, MAX_OBSTACULOS);
	inicializar_trapdoor(e);
}










/*++++++++++++++++++++++++++++++++GAME FLOW+++++++++++++++++++++++++++++++++++++*/

/*
	Nesta seccção estão implementados os diversos "ecrãs" do jogo. i.e.
	home, game over, jogo, highscores...
*/



/**
	\brief  Coloca a estrutura do estado a zero.
	@param e Apontador para o estado do jogo.

*/
void homescreen(ESTADO *e) {
	*e = estadozero();
	e->screen = 's';
}




/**
	\brief  Imprime o ecrã de início de jogo.

*/
void printhomescreen() {
	ESTADO e;
	char link[MAX_BUFFER];
	inicializar(&e);

	sprintf(link, "http://localhost/cgi-bin/jogo?g");

	IMAGEM_2(0, 0, 670, 900, "firstscreen.png");
	ABRIR_LINK(link, "single");
	IMAGEM_2(200, 400, 400, 150, "start_button.png");
	FECHAR_LINK;


	sprintf(link, "http://localhost/cgi-bin/jogo?h");
	ABRIR_LINK(link, "double");
	IMAGEM_2(200, 600, 400, 150, "hscores.png");
	FECHAR_LINK;

}


/**
	\brief  Processa o fim de jogo, quando o hp do jogador é menor que 0.
	@param e Apontador para o estado do jogo.

*/
void gameover(ESTADO *e) {
	e->screen = 'o';

	int i, j;
	HSCORES hs;
	FILE* file = fopen("hscores", "rb");

	if(fread(&hs, sizeof(HSCORES), 1, file) != 1)
		perror("não consegui ler os hscores ao processar o gameover");

	for (i = 0; i < 5; i++)
		if (hs.score[i].num < e->jog.exp) {
			for (j = 4; j > i; j--)
				hs.score[j] = hs.score[j-1];
			hs.score[i].num = e->jog.exp;
			hs.score[i].bot = e->bot;
			break;
		}
	fclose(file);

	file = fopen("hscores", "wb");
	fwrite(&hs, sizeof(HSCORES), 1, file);

	fclose(file);

	ABRIR_LINK("http://localhost/cgi-bin/jogo?", "single");
	IMAGEM_2(0, 0, 670, 900, "gameover.png");
	FECHAR_LINK;
}




/**
	\brief  Função que controla, em função de certos campos na estrutura do
		estado, o ecrã a representar. Faz ligação com o módulo print.c .
	@param e Apontador para o estado do jogo.

*/
void control_estado(ESTADO *e) {
	if (e->jog.hp < 0)
		gameover(e);

	else if (e->screen == 's')
		printhomescreen();

	else if (e->screen == 'g')
		imprime_estado(e);

	else if (e->screen == 'h')
		print_hscores();

}





/**
	\brief  Efetua uma jogada na casa especificada pelas coordenadas dos
		parâmetros. Caso haja um inimigo, ataca, caso contrário, mover-se
		para a casa.
	@param e Apontador para o estado do jogo.
	@param x primeira coordenada
	@param y segunda coordenada

*/
void jogada(ESTADO *e, int x, int y) {
	if (posicao_ocupada(e, x, y)) {
		attack(e, x, y);
		e->jog.prevpos.x = x;
		e->jog.prevpos.y = y;
	}

	else  {
		if (!short_range(e->jog.pos.x, e->jog.pos.y, x, y))
			e->jog.jump--;

		e->jog.prevpos = e->jog.pos;
		e->jog.pos.x = x;
		e->jog.pos.y = y;
		e->jog.last = 'm';
	}

	react(e);

}


/**
	\brief Gera m ataque às casas contíguas à do jogador.
	@param e Apontador para o estado do jogo.

*/
void aoe_skill(ESTADO* e) {
	e->jog.prevpos = e->jog.pos;
	e->jog.last = 'b';

	int x = e->jog.pos.x;
	int y = e->jog.pos.y;
	int i, j;

	for(i = -2; i <= 2; i++)
		for(j = -2; j <=2; j++)
			if (posicao_valida(x + i, y + j) && short_range(x + i, y + j, x, y))
				attack(e, x + i, y + j);


	e->jog.flames--;

	react(e);
}



/**
	\brief  Altera o estado do jogo para o jogador poder mover-se 2 casas num
		salto.
	@param e Apontador para o estado do jogo.

*/
void estado_doublejump(ESTADO * e) {
	int i;

	read_estado(e);

	if(e->jog.mode != 'd')
		e->jog.mode = 'd';
	else
		e->jog.mode = 'n';

	for(i = 0; i < e->num_inimigos; i++)
		e->inimigo[i].last = 'm';


	e->jog.prevpos = e->jog.pos;


	for(i = 0; i < e->num_inimigos; i++)
		e->inimigo[i].prevpos = e->inimigo[i].pos;
}


/**
	\brief  Gere a opção de mostrar as casas que podem ser atacadas por inimigos.
	@param e Apontador para o estado do jogo.

*/
void estado_enemyattackinfo( ESTADO * e) {
	read_estado(e);

	if(e->jog.mode != 'i')
		e->jog.mode = 'i';
	else
		e->jog.mode = 'n';

	int i;

	for(i = 0; i < e->num_inimigos; i++)
		e->inimigo[i].last = 'm';

	e->jog.prevpos = e->jog.pos;

	for(i = 0; i < e->num_inimigos; i++)
		e->inimigo[i].prevpos = e->inimigo[i].pos;

}



/**
	\brief  Altera o estado do jogo para o modo de jogo automático (bot).
	@param e Apontador para o estado do jogo.

*/
void estado_bot(ESTADO * e) {
	read_estado(e);

	if (e->bot == '1')
		e->bot = '0';
	else
		e->bot = '1';

	int i;

	for(i = 0; i < e->num_inimigos; i++) {
		e->inimigo[i].last = 'm';
		e->inimigo[i].prevpos = e->inimigo[i].pos;
	}


	e->jog.prevpos = e->jog.pos;
}




/**
	\brief  Gere qual a jogada "estática", ou seja, que servem como meio para
		outras jogadas, está a ser executada. É chamada quando há apenas
		1 char depois do '?' na barra de endereços.
	@param e Apontador para o estado do jogo.
	@param args Parte do endereço que varia com o Apontador para o estado do jogo.

*/
void estado_staticmove(ESTADO * e, char * args) {

	if(strcmp(args, "d") == 0)
		estado_doublejump(e);

	else if (strcmp(args, "i") == 0)
		estado_enemyattackinfo(e);

	else if (strcmp(args, "b") == 0) { /*ataque com área de efeito*/

		read_estado(e);
		aoe_skill(e);
	}

	else if (strcmp(args, "h") == 0) /*highscores*/
		e->screen = 'h';

	else if (strcmp(args, "r") == 0) /* ativar o bot */
		estado_bot(e);

	else
		inicializar(e);
}


/**
	\brief  Aplica ao estado registado no ficheiro a jogada estpulada na barra
		de endereços.
	@param e Apontador para o estado do jogo.
	@param args Parte do endereço que varia com o Apontador para o estado do jogo.

*/
void merge_estadoargs(ESTADO * e, char* args) {
	int length = strlen(args);

	if (length > 2) { /*quando se dá uma jogada normal*/
		read_estado(e);

		int x, y;
		sscanf(args, "g,%d,%d", &x, &y);

		jogada(e, x, y);

	}

	else if (length == 2) { /*quando se entra num novo nível*/
		read_estado(e);
		reinicializar(e);
	}

	else if (length == 1)
		estado_staticmove(e, args);
}






/**
	\brief  Verifica o endereço da página averiguando se imprime o menu principal
		ou outro ecrã.
	@param e Apontador para o estado do jogo.
	@param args Parte do endereço que varia com o Apontador para o estado do jogo.

*/
void construir_estado(ESTADO *e, char* args) {
	if(strlen(args) == 0)
		homescreen(e);
	else {
		merge_estadoargs(e, args);
	}


}









/**
	\brief  A função main do programa.

	De uma forma geral, a forma de funcionamento do programa é a seguinte:\n
	-O o estado é construido a partir da informação na barra de endereços e do ficheiro local.
	-O estado reage à jogada que acabou de ser "retirada" da barra de endereços.
	-O estado é imprimido e correm o(s) script(s) necessários.

*/
int main() {
	srandom(time(NULL));
	ESTADO e;
	construir_estado(&e, getenv("QUERY_STRING"));

	COMECAR_HTML;
	ABRIR_SVG(1300, 900);

	control_estado(&e);

	FECHAR_SVG;

	if(e.jog.mode == 'n')
	keys_b();
	else
	keys_bs();
	armazena_estado(&e);

	return 0;
}
