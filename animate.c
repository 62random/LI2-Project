#include "header.h"


/**
	@file animate.c Este ficheiro contém as funções que geram tags html que
		em que são implementadas animações.
*/


/**
	\brief Função que efetua a translação de um jogador dede a sua posição prévia
		para a sua posição atual, ou dos efeitos animados gerados pela sua jogada.
	@param e Apontador para o estado do jogo.
*/
void translateplayer(ESTADO *e) {
	int a, b, x, y;
	x = e->jog.prevpos.x;
	y = e->jog.prevpos.y;
	a = get_posx(e->jog.pos.x, e->jog.pos.y) + DEVX;
	b = get_posy(e->jog.pos.y) + DEVY;
	x = get_posx(e->jog.prevpos.x, e->jog.prevpos.y) + DEVX;
	y = get_posy(e->jog.prevpos.y) + DEVY;

	if (e->jog.last != 'a' && e->jog.last != 'b')
		printf("<image id=%s x=%d y=%d height=%d width=%d  xlink:href=http://localhost/images/player.png />\n\
		<animate\n\txlink:href=#%s\n\tattributeName=x\n\tfrom=%d\n\tto=%d\n\tdur=0.2s\n\tfill=freeze />\n\
		<animate\n\txlink:href=#%s\n\tattributeName=y\n\tfrom=%d\n\tto=%d\n\tdur=0.2s\n\tfill=freeze />", "player", x, y, ESCALAIMG, ESCALAIMG, "player", x, a, "player", y, b);

	else if (e->jog.last == 'b') {
		int i, j, counter = 0;

		float flt_escala = ESCALA/100.00;
		int horiz_dev1 = flt_escala*25;
		int horiz_dev2 = flt_escala*50;
		int vertical_dev = flt_escala*43;

		IMAGEM_2(a, b, ESCALAIMG, ESCALAIMG, "player.png");

		x = e->jog.pos.x;
		y = e->jog.pos.y;
		char link[50];
		char num[2];

		for(i = -2; i <= 2; i++)
			for(j = -2; j <= 2; j++)
				if (posicao_valida(x + i, y + j) && short_range(x + i, y + j, x, y) && (i != 0 || j != 0)) {

					int x1 = get_posx(x + i, y + j);
					int y1 = get_posy( y + j);

					printf("<polygon id=bmb%d%d points=\"%d,%d %d,%d %d,%d %d,%d %d,%d %d,%d\" style=\"fill:#900000;stroke:black;stroke-width:3\" />\n \
					<animate\n\txlink:href=#bmb%d%d\n\tattributeName=fill-opacity\n\tfrom=0\n\tto=1\n\tdur=0.3s />\n\
					<animate\n\txlink:href=#bmb%d%d\n\tattributeName=fill-opacity\n\tfrom=1\n\tto=0\n\tdur=0.3s\n\tbegin=0.3s\n\tfill=freeze />\n",
						 i, j, x1, y1, x1 + horiz_dev1, y1 + vertical_dev, x1 + horiz_dev1 + horiz_dev2, y1 + vertical_dev, x1 + ESCALA, y1,
						 x1 + horiz_dev1 + horiz_dev2, y1 - vertical_dev, x1 + horiz_dev1, y1 - vertical_dev, i, j, i, j);

					sprintf(link, "http://localhost/cgi-bin/jogo?g,%d,%d", x + i, y + j);
					sprintf(num, "%d", counter);
					ABRIR_LINK(link, num);
					print_hexpos_trans(x + i, y + j);
					FECHAR_LINK;

					counter++;
				}

		e->jog.last = 'm';
	}

	else if (e->jog.last == 'a'){
		printf("<image id=%s x=%d y=%d height=%d width=%d  xlink:href=http://localhost/images/player.png />\n\
		<animate\n\txlink:href=#%s\n\tattributeName=x\n\tfrom=%d\n\tto=%d\n\tdur=0.1s />\n\
		<animate\n\txlink:href=#%s\n\tattributeName=y\n\tfrom=%d\n\tto=%d\n\tdur=0.1s />\n\
		<animate\n\txlink:href=#%s\n\tattributeName=x\n\tfrom=%d\n\tto=%d\n\tdur=0.1s\n\tbegin=0.1s\n\tfill=freeze />\n\
		<animate\n\txlink:href=#%s\n\tattributeName=y\n\tfrom=%d\n\tto=%d\n\tdur=0.1s\n\tbegin=0.1s\n\tfill=freeze />\n",\
		 "player", x, y, ESCALAIMG, ESCALAIMG, "player", a, x, "player", b, y, "player", x, a, "player", y, b);


	}


}


