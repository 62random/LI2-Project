#include "header.h"

/**
	@file print.c Este ficheiro contém as funções que gerem a (esmagadora)
		maioria das funções que imprimem conteúdo para o stdin, ou por
		outras palavras, imprimem conteúdo an página.
*/


/**
	\brief Esta função imprime um inimigo, dado o estado e as coordenadas.
	@param e Apontador para o estado do jogo.
	@param x 1ª coordenada do inimigo
	@param y 2ª coordenada do inimigo
*/
void imprime_inimigo(ESTADO *e, int x, int y) {
	int i = inimigo_cord(e, x, y);
	translateenemy(e, i);
	if (e->inimigo[i].last == 'a' && e->inimigo[i].type == 'a')
		fireball(e, i);

}

/**
	\brief Esta função imprime um obstáculo, dadas as suas coordenadas. Não é
		necessário fornecer informação sobre o estado do jogo porque os
		obstáculos são inanimados.
	@param x 1ª coordenada do obstáculo
	@param y 2ª coordenada do obstáculo
*/
void imprime_obstaculo(int x, int y) {
	int a, b;
	a = get_posx(x, y) + DEVX;
	b = get_posy( y) + DEVY;
	IMAGEM_1(a, b, ESCALAIMG, "obstacle.png");
}



/**
	\brief Esta função imprime uma casa do mapa, o que que quer que esteja
		lá dentro, entre um inimigo, obstáculo, ou nada. (jogador e trapdoor
		geridos por outras funções)
	@param e Apontador para o estado do jogo.
	@param x 1ª coordenada da casa
	@param y 2ª coordenada da casa
*/
void imprime_casa(ESTADO *e, int x, int y) {

	if (tem_inimigo(e, x, y)) {
		print_hexpos_trans(x, y);
		imprime_inimigo(e, x, y);
		return;
	}

	if (tem_obstaculo(e, x, y)) {
		print_hexpos_trans(x, y);
		imprime_obstaculo(x, y);
		return;
	}


	print_hexpos_trans(x, y);
}


/**
	\brief Esta função é semelhante à imprime_casa, no entanto aplica à casa
		uma cor diferente da do resto do mapa. (Não passámos a cor como
		argumento de uma só função porque, na verdade, o tabuleiro é
		imprimido apenas uma vez e apenas utilizamos hexágonos novamente
		para introduzir links nas casas)
	@param e Apontador para o estado do jogo.
	@param x 1ª coordenada da casa
	@param y 2ª coordenada da casa
*/
void imprime_casa_hl(ESTADO *e, int x, int y) {

	if (tem_inimigo(e, x, y)) {
		print_hexpos(x, y, "#404040");
		imprime_inimigo(e, x, y);
		return;
	}

	if (tem_obstaculo(e, x, y)) {
		print_hexpos(x, y, "#404040");
		imprime_obstaculo(x, y);
		return;
	}

	print_hexpos(x, y, "#404040");
}



/**
	\brief Esta função imprime a trapdoorpara o próximo nível.
	@param e Apontador para o estado do jogo.
*/
void imprime_trapdoor(ESTADO *e) {
	int a, b;
	a = get_posx(e->trapdoor.x, e->trapdoor.y) + 10;
	b = get_posy( e->trapdoor.y) - 25;

	if (short_range(e->trapdoor.x, e->trapdoor.y, e->jog.pos.x, e->jog.pos.y)) {
		printf("<a xlink:href=http://localhost/cgi-bin/jogo?tr>\n");

		print_hexpos(e->trapdoor.x, e->trapdoor.y, COR);
		IMAGEM_1(a, b, 5*ESCALA/7, "trapdoor.png");
		FECHAR_LINK;
	}
	else {
		print_hexpos(e->trapdoor.x, e->trapdoor.y, COR);
		IMAGEM_1(a, b, 5*ESCALA/7, "trapdoor.png");
	}
}



/**
	\brief Esta função imprime uma jogada, ou seja, um link que, ao sr clicado
		redirecionará o browser para uma nova página em que o jogo evoluirá
		no sentido desejado. (i.e. imprime o link na casa XY, que, ao ser
		clicado, levará o jogador para a casa XY)
	@param e Apontador para o estado do jogo.
	@param dx variação da 1ª coordenada do jogador
	@param dy variação da 2ª coordenada do jogador
	@param mode modo de movimento do jogador (i.e. salto duplo, normal)
	@param id id da tag svg do link criado, a fim de implementar o funcionamento
		de teclas
*/
void imprime_movimento(ESTADO *e, int dx, int dy, char mode, char* id) {

	int x = e->jog.pos.x + dx;
	int y = e->jog.pos.y + dy;
	char link[MAX_BUFFER];

	if(!posicao_valida(x, y))
		return;

	else if(tem_jogador(e, x, y))
		return;

	if (!tem_trapdoor(e, x, y))
		sprintf(link, "http://localhost/cgi-bin/jogo?g,%d,%d", x, y);
	else
		sprintf(link, "http://localhost/cgi-bin/jogo?tr");

	ABRIR_LINK(link, id);
	if(mode == 'd')
		imprime_casa_hl(e, x, y);
	else
		imprime_casa(e, x, y);
	FECHAR_LINK;
}




