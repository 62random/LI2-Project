
/**
@file estado.h
Definição do estado e das funções que convertem estados em strings e vice-versa
*/

/** \brief O nº máximo de inimigos na struct do estado*/
#define MAX_INIMIGOS		20

/** \brief O nº máximo de obstáculos na struct do estado*/
#define MAX_OBSTACULOS		20

/** \brief Estrutura que armazena uma posição*/
typedef struct posicao {
	/** \brief 1ª coordenada (uma "pseudo-abcissa", tendo em conta que o sistema
	de coordenadas é hexagonal e não ortonormado)*/
	char x;
	/** \brief 1ª coordenada (uma "pseudo-ordenada", tendo em conta que o sistema
	de coordenadas é hexagonal e não ortonormado)*/
	char y;
} POSICAO;



/**
\brief Estrutura que descreve o jogador
*/

typedef struct player {
	/** \brief A jogada ANTERIOR da personagem. e.g 'a' de ataque*/
	char last;
	/** \brief A posição ANTERIOR da personagem */
	POSICAO prevpos;
	/** \brief A posição da personagem */
	POSICAO pos;
	/** \brief O modo em que o jogador se encontra (ou skill ativada) m */
	char mode;
	/** \brief Int que representa os health points da personagem */
	int hp;
	/**vezes que ainda pode utilizar o poder jump"*/
	int jump;
	/**vezes que ainda pode utilizar o poder flames"*/
	int flames;
	/** \brief Int que representa os damage points da personagem */
	int dmg;
	/** \brief Int que representa os experience points do jogador
	que são também a sua pontuação no jogo */
	int exp;
} PLAYER;


/**
\brief Estrutura que descreve uma non playable character
*/
typedef struct npc {
	/** \brief A jogada ANTERIOR da personagem. e.g 'a' de ataque*/
	char last;
	/** \brief A posição ANTERIOR da personagem */
	POSICAO prevpos;
	/** \brief A posição da personagem */
	POSICAO pos;
	/** \brief O "tipo" de uma personagem
	(um caracter que representa cetos atributos)*/
	char type;
	/** \brief Int que representa os health points da personagem */
	int hp;
	/** \brief Int que representa os damage points da personagem */
	int dmg;
	/** \brief Int que representa os experience points da personagem */
	int exp;
} NPC;




/**
\brief Estrutura que armazena o estado do jogo
*/
typedef struct estado {
	/** \brief char que caracteriza o ecrã em que o jogo se encontra*/
	char screen;
	/** \brief char que indica se o jogo está em modo de jogo automático*/
	char bot;
	/** \brief Nível em que a dungeon se encontra*/
	int lvl;
	/** \brief porta para o próximo nível */
	POSICAO trapdoor;
	/** \brief A posição do jogador */
	PLAYER jog;
	/** \brief O nº de inimigos */
	char num_inimigos;
	/** \brief O nº de obstáculos */
	char num_obstaculos;
	/** \brief Array com a posição dos inimigos */
	NPC inimigo[MAX_INIMIGOS];
	/** \brief Array com a posição dos obstáculos */
	NPC obstaculo[MAX_OBSTACULOS];
} ESTADO;


/**
\brief Estrutura que descreve um high score
*/
typedef struct score {
	/** inteiro que representa o score da partida registada*/
	int num;
	/** char que regista se o score foi feito por um bot*/
	char bot;
} SCORE;

/**
\brief Estrutura que descreve um score board, ou seja, uma lista de high scores
*/
typedef struct hscores{
	/** lista de scores registados */
	SCORE score[5];
} HSCORES;
