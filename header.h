#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "estado.h"
#include "cgi.h"

/**
	@file header.h Este ficheiro contém os protótipos de todas (quase todas) as funções
 	      envolvidas neste projeto. É feito o import de outros ficheiros com
	      conteúdo utilizado recorrentemente nos diversos módulos.
*/

/**
        \mainpage Notas gerais:\n\t
        \section vars Nomes de variáveis:
                -variáveis com as letras x e y em evidência (i.e x, y, x2, y2, x1...) referem-se SEMPRE a coordenadas de posições\n
                -variáveis semelhantes às referidas na linha anterior mas com as letras a,b ,c e d
                também se referem a posições, e são utilizadas sempre em simultâneo com as outras (para não haver repetições)\n
                -variáveis i e j são sempre variáveis de controlo de ciclos\n
*/








/*estado.c----------------------------------------------------------------------*/
/*
	Neste módulo, é feita a gestão e manipulação do estado de jogo como
	"pedaço" de informação, ou seja, a forma como armazenamos e convertemos
	a informação de modo a poder utilizá-la da maneira que nos convier.
*/

void armazena_jogador(ESTADO* e, FILE* f);
void armazena_inimigo(ESTADO* e, int n, FILE* f);
void armazena_obstaculo(ESTADO* e, int n, FILE* f);
void armazena_estado(ESTADO *e);
void read_obstaculo(ESTADO* e, int n, FILE* f);
void read_inimigo(ESTADO* e, int n, FILE* f);
void read_jogador(ESTADO* e, FILE* f);
void read_estado(ESTADO* e);


/** \brief O nº máximo de caracteres na query_string*/
#define MAX_BUFFER		10240


/*data.c------------------------------------------------------------------------*/
/*
	Este módulo contém funções que trabalham com informação muito genéreinica
	que é utilizada pela maioria dos módulos restantes devido ao quão elementar
	é a informação que as funções aqui definidas produzem.
*/

int posicao_valida(int x, int y);
int posicao_igual(POSICAO a, int x, int y);
int tem_jogador(ESTADO *e, int x, int y);
int tem_inimigo(ESTADO *e, int x, int y);
int tem_obstaculo(ESTADO *e, int x, int y);
int tem_trapdoor(ESTADO *e, int x, int y);
int posicao_ocupada(ESTADO *e, int x, int y);
int jogador_perto(ESTADO *e, int x, int y);
int obstaculo_cord(ESTADO *e, int x, int y);
int inimigo_cord(ESTADO *e, int x, int y);
int dist(int x1, int y1, int x2, int y2);
int short_range(int x1, int y1, int x2, int y2);
int double_range(int x1, int y1, int x2, int y2);
int cords_line(int x1, int y1, int x2, int y2);
int cords_vertical(int x1, int y1, int x2, int y2);
int cords_obliqua(int x1, int y1, int x2, int y2);
float diff_angular(int x1, int y1, int x2, int y2);
int dist_casas(int x1, int y1, int x2, int y2);
void neighbours(POSICAO* nbrs, int x, int y);
void halfneighbours(POSICAO* nbrs, int x, int y);
int isattckable(ESTADO* e, int x, int y);
int archer_range ( ESTADO* e, int x, int y);


/*print.c-----------------------------------------------------------------------*/

/*
	As funções aqui definidas tratam da representação visual do estado do jogo,
	desde a impressão do tabuleiro à impressão dp jogador e das células
	"clicáveis" que fazem o jogo avançar.
*/

void imprime_inimigo(ESTADO *e, int x, int y);
void imprime_obstaculo(int x, int y);
void imprime_casa(ESTADO *e, int x, int y);
void imprime_casa_hl(ESTADO *e, int x, int y);
void imprime_trapdoor(ESTADO *e);
void imprime_movimento(ESTADO *e, int dx, int dy, char mode, char * id);
void imprime_power_salto(ESTADO *e);
void imprime_powers(ESTADO *e);
void imprime_movimentos(ESTADO *e);
void imprime_movimentos_d(ESTADO *e);
void imprime_jogador(ESTADO *e);
void imprime_inimigos(ESTADO *e);
void imprime_obstaculos(ESTADO *e);
void imprime_estado(ESTADO *e);
int get_posx(int x, int y);
int get_posy(int y);
void print_hex(int x, int y, char * cor);
void print_hexpos(int x, int y, char* cor);
void print_hex_trans(int x, int y);
void print_hexpos_trans(int x, int y);
void hex_grid();
void imprime_alg(int n, int x, int y, int size);
void imprime_int(int n, int x, int y,int size);
void print_hscores();
void imprime_power_flames(ESTADO * e);
void imprime_help();
void imprime_bot();