/**
	\brief Esta função imprime um botão para ativar o salto duplo.
	@param e Apontador para o estado do jogo.
*/
void imprime_power_salto(ESTADO *e) {


	char link[MAX_BUFFER];
	sprintf(link, "http://localhost/cgi-bin/jogo?d");

	if (e->jog.jump > 0) {
		ABRIR_LINK(link, "double");
		IMAGEM_2(14,807,340,85,"jump.png");
		FECHAR_LINK;
	}
	else
		IMAGEM_2(14,807,340,85,"jump.png");

	imprime_int(e->jog.jump, 300, 840, 30);
}



/**
	\brief Esta função imprime um botão para ativar o ataque especial.
	@param e Apontador para o estado do jogo.
*/
void imprime_power_flames(ESTADO* e) {
	char link[MAX_BUFFER];
	sprintf(link, "http://localhost/cgi-bin/jogo?b");

	if (e->jog.flames > 0) {
		ABRIR_LINK(link, "single");
		IMAGEM_2(354,807,300,85,"flames.png");
		FECHAR_LINK;
	}
	else
		IMAGEM_2(354,807,300,85,"flames.png");

	imprime_int(e->jog.flames, 580, 840, 30);
}

/**
	\brief Esta função imprime um "highlight" nas casas que um dado inimigo pode atacar.
	@param e Apontador para o estado do jogo.
	@param x número identificador de um inimigo na estrutura do estado
*/
void help_enemy(ESTADO* e, int n) {
	int i, j;
	int x = e->inimigo[n].pos.x;
	int y = e->inimigo[n].pos.y;

	if (e->inimigo[n].type == 'm') {
		for (i = -2; i <= 2; i++)
			for (j = -2; j <= 2; j++)
				if( posicao_valida(x+i, y+ j) && short_range(x, y, x + i, y + j) && ( i!= 0 || j != 0))
					imprime_casa_hl(e, x + i, y + j);
	}
	else
		for (i = -10; i<=10; i++)
			for(j = -10; j <= 10; j++)
				if(posicao_valida(x+i, y+ j) && ( i!= 0 || j != 0)
				&& dist_casas(x, y, x + i, y + j) < 6 && cords_line(x, y, x + i, y + j))
					imprime_casa_hl(e, x + i, y + j);


}



/**
	\brief Esta função imprime um "highlight" em todas as casas que podem ser
		atacadas por inimigos.
*/
void imprime_help() {
	char link[50];
	sprintf(link, "http://localhost/cgi-bin/jogo?i");


	ABRIR_LINK(link, "help");
	IMAGEM_2(619, 20, 34, 34, "help.png");
	FECHAR_LINK;

}




void imprime_bot() {
	char link[50];
	sprintf(link, "http://localhost/cgi-bin/jogo?r");


	ABRIR_LINK(link, "bot");
	IMAGEM_2(530, 20, 72, 34, "bot.png");
	FECHAR_LINK;
}





/**
	\brief Esta função chama as funções que imprimem jogadas especiais
		(i.e. salto duplo, flames, help)
	@param e Apontador para o estado do jogo.
*/
void imprime_powers(ESTADO *e) {
	imprime_power_salto(e);
	imprime_power_flames(e);
	imprime_help();
	imprime_bot();
}



/**
	\brief Esta função imprime os movimentos que o jogador pode efetuar.
	@param e Apontador para o estado do jogo.
*/
void imprime_movimentos(ESTADO *e) {
	char id1[20];
	int i, j, id = 0;
	for(j = -2; j<=2; j++)
		for(i = -1; i<=1; i++)
			if (short_range(e->jog.pos.x, e->jog.pos.y, e->jog.pos.x + i, e->jog.pos.y + j)) {
				sprintf(id1, "%d", id);
				imprime_movimento(e, i, j, e->jog.mode, id1);
				id++;
			}
}




