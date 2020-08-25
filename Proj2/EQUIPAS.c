/*  
Ficheiro: EQUIPAS.c
Nome: Joao Rui Vargas de Matos 
Numero: 95610 
Descricao: Ficheiro source auxiliar que manipula as equipas 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EQUIPAS.h"

/*Devolve a chave para as equipas*/
int E_hash(char *v, int M){
    int h = 0, a = 919;
    for (; *v != '\0'; v++)
        h = (a*h + *v) % M;
    return h;
}

/*Inicializa a hashtable das equipas*/
Elink* E_Init() {
    int i;
    Elink* Eheads;
    Eheads =(Elink*)malloc(HASH_E*sizeof(Elink));
    for (i = 0; i < HASH_E; i++) 
        Eheads[i] = NULL;
    return Eheads;
}

/*Procura a equipa na hashtable pelo nome da equipa dado pela chave*/
pEquipa E_STSearch(Elink* Eheads,char *nome) {
    int i = E_hash(nome, HASH_E);
    return E_Procura_Hash(Eheads[i], nome);
}

/*Insere uma equipa na hashtable das equipas*/ 
void E_STinsert(Elink* Eheads,pEquipa p) {
    int i = E_hash(p->nome, HASH_E);
    Eheads[i] = E_Push(Eheads[i], p);
}

/*Insere uma equipa num dos ponteiros da hash como o primeiro elemento*/
Elink E_Push(Elink head,pEquipa p){
    Elink next=head;
    head=malloc(sizeof(struct Enode));
    head->next = next;
    head->e=p;
    return head;
}

/*Percorre a hashtable das equipas para destruir os indices*/ 
void Limpa_Eheads(Elink* Eheads){
    int i;
    for (i = 0; i < HASH_E; i++) 
        destroy_E(Eheads[i]);
    free(Eheads);
}

/*Da free ao primeiro elemento da lista num dos indices da hashtable*/
Elink Epop(Elink head) {
    Elink next;
    if (!head) return NULL;
    next = head->next;
    free(head->e->nome);
    free(head->e);
    free(head);
    return next;
}

/*Da sucessivamente pop ate o head for NULL*/
Elink destroy_E(Elink head) {
    while(head)
        head = Epop(head);
    return NULL;   
}

/*Procura o jogo num dos indice da hashtable*/
pEquipa E_Procura_Hash(Elink head, char* nome){
    Elink t;
    for(t = head; t != NULL; t = t->next)
        if(strcmp(t->e->nome, nome) == 0)
            return t->e;
    return NULL;
}

/*Funcao que e usada como criterio de comparacao para ordenar equipas por ordem lexicografica*/
int Compara_strcmp (const void * a, const void * b ) {
    return strcmp(*(const char**)a,*(const char**)b);
}