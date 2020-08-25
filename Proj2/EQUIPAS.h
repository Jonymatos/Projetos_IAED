/*  
Ficheiro: EQUIPAS.h
Nome: Joao Rui Vargas de Matos 
Numero: 95610 
Descricao: Ficheiro header auxiliar que manipula as equipas 
*/

#ifndef EQUIPAS_H
#define EQUIPAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_E 1637

/*Estretura das equipas*/
typedef struct Equipa{
    char *nome;
    unsigned short int vit;
}*pEquipa;

/*Estretura do no das equipas da hash*/
typedef struct Enode{
    struct Enode *next;
    pEquipa e;
}*Elink;

/*Funcoes que manipulam as equipas*/
int E_hash(char *v, int M);
int Compara_strcmp (const void * a, const void * b );
Elink* E_Init();
void E_STinsert(Elink* Eheads,pEquipa p);
pEquipa E_STSearch(Elink* Eheads,char *nome);
pEquipa E_Procura_Hash(Elink head, char* nome);
pEquipa E_Procura_Hash_Prev(Elink head, char* nome);
Elink E_Push(Elink head, pEquipa p);
void Limpa_Eheads(Elink* Eheads);
Elink Epop(Elink head);
Elink destroy_E(Elink head);

#endif