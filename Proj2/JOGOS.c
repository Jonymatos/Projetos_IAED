/*  
Ficheiro: JOGOS.c
Nome: Joao Rui Vargas de Matos 
Numero: 95610 
Descricao: Ficheiro source auxiliar que manipula os jogos
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JOGOS.h"

/*Devolve a chave para os jogos*/
int J_hash(char *v, int M){
    int h = 0, a = 919;
    for (; *v != '\0'; v++){
        h = (a*h + *v) % M;}
    return h;
}

/*Inicializa a lista dos jogos*/
Q QUEUEinit() {
    Q q = (Q)malloc(sizeof(struct queue));
    q->head = NULL;
    q->tail = NULL;
    return q;
} 

/*Inicializa a hashtable dos jogos*/
Jlink* J_Init() {
    int i;
    Jlink* Jheads;
    Jheads =(Jlink*)malloc(HASH_J*sizeof(Jlink));
    for (i = 0; i < HASH_J; i++) 
        Jheads[i] = NULL;
    return Jheads;
}

/*Procura o jogo na hashtable pelo nome do jogo dado pela chave*/
pJogo J_STSearch(Jlink* Jheads,char *nome) {
    int i = J_hash(nome, HASH_J);
    return J_Procura_Hash(Jheads[i], nome);
}

/*Insere um jogo na hashtable dos jogos e na lista dos jogos*/ 
void J_STinsert(Q Todos_Jogos,Jlink* Jheads,pJogo p) {
    int i = J_hash(p->nome, HASH_J);
    Jheads[i] = J_Push(Todos_Jogos, Jheads[i], p);
}

/*Insere um jogo num dos ponteiros da hash como o primeiro elemento*/
Jlink J_Push(Q Todos_Jogos,Jlink head,pJogo p){
    Jlink next=head;
    head=(Jlink)malloc(sizeof(struct Jnode));
    head->next = next;
    head->j=p;
    head->pass=QUEUEput(Todos_Jogos,p);
    return head;
}

/*Remove um jogo na hashtable e na lista dado pelo jogo dado pela chave*/ 
void J_STdelete(Jlink* Jheads,Q Todos_Jogos,pJogo p){
    int i = J_hash(p->nome, HASH_J);
    Jheads[i]=Apaga_Jogo_Hash(Jheads[i],Todos_Jogos,p);
}

/*Remove um jogo numa dos indices da hashtable e na lista dado pelo jogo*/
Jlink Apaga_Jogo_Hash(Jlink head, Q q, pJogo p){
    Jlink t,pre;
    /*Ciclo responsavel pela procura do jogo*/
    for(pre=NULL,t = head; t != NULL;pre = t, t = t->next) {
        if(strcmp(t->j->nome,p->nome) == 0) { /*Primeiro remove o no da lista dos jogos dando free*/
            /*Se o no da lista do jogo for o primeiro no, ou seja a head, so da pop ao primeiro no*/
            if (!t->pass->prev)
                QUEUE_Pop(q);
            /*Se o no for o ultimo atualiza a tail da lista e da free ao no a seguir*/
            else if (!t->pass->next){
                q->tail=q->tail->prev;
                q->tail->next=NULL;
                free(t->pass);}
            /*Caso geral de removacao do no na lsita*/
            else{
                Qlink ant=t->pass->prev,prox=t->pass->next;
                ant->next=prox;
                prox->prev=ant;
                free(t->pass);}
            /*Seguidamente remove pela hashtable*/
            if(t == head)
                head = t->next;
            else
                pre->next = t->next;
            /*Da free do no da hashtable e termina o ciclo no que retorna a nova head*/
            FREE_Jnode(t);
            break;}
        }
    return head;
}

/*Percorre a hashtable dos jogos para destruir os indices*/
void Limpa_Jheads(Jlink* Jheads){
    int i;
    for (i = 0; i < HASH_J; i++) 
        destroy_J(Jheads[i]);
    free(Jheads);
}

/*Da free ao primeiro elemento da lista num dos indices da hashtable*/
Jlink Jpop(Jlink head) {
    Jlink next;
    if (!head) return NULL;
    next = head->next;
    FREE_Jnode(head);
    return next;
}

/*Da sucessivamente pop ate o head for NULL*/
Jlink destroy_J(Jlink head) {
    while(head)
        head = Jpop(head);
    return NULL;   
}

/*Procura o jogo num dos indice da hashtable*/
pJogo J_Procura_Hash(Jlink head, char* nome){
    Jlink t;
    for(t = head; t != NULL; t = t->next)
        if(strcmp(t->j->nome, nome) == 0)
            return t->j;
    return NULL;
}

/*Insere o jogo como o primeiro elemento num dos indices da hashtable dos jogos*/
Qlink QUEUEput(Q q, pJogo p) {
    if (q->head == NULL) {
        q->head = (q->tail = NEWnode(p, q->head));
        q->head->prev=NULL;
        return q->head;}
    q->tail->next = NEWnode(p, q->tail->next);
    q->tail->next->prev=q->tail;
    q->tail = q->tail->next;
    return q->tail;
}

/*Aloca dinamicamente um novo no para a lista dos jogos*/
Qlink NEWnode(pJogo p, Qlink next) {
    Qlink x = (Qlink) malloc(sizeof(struct QUEUEjogos));
    x->j = p;
    x->next = next;
    return x;
}

/*Destroi a lista dos jogos ate a head for NULL*/
void Limpa_QUEUE(Q Todos_Jogos){
    while(Todos_Jogos->head!=NULL)
        Todos_Jogos = QUEUE_Pop(Todos_Jogos);
    free(Todos_Jogos);
}

/*Destroi o primeiro elemento da lista dos jogos*/
Q QUEUE_Pop(Q q){
    Qlink t = q->head->next;
    free(q->head);
    q->head = t;
    if (q->head)
        q->head->prev=NULL;
    return q;
}

/*Destroi os ponteiros de um no da hashtable dos jogos*/
void FREE_Jnode(Jlink head){
    free(head->j->nome);
    free(head->j->equipa1);
    free(head->j->equipa2);
    free(head->j);
    free(head);
}