/*  
Ficheiro: JOGOS.h
Nome: Joao Rui Vargas de Matos 
Numero: 95610 
Descricao: Ficheiro header auxiliar que manipula os jogos
*/

#ifndef JOGOS_H
#define JOGOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_J 1637

/*Estretura dos jogos*/
typedef struct Jogo{
    char *nome;
    char *equipa1;
    char *equipa2;
    int score1;
    int score2;
}*pJogo;

/*Estretura do no do jogo da hash*/
typedef struct Jnode{
    struct Jnode *next;
    /*Ponteiro pass que aponta para o jogo correspondente na QUEUE dos jogos*/
    struct QUEUEjogos *pass;
    pJogo j;
}*Jlink;

/*Estretura do no da lista dos jogos*/
typedef struct QUEUEjogos{ 
    pJogo j; 
    struct QUEUEjogos *next, *prev;
}*Qlink;

/*Estretura da QUEUE dos jogos*/
typedef struct queue{ Qlink head, tail ;}*Q;

/*Funcoes que manipulam os jogos*/
Q QUEUEinit();
Jlink* J_Init();
int J_hash(char *v, int M);
void J_STinsert(Q Todos_Jogos,Jlink* Jheads,pJogo p);
pJogo J_STSearch(Jlink* Jheads,char *nome);
pJogo J_Procura_Hash(Jlink head, char* nome);
Jlink J_Push(Q Todos_Jogos,Jlink head, pJogo p);
Jlink Apaga_Jogo_Hash(Jlink head,Q q, pJogo p);
Jlink Jpop(Jlink head);
Jlink destroy_J(Jlink head);
Qlink QUEUEput(Q q, pJogo p);
Qlink NEWnode(pJogo p, Qlink next);
Q QUEUE_Pop(Q q);
void J_STdelete(Jlink* Jheads,Q Todos_Jogos, pJogo p);
void FREE_Jnode(Jlink head);
void Limpa_Jheads(Jlink* Jheads);
void Limpa_QUEUE(Q Todos_Jogos);

#endif