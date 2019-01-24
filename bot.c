#include "header.h"



/**
	@file bot.c Este ficheiro contém as funções que geram o funcionamento
        do bot que pode ser utilizado para o jogo correr sem necessidade de
        intervenção humana.
*/





/**
	\brief Averigua se o jogador pode matar um inimigo, mesmo não estando em risco
	@param e Apontador para o estado do jogo.
	@param pos Posição onde pode (ou não) ser registada a posição da proxima jogada
*/
void safeattack(ESTADO *e, POSICAO * pos) {
        int x = e->jog.pos.x;
        int y = e->jog.pos.y;

        int i, count;
        POSICAO vizinhos[6];
        neighbours(vizinhos, x, y);

        for(i = 0, count = 0; i < 6; i++)
                if (tem_inimigo(e, vizinhos[i].x, vizinhos[i].y))
                        count++;

        if(count > 0) {
                for(i = 0; !tem_inimigo(e, vizinhos[i].x, vizinhos[i].y); i++)
                        ;

                pos->x = vizinhos[i].x;
                pos->y = vizinhos[i].y;
        }

}






/**
	\brief Gere uma jogada ofensiva por parte do bot.
	@param e Apontador para o estado do jogo.
	@param returned String onde será escrita a nova jogada
*/
void offense(ESTADO *e, char * returned) {

        POSICAO proxima_posicao = e->jog.pos;

        safeattack(e, &proxima_posicao);

        if (proxima_posicao.x == e->jog.pos.x && proxima_posicao.y == e->jog.pos.y) {
                int x = e->jog.pos.x;
                int y = e->jog.pos.y;

                POSICAO vizinhos[6];
                neighbours(vizinhos, x, y);

                proxima_posicao = step(e, x, y, e->trapdoor.x, e->trapdoor.y);

                if (isattckable(e, proxima_posicao.x, proxima_posicao.y)
                || (proxima_posicao.x == x && proxima_posicao.y ==y) ) {
                        proxima_posicao.x = x;
                        proxima_posicao.y = y;

                        int m_dist = 100;

                        for(int i = 0; i < 6 && vizinhos[i].x != -1; i++)
                                if(tem_inimigo(e, vizinhos[i].x, vizinhos[i].y)) {
                                        proxima_posicao = vizinhos[i];
                                        break;
                                }
                                else if (dist_casas(e->trapdoor.x, e->trapdoor.y, vizinhos[i].x, vizinhos[i].y) < m_dist
                                && !isattckable(e, vizinhos[i].x, vizinhos[i].y) && posicao_valida(vizinhos[i].x, vizinhos[i].y)) {
                                        proxima_posicao = vizinhos[i];
                                        m_dist = dist_casas(e->trapdoor.x, e->trapdoor.y, vizinhos[i].x, vizinhos[i].y);
                                }
                }
        }

        sprintf(returned, "g,%d,%d", proxima_posicao.x, proxima_posicao.y);

}


/**
\brief Gere uma jogada em que, por falta de ataques especiais, resta ao bot
a escolha de matar um inimigo que esteja à sua beira.
@param e Apontador para o estado do jogo.
@param returned String onde será escrita a nova jogada
*/
void quem_vai_a_guerra_da_e_leva(ESTADO * e, char * returned) {
        int x = e->jog.pos.x;
        int y = e->jog.pos.y;


        POSICAO vizinhos[6];
        neighbours(vizinhos, x, y);

        POSICAO proxima_posicao = {x, y};

        for (int i = 0; i < 6 && vizinhos[i].x != -1; i++)
        if (tem_inimigo(e, vizinhos[i].x, vizinhos[i].y)) {
                proxima_posicao = vizinhos[i];
                break;
        }

        sprintf(returned, "g,%d,%d", proxima_posicao.x, proxima_posicao.y);
}