/** \brief O nº máximo de colunas no mapa (nº de colunas da parte mais larga)*/
#define TAM			5
/** \brief Tamanho de um quadrado em que um hexágono do mapa podia estar inscrito*/
#define ESCALA			75
/** \brief Tamanho de uma imagem colocada dentro de um hexágono do mapa*/
#define ESCALAIMG		3*ESCALA/4
/** \brief Abcissa do vértice mais à esquerda do hexágono mais acima no mapa*/
#define XSTART			295
/** \brief Ordenada do vértice mais à esquerda do hexágono mais acima no mapa*/
#define YSTART			125
/** \brief A cord os hexágonos do mapao*/
#define COR			"#808080"
/** \brief O desvio horizonal que uma imagem inscrita num hexágono tem da posição do vértice de referência*/
#define DEVX			12
/** \brief O desvio vertical que uma imagem inscrita num hexágono tem da posição do vértice de referência*/
#define DEVY			-30
/** \brief A representação float do número pi*/
#define PI                      3.1415927



/*react.c-----------------------------------------------------------------------*/
/*
	Módulo onde se encontra definido o procedimento do programa quando é efetuado
	um movimento pelo jogador. i.e. movimentação dos inimigos.
*/

void move_inimigo_a(ESTADO *e, int n);
void move_inimigo_m(ESTADO *e, int n);
void react_inimigo_m(ESTADO *e, int n);
void react_inimigo_a(ESTADO *e, int n);
void react_inimigos(ESTADO *e);
void react(ESTADO *e);


/*battle.c-----------------------------------------------------------------------*/
/*
	Módulo onde está implementado o sistema de ataque a NPC's (inimigos e
	obstáculos).
*/
void delete_obstaculo(ESTADO *e, int n);
void delete_inimigo(ESTADO *e, int n);
void attack(ESTADO *e, int x, int y);


/*animate.c-----------------------------------------------------------------------*/
/*
	Implementação de animações SVG (por uma questão de flexibilidade, não
	foram definidas macros para tal, tendo em conta que havia uma grande
	variação dos parâmetros a transmitir às diferentes funções). Poder-se-ia
	dizer que este é uma espécie de submódulo do "print.c", mas decidimos
	implementá-lo separadamente devido ao distinto modo de funcionamento e
	ao contraste visual entre o código destas funções e as do outro módulo.
*/

void translateplayer(ESTADO *e);
void translateenemy(ESTADO *e, int id);
void fireball(ESTADO *e, int id);



/*pathfind.c-----------------------------------------------------------------------*/

/*
	Módulo onde está implementado o sistema de pathfinding.
*/


POSICAO visit_step(int matriz[6][21], int a, int b, int x, int y);
void preenche_vizinhos(ESTADO * e, int matriz[6][21], int a, int b, int d, int x, int y);
void preenche_matriz(ESTADO * e, int matriz[6][21], int a, int b, int x, int y);
POSICAO step(ESTADO *e, int a, int b, int x, int y);
void matriz_condicionada_ataques(ESTADO * e, int matriz[6][21]);
POSICAO step_condicionado(ESTADO *e, int a, int b, int x, int y);


/*script.c-----------------------------------------------------------------------*/

void keys_b();
void keys_bs();
void auto_walk(ESTADO * e);
void use_bot(ESTADO * e);


/*bot.c-----------------------------------------------------------------------*/

void auto_move(ESTADO *e, char *  returned);
void defend(ESTADO *e, char *  returned);
void run_away(ESTADO *e, char *  returned);
void offense(ESTADO *e, char *  returned);
void quem_vai_a_guerra_da_e_leva(ESTADO * e, char * returned);


/*main.c-----------------------------------------------------------------------*/

/*
	Módulo principal, onde está delineado o funcionamento do programa e são
	chamadas direta ou indiretamente todas as funções existentes no projeto.
*/

void inicializar_inimigo(ESTADO *e, char type);
void inicializar_trapdoor (ESTADO *e);
void inicializar_obstaculo(ESTADO *e);
void inicializar_obstaculos(ESTADO *e, int num);
void inicializar_inimigos(ESTADO *e);
void inicializar_jogador(ESTADO *e);
ESTADO estadozero();
void inicializar(ESTADO *e);
void reinicializar_jogador(ESTADO *e);
void ler_estado(ESTADO *e, char *args);
void homescreen(ESTADO *e);
void printhomescreen();
void gameover(ESTADO *e);
void control_estado(ESTADO *e);
void imprime_info(ESTADO *e);
void construir_estado(ESTADO *e, char* args);
void merge_estadoargs(ESTADO * e, char* args);
void jogada(ESTADO *e, int x, int y);
void printhomescreen();
void aoe_skill(ESTADO* e);
void estado_doublejump(ESTADO * e);
void estado_enemyattackinfo( ESTADO * e);
void estado_staticmove(ESTADO * e, char * args);
void estado_bot(ESTADO * e);







/* LIBRARIES, não sei porque é que isto é necessário...*/
void srandom(unsigned int seed);
long int random(void);
double round (double a);
