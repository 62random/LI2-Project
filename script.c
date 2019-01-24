#include "header.h"

/**
	@file script.c Este ficheiro contém funções que imprimem para o stdin
		no nosso caso, graças ao cgi-bin, na página html, scripts em
		javascript, para tratar de aspetos que requerem a lteração de
		elementos da página que não possam ser geridos em puro html
		(i.e. tags <animate>)
*/


/**
	\brief Esta função imprime um script que testa se a tecla premida
		(evento gerido recorrendo à livraria jQuery) é uma tecla
		entre as que queremos utilizar, e, mediante o código da
		tecla, efetua uma ação.
*/
void keys_b() {
	printf("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js\"></script>\n \
	<script>\n\t \
	$(document).keydown(function(e){\n\t\t \
		if(e.keyCode == 87) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('0').href.animVal;\n\t\t \
		}\n\t \
 \
		if(e.keyCode == 81) {\n\t\t \
						e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('1').href.animVal;\n\t\t \
		}\n\t \
 \
		if(e.keyCode == 69) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('2').href.animVal;\n\t\t \
		}\n\t \
 \
		if(e.keyCode == 90) {\n\t\t  \
			e.preventDefault();\n\t\t\t \
			window.location.href = window.location.href;\n\t\t \
		}\n\t \
 \
		if(e.keyCode == 65) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('4').href.animVal;\n\t\t \
		}\n\t \
 \
		if(e.keyCode == 68) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('5').href.animVal;\n\t\t \
		}\n\t \
 \
		if(e.keyCode == 83) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('6').href.animVal;\n\t\t \
		}\n\t \
 \
		if(e.keyCode == 13) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('single').href.animVal;\n\t\t \
		}\n\t \
 \
		if(e.keyCode == 8) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('double').href.animVal;\n\t\t \
		}\n\t \
\
		if(e.keyCode == 32) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('bot').href.animVal;\n\t\t \
		}\n\t \
\
		if(e.keyCode == 73) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('help').href.animVal;\n\t\t \
		}\n\t \
	});\n \
\
</script>\n \
	");
}



/**
	\brief Esta função imprime um script que testa se a tecla premida
		(evento gerido recorrendo à livraria jQuery) é uma tecla
		entre as que queremos utilizar, e, mediante o código da
		tecla, efetua uma ação.
		Esta função é semelhante à void keys_bs(); no entanto, lida
		com as situações em que o jogador pode saltar duas casas de uma
		vez e, portanto, há um set de jogadas diferentes a codificar.
*/
void keys_bs() {
	printf("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js\"></script>\n \
	<script>\n\t \
	$(document).keydown(function(e){\n\t\t \
		if(e.keyCode == 87) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('0').href.animVal;\n\t\t \
		}\n\t \
 \
		if(e.keyCode == 81) {\n\t\t \
						e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('3').href.animVal;\n\t\t \
		}\n\t \
 \
		if(e.keyCode == 69) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('4').href.animVal;\n\t\t \
		}\n\t \
 \
		if(e.keyCode == 90) {\n\t\t  \
			e.preventDefault();\n\t\t\t \
			window.location.href = window.location.href;\n\t\t \
		}\n\t \
 \
		if(e.keyCode == 65) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('8').href.animVal;\n\t\t \
		}\n\t \
 \
		if(e.keyCode == 68) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('9').href.animVal;\n\t\t \
		}\n\t \
 \
		if(e.keyCode == 83) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('12').href.animVal;\n\t\t \
		}\n\t \
 \
		 if(e.keyCode == 97) {\n\t\t \
			 e.preventDefault();\n\t\t\t \
			 window.location.href = document.getElementById('10').href.animVal;\n\t\t \
		 }\n\t \
\
		if(e.keyCode == 99) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('11').href.animVal;\n\t\t \
		}\n\t \
\
		if(e.keyCode == 100) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('5').href.animVal;\n\t\t \
		}\n\t \
\
		if(e.keyCode == 102) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('7').href.animVal;\n\t\t \
		}\n\t \
\
		if(e.keyCode == 103) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('1').href.animVal;\n\t\t \
		}\n\t \
\
		if(e.keyCode == 105) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('2').href.animVal;\n\t\t \
		}\n\t \
\
		if(e.keyCode == 13) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('single').href.animVal;\n\t\t \
		}\n\t \
\
		if(e.keyCode == 8) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('double').href.animVal;\n\t\t \
		}\n\t \
\
		if(e.keyCode == 32) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('bot').href.animVal;\n\t\t \
		}\n\t \
\
		if(e.keyCode == 73) {\n\t\t \
			e.preventDefault();\n\t\t\t \
			window.location.href = document.getElementById('help').href.animVal;\n\t\t \
		}\n\t \
	});\n \
\
</script>\n \
	");
}



/**
	\brief Esta função gera um script que faz o jogador mover-se automaticamente
		em direção à saída, quando não há inimigos vivos.
	@param e Apontador para o estado do jogo.
*/
void auto_walk(ESTADO * e) {
	int x = e->jog.pos.x;
	int y = e->jog.pos.y;
	int a = e->trapdoor.x;
	int b = e->trapdoor.y;


	if(short_range(x, y, a, b)) {
		printf("<script>\n\t \
				setTimeout(function(){window.location.href = \"http://localhost/cgi-bin/jogo?tr\";},600)\n \
			</script>");
		return;
	}

	POSICAO proxima_posicao;

	proxima_posicao = step(e, x, y, a, b);

	printf("<script>\n\t \
			setTimeout(function(){window.location.href = \"http://localhost/cgi-bin/jogo?g,%d,%d\";},300)\n \
		</script>\n", proxima_posicao.x, proxima_posicao.y);
}


/**
	\brief Script que invoca a utilização do bot para jogar automaticamente.
	@param e Apontador para o estado do jogo.
*/
void use_bot(ESTADO * e) {

	if(e->num_inimigos < 1) {
		auto_walk(e);
		return;
	}

	char returned[10];
	auto_move(e, returned);
	printf("<script>\n\t \
			setTimeout(function(){window.location.href = \"http://localhost/cgi-bin/jogo?%s\";},600)\n \
		</script>\n", returned);
}
