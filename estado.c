#include "header.h"


/**
@file estado.c Este ficheiro contém as funções responsáveis pela leitura e escrita
 	do estado do jogo no ficheiro local que o armazena.
*/

/*--------------ARMAZENAR E LER ESTADO NUM FICHEIRO-----------------------------*/


/**
	\brief Esta função armazena o estado do jogo no ficheiro, escrevendo
		a estrutura integralmente (em binário) para o ficheiro.
	@param e Apontador para o estado do jogo.
*/
void armazena_estado(ESTADO *e) {
	FILE* file;
	if ((file = fopen("estado", "wb")) == NULL) {
		perror("não foi possível abrir o ficheiro");

		exit(1);
	}


	fwrite(e, sizeof(ESTADO), 1, file);


	fclose(file);

}






/*-----------------------LEITURA DE ESTADO--------------------------------------*/





/**
	\brief Esta função lê o estado do jogo no ficheiro, lendo
		a estrutura integralmente (em binário) do ficheiro.
	@param e Apontador para o estado do jogo.
*/
void read_estado(ESTADO* e) {
	FILE* file;

	if ((file = fopen("estado", "rb")) == NULL) {
		perror("não foi possível abrir o ficheiro");
		exit(1);
	}


	if (fread(e, sizeof(ESTADO), 1, file) != 0)
		perror("não consgui ler o estado 1");


	fclose(file);

}