/**
	\brief Uma função que encontra a próxima jogada de uma maneira alternativa
                ao sistema de pathfinding, que, embora seja mais preciso, por vezes
                torna-se inutilizável.
	@param e Apontador para o estado do jogo.
	@param pos Posição em que será registada a proxima jogada.
*/
void run_distance(ESTADO * e, POSICAO * pos) {
        int x = e->jog.pos.x;
        int y = e->jog.pos.y;

        POSICAO vizinhos[6], semivizinhos[12];
        neighbours(vizinhos, x, y);
        halfneighbours(semivizinhos, x, y);
        int dist_to_trapdoor = 100;


        for (int i = 0; i < 6 && vizinhos[i].x != -1; i++)
                if (dist_casas(vizinhos[i].x, vizinhos[i].y, e->trapdoor.x, e->trapdoor.y) < dist_to_trapdoor
                && !isattckable(e, vizinhos[i].x, vizinhos[i].y)
                && !tem_obstaculo(e, vizinhos[i].x, vizinhos[i].y)) {
                        pos->x = vizinhos[i].x;
                        pos->y = vizinhos[i].y;
                        dist_to_trapdoor = dist_casas(vizinhos[i].x, vizinhos[i].y, e->trapdoor.x, e->trapdoor.y);
                }

        if (e->jog.jump > 0)
                for (int i = 0; i < 12 && semivizinhos[i].x != -1; i++)
                        if (dist_casas(semivizinhos[i].x, semivizinhos[i].y, e->trapdoor.x, e->trapdoor.y) < dist_to_trapdoor
                        && !isattckable(e, semivizinhos[i].x, semivizinhos[i].y)
                        && !posicao_ocupada(e, semivizinhos[i].x, semivizinhos[i].y)) {
                                pos->x = semivizinhos[i].x;
                                pos->y = semivizinhos[i].y;
                                dist_to_trapdoor = dist_casas(semivizinhos[i].x, semivizinhos[i].y, e->trapdoor.x, e->trapdoor.y);
                        }
}




/**
	\brief Gere uma jogada em que o bot pretende apenas fugir de casas que possam
                ser atacadas por inimigos.
	@param e Apontador para o estado do jogo.
	@param returned String onde será escrita a nova jogada
*/
void run_away(ESTADO * e, char * returned) {
        int x = e->jog.pos.x;
        int y = e->jog.pos.y;

        POSICAO proxima_posicao = {x, y};
        proxima_posicao = step(e, x, y, e->trapdoor.x, e->trapdoor.y);

        if(isattckable(e, proxima_posicao.x, proxima_posicao.y))
                run_distance(e, &proxima_posicao);

        if ( proxima_posicao.x == x && proxima_posicao.y == y)
                quem_vai_a_guerra_da_e_leva(e, returned);

        else if (double_range(proxima_posicao.x, proxima_posicao.y, x, y)
        && !short_range(proxima_posicao.x, proxima_posicao.y, x, y)) {
                if(e->jog.mode == 'd') {
                        sprintf(returned, "g,%d,%d", proxima_posicao.x, proxima_posicao.y);
                        e->jog.mode = 'n';
                }
                else
                        sprintf(returned, "d");
        }
        else
                sprintf(returned, "g,%d,%d", proxima_posicao.x, proxima_posicao.y);
}







/**
	\brief Gere uma jogada defensiva por parte do bot.
	@param e Apontador para o estado do jogo.
	@param returned String onde será escrita a nova jogada
*/
void defend(ESTADO * e, char * returned){
        int x = e->jog.pos.x;
        int y = e->jog.pos.y;

        int i, count;
        POSICAO vizinhos[6];
        neighbours(vizinhos, x, y);

        for(i = 0, count = 0; i < 6; i++)
                if (tem_inimigo(e, vizinhos[i].x, vizinhos[i].y))
                        count++;

        if(count > 1)
                if (e->jog.flames > 0)
                        sprintf(returned, "b");
                else
                        run_away(e, returned);
        else if (count == 1 && !archer_range(e, x, y)) {

                for (i = 0; i< 6; i++)
                        if (tem_inimigo(e, vizinhos[i].x, vizinhos[i].y))
                                break;
                sprintf(returned, "g,%d,%d", vizinhos[i].x, vizinhos[i].y);

        }
        else
                run_away(e, returned);

}







/**
	\brief Gere uma jogada feita pelo bot, dependendo do estado do jogo.
	@param e Apontador para o estado do jogo.
	@param returned String onde será escrita a nova jogada
*/
void auto_move(ESTADO * e, char * returned){
        int x = e->jog.pos.x;
        int y = e->jog.pos.y;

        if (short_range(x, y, e->trapdoor.x, e->trapdoor.y)) {
                sprintf(returned, "tr");
                return;
        }

        if (isattckable(e, x, y))
                defend(e, returned);
        else
                offense(e, returned);

}