/**
	\brief Esta função imprime os movimentos que o jogador pode efetuar, quando
		está em modo de salto duplo.
	@param e Apontador para o estado do jogo.
*/
void imprime_movimentos_d(ESTADO *e) {
	char id1[20];
	int i, j, id = 0;


	for(j = -4; j<=4; j++)
		for(i = -3; i<=3; i++)
			if (double_range(e->jog.pos.x, e->jog.pos.y, e->jog.pos.x + i, e->jog.pos.y + j)
			&& (!short_range(e->jog.pos.x, e->jog.pos.y, e->jog.pos.x + i, e->jog.pos.y + j)
			|| (i == 0 && j == 0))) {
				sprintf(id1, "%d", id);
				if(!posicao_ocupada(e, e->jog.pos.x +i, e->jog.pos.y + j))
					imprime_movimento(e, i, j, e->jog.mode, id1);
				id++;
			}
}





/**
	\brief Esta função imprime todos os aspetos do jogo que se prendem com o jogador.
		A sua vida, experiência (ou pontuação), e movimentos.
	@param e Apontador para o estado do jogo.
*/
void imprime_jogador(ESTADO *e) {
	int i;
	if(e->jog.jump <= 0)
		e->jog.mode = 'n';

	if (e->jog.mode == 'd')
		imprime_movimentos_d(e);

	else if (e->jog.mode == 'i')
		for (i = 0; i < e->num_inimigos; i++)
			help_enemy(e, i);
	else
		imprime_movimentos(e);

	imprime_powers(e);

	translateplayer(e);

	for(i = 0; i < e->jog.hp; i++)
		IMAGEM_1(36 + 28*i, 764, 27 , "heart.png");

	IMAGEM_2(170, 15, 100, 50, "exp.png");
	imprime_int(e->jog.exp, 228, 15, 45);

	if(e->bot == '1')
		use_bot(e);

	if(e->num_inimigos == 0)
		auto_walk(e);


}


/**
	\brief Esta função imprime todos os inimigos no jogo.
	@param e Apontador para o estado do jogo.
*/
void imprime_inimigos(ESTADO *e) {
	int i;
	for(i = 0; i < e->num_inimigos; i++)
		if (!short_range(e->inimigo[i].pos.x, e->inimigo[i].pos.y, e->jog.pos.x, e->jog.pos.y)
		|| (e->inimigo[i].prevpos.x == e->inimigo[i].pos.x && e->inimigo[i].prevpos.y == e->inimigo[i].pos.y))
			imprime_inimigo(e, e->inimigo[i].pos.x, e->inimigo[i].pos.y);
}


/**
	\brief Esta função imprime todos os obstáculos no mapa.
	@param e Apontador para o estado do jogo.
*/
void imprime_obstaculos(ESTADO *e) {
	int i;
	for(i = 0; i < e->num_obstaculos; i++)
		imprime_obstaculo(e->obstaculo[i].pos.x, e->obstaculo[i].pos.y);
}



/**
	\brief Esta função gera (quase) todo o output que corresponde à representação do
		jogo em html.
	@param e Apontador para o estado do jogo.
*/
void imprime_estado(ESTADO *e) {
	IMAGEM_2(0, 0, 670, 900, "backgame.png");
	imprime_int(e->lvl, 70, 18, 40);
	hex_grid();
	imprime_obstaculos(e);
	imprime_inimigos(e);
	imprime_jogador(e);
	fprintf(stderr, "print player\n");
	imprime_trapdoor(e);

}



/**
	\brief Esta função obtém a primeira coordenada (abcissa) absoluta de um
	 	ponto na página a partir das suas coordenadas no jogo.
	@param x 1ª coordenada
	@param y 2ª coordenada
*/
int get_posx(int x, int y) {
	float a = ESCALA/100.00;
	int h1 = a*25;
	int h2 = a*50;

	if (y <= TAM)
		return XSTART - (h1 + h2)*y + x*(ESCALA + h2);
	else if (y <= TAM*3 ) {
		if (y%2 == 0)
			return XSTART - (h1 + h2)*(TAM - 1) + x*(ESCALA + h2);
		else
			return XSTART - (h1 + h2)*TAM + x*(ESCALA + h2);
	}
	else
		return XSTART - (h1 + h2)*TAM +(h1+h2)*(y - TAM*3) + x*(ESCALA + h2);
}


/**
	\brief Esta função obtém a segunda coordenada (abcissa) absoluta de um
	 	ponto na página a partir das suas coordenadas no jogo.
	@param x 2ª coordenada
*/
int get_posy( int y) {
	float a = ESCALA/100.00;
	int v = a*43;

	if (y <= TAM)
		return YSTART + y*v;
	else if (y <= TAM*3 ) {
		if (y%2 == 0)
			return YSTART + y*v;
		else
			return YSTART + y*v;
	}
	else
		return YSTART + y*v;
}




/**
	\brief Esta função obtém imprime um hexágono na página, mediante as
		coordenadas e a cor.
	@param x 1ª coordenada
	@param y 2ª coordenada
	@param cor cor do hexágono
*/
void print_hex(int x, int y, char * cor) {
	float a = ESCALA/100.00;
	int h1 = a*25;
	int h2 = a*50;
	int v = a*43;

	printf("<polygon points=\"%d,%d %d,%d %d,%d %d,%d %d,%d %d,%d\" style=\"fill:%s;stroke:black;stroke-width:3\" />\n",
		 x, y, x+h1, y+v, x+h1+h2, y+v, x+ESCALA, y, x+h1+h2, y-v, x+h1, y-v, cor);
}


/**
	\brief Esta função obtém imprime um hexágono transparente na página, mediante
	as coordenadas.
	@param x 1ª coordenada
	@param y 2ª coordenada
*/
void print_hex_trans(int x, int y) {
	float a = ESCALA/100.00;
	int h1 = a*25;
	int h2 = a*50;
	int v = a*43;

	printf("<polygon points=\"%d,%d %d,%d %d,%d %d,%d %d,%d %d,%d\" style=\"fill:%s;stroke:black;stroke-width:3;fill-opacity:0\" />\n",
		 x, y, x+h1, y+v, x+h1+h2, y+v, x+ESCALA, y, x+h1+h2, y-v, x+h1, y-v, COR);
}



/**
	\brief Esta função obtém imprime um hexágono na página, mediante as
		coordenadas no jogo e a cor.
	@param x 1ª coordenada
	@param y 2ª coordenada
	@param cor cor do hexágono
*/
void print_hexpos(int x, int y, char* cor) {

	print_hex(get_posx(x,y), get_posy(y), cor);
}


/**
	\brief Esta função obtém imprime um hexágono transparente na página, mediante
		as coordenadas no jogo.
	@param x 1ª coordenada
	@param y 2ª coordenada
*/
void print_hexpos_trans(int x, int y) {

	print_hex_trans(get_posx(x,y), get_posy(y));
}


/**
	\brief Esta função obtém imprime um a grelha de haxágonos na página.
		O tamanho dos hexágonos, o número de hexágonos, e a posição da
		grelha estão em #defines.
*/
void hex_grid() {
	int i, j;
	for(i = 0; i <= TAM*4; i++) {
		if (i < TAM)
			for(j = 0; j <= i; j++)
				print_hexpos(j, i, COR);
		else if (i <= TAM * 3)
			for(j = 0; j <= TAM - (i+1)%2; j++)
				print_hexpos(j, i, COR);
		else
			for(j = 0; j <= TAM - (i - TAM*3); j++)
				print_hexpos(j, i, COR);
	}


}


/**
	\brief Esta função obtém imprime um algarismo na página.
	@param n algarismo a ser imprimido
	@param x 1ª coordenada
	@param y 2ª coordenada
	@param size tamanho do algarismo imrimido (altura  píxeis)
*/
void imprime_alg(int n, int x, int y, int size) {
	printf("<image x=%d y=%d width=%d height=%d xlink:href=http://localhost/images/%d.png />\n", \
								x, y, size, size, n);
}



/**
	\brief Esta função obtém imprime um número inteiro na página.
	@param n número a ser imprimido
	@param x 1ª coordenada
	@param y 2ª coordenada
	@param size tamanho do número imrimido (altura de cada algarismo em píxeis)
*/
void imprime_int(int n, int x, int y,int size) {
	int i, j;
	if (n == 0)
		imprime_alg(0, x + 5*size/8, y, size);
	for (i = n, j = 0; i > 0; i /=10, j++)
		;
	for (i = n; i > 0; i/= 10, j--)
		imprime_alg(i%10, x + 5*size*j/8, y, size);
}






/**
	\brief Esta função obtém imprime os highscores contidos num ficheiro.
*/
void print_hscores() {
	FILE* f = fopen("hscores", "rb");

	HSCORES hs;
	if (fread(&hs, sizeof(HSCORES), 1, f) != 1)
		perror("não consegui ler os hscores para imprimir o board");


	fclose(f);

	ABRIR_LINK("http://localhost/cgi-bin/jogo?", "single");
	IMAGEM_2(0, 0, 670, 900, "empty.png");
	FECHAR_LINK;

	IMAGEM_2(100, 100, 400, 150, "hscores.png");

	int i;

	for(i = 0; i < 5; i++) {
		imprime_int(i + 1, 130, 305 + 120*i, 30);
		imprime_int(hs.score[i].num, 200, 250 + 120*i, 100);
		if (hs.score[i].bot == '1')
			IMAGEM_2(500, 260 + 120*i, 100, 100, "fire.png");
	}


}