/**
	\brief Função que imprime as tags correspondentes à animação do movimento
		dos inimigos.
	@param e Apontador para o estado do jogo.
	@param id número identificador do inimigo na estrutura do jogo
*/
void translateenemy(ESTADO *e, int id) {
	int x, y, a, b, i;
	x = get_posx(e->inimigo[id].prevpos.x, e->inimigo[id].prevpos.y) + DEVX;
	y = get_posy(e->inimigo[id].prevpos.y) + DEVY;
	a = get_posx(e->inimigo[id].pos.x, e->inimigo[id].pos.y) + DEVX;
	b = get_posy(e->inimigo[id].pos.y) + DEVY;
	char type = e->inimigo[id].type;
	char str1[20], str2[20];
	sprintf(str1, "enemy%d", id);

	printf("<image id=%s x=%d y=%d height=%d width=%d  xlink:href=http://localhost/images/enemy_%c.png />\n\
	<animate\n\txlink:href=#%s\n\tattributeName=x\n\tfrom=%d\n\tto=%d\n\tdur=0.2s\n\tbegin=0.2s\n\tfill=freeze />\n\
	<animate\n\txlink:href=#%s\n\tattributeName=y\n\tfrom=%d\n\tto=%d\n\tdur=0.2s\n\tbegin=0.2s\n\tfill=freeze />\n\n", str1, x, y, ESCALAIMG, ESCALAIMG, type, str1, x, a, str1, y, b);

	for(i = 0; i < e->inimigo[id].hp; i++) {
		sprintf(str2, "enemy%dhp%d", id, i);
		printf("<image id=%s x=%d y=%d height=%d width=%d  xlink:href=http://localhost/images/heart.png />\n\
		<animate\n\txlink:href=#%s\n\tattributeName=x\n\tfrom=%d\n\tto=%d\n\tdur=0.2s\n\tbegin=0.2s\n\tfill=freeze />\n\
		<animate\n\txlink:href=#%s\n\tattributeName=y\n\tfrom=%d\n\tto=%d\n\tdur=0.2s\n\tbegin=0.2s\n\tfill=freeze />\n\n",\
		str2, x + ESCALAIMG/2 + i*ESCALAIMG/8, y + ESCALAIMG/10, ESCALAIMG/10, ESCALAIMG/10, str2,
		x + ESCALAIMG/2 + i*ESCALAIMG/8, a+ ESCALAIMG/2 + i*ESCALAIMG/8, str2, y + ESCALAIMG/10,  b + ESCALAIMG/10);
	}
}


/**
	\brief Função que imprime as tags correspondentes à animação que representam
		o ataque dos inimigos que atacam à distância
	@param e Apontador para o estado do jogo.
	@param id número identificador do inimigo na estrutura do jogo
*/
void fireball(ESTADO *e, int id) {
	int x, y, a, b;
	x = get_posx(e->inimigo[id].pos.x, e->inimigo[id].pos.y) + DEVX;
	y = get_posy(e->inimigo[id].pos.y) + DEVY;
	a = get_posx(e->jog.pos.x, e->jog.pos.y) + DEVX + 10;
	b = get_posy(e->jog.pos.y) + DEVY - 10;
	char str1[10];
	sprintf(str1, "fire%d", id);

	printf("<image id=%s x=%d y=%d height=%d width=%d fill-opacity=0 xlink:href=http://localhost/images/fire.png />\n\
	<animate\n\txlink:href=#%s\n\tattributeName=x\n\tfrom=%d\n\tto=%d\n\tdur=0.3s\n\tbegin=0.2s\n\tfill=freeze />\n\
	<animate\n\txlink:href=#%s\n\tattributeName=y\n\tfrom=%d\n\tto=%d\n\tdur=0.3s\n\tbegin=0.2s\n\tfill=freeze />\n\n",\
	 str1, x, y, ESCALAIMG, ESCALAIMG, str1, x, a, str1, y, b);
}
