/*  
Ficheiro: proj2.c
Nome: Joao Rui Vargas de Matos 
Numero: 95610 
Descricao: Codigo do segundo projecto DE IAED desenvolvido em linguagem C 
*/

/* Bibliotecas */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "JOGOS.h"
#include "EQUIPAS.h"

/* Definicao de constante */
#define MAX_CHAR 1023

typedef unsigned int uint;

/*Chamadas de funcoes comandos*/
void Adiciona_Equipa(Elink *Eheads,uint* Cont_Ln,uint* Cont_Eq);
void Adiciona_Jogo(Elink *Eheads,Jlink* Jheads,Q Todos_Jogos,uint* Cont_Ln);
void Imprime_Jogos(Q q,uint* Cont_Ln);
void Procura_Jogo(Jlink *Jheads,uint* Cont_Ln);
void Procura_Equipa(Elink *Eheads,uint* Cont_Ln);
void Remove_Jogo(Elink *Eheads,Jlink* Jheads,Q Todos_Jogos,uint* Cont_Ln);
void Altera_Score(Elink *Eheads,Jlink* Jheads,uint* Cont_Ln);
void Mostra_Melhores_Equipas(Elink *Eheads,uint* Cont_Ln,uint Cont_Eq);
void Limpa(Jlink* Jheads,Elink *Eheads,Q Todos_Jogos);

/*Codigo principal*/
int main(){
    /*Inicializacao da lista de jogos*/
    Q Todos_Jogos=QUEUEinit();
    /*Inicializacao da hastables das equipas e jogos*/
    Elink* Eheads=E_Init();
    Jlink* Jheads=J_Init();
    int car=getchar();
    uint Cont_Ln=1,Cont_Eq=0;
    while (car!='x'){
        switch(car){
            case 'a':
                Adiciona_Jogo(Eheads,Jheads,Todos_Jogos,&Cont_Ln);
                break;
            case 'A':
                Adiciona_Equipa(Eheads,&Cont_Ln,&Cont_Eq);
                break;
            case 'l':
                Imprime_Jogos(Todos_Jogos,&Cont_Ln);
                break;
            case 'p':
                Procura_Jogo(Jheads,&Cont_Ln);
                break; 
            case 'P':
                Procura_Equipa(Eheads,&Cont_Ln);
                break;
            case 'r':
                Remove_Jogo(Eheads,Jheads,Todos_Jogos,&Cont_Ln);
                break;
            case 's':
                Altera_Score(Eheads,Jheads,&Cont_Ln);
                break;
            case 'g':
                Mostra_Melhores_Equipas(Eheads,&Cont_Ln,Cont_Eq);
                break;
        }
        car=getchar();
    }
    Limpa(Jheads,Eheads,Todos_Jogos);
    return 0;
}

/*Adiciona um jogo no sistema imprime erro se as equipas nao existirem ou se o jogo ja existir*/
void Adiciona_Jogo(Elink *Eheads,Jlink* Jheads,Q Todos_Jogos,uint* Cont_Ln){   
    char nome[MAX_CHAR],equipa1[MAX_CHAR],equipa2[MAX_CHAR];
    uint score1,score2;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]",nome,equipa1,equipa2);
    scanf(":%u:%u",&score1,&score2);
    if (J_STSearch(Jheads,nome)!=NULL)
        printf("%u Jogo existente.\n",*Cont_Ln);
    else if (!(E_STSearch(Eheads,equipa1)) || (!E_STSearch(Eheads,equipa2)))
        printf("%u Equipa inexistente.\n",*Cont_Ln);
    else{
        /*Alocacao dinamica do jogo*/
        pJogo j;
        j=(pJogo) malloc(sizeof(struct Jogo));
        j->score1=score1;j->score2=score2;
        j->nome=(char*) malloc(sizeof(char)*(strlen(nome)+1));
        strcpy(j->nome,nome);
        j->equipa1=(char*) malloc(sizeof(char)*(strlen(equipa1)+1));
        strcpy(j->equipa1,equipa1);
        j->equipa2=(char*) malloc(sizeof(char)*(strlen(equipa2)+1));
        strcpy(j->equipa2,equipa2);
        J_STinsert(Todos_Jogos,Jheads,j);
        /*Atualizacao do numero de vitorias se houver vencedor*/
        if (score1>score2){
            pEquipa e=E_STSearch(Eheads,equipa1);
            e->vit++;}
        else if (score1<score2){
            pEquipa e=E_STSearch(Eheads,equipa2);
            e->vit++;}
        }
    (*Cont_Ln)++;
}

/*Imprime os jogos por ordem de insercao, (errros nao aplicaveis)*/
void Imprime_Jogos(Q q,uint* Cont_Ln){
    Qlink ptr = q->head;
    for(;ptr;ptr=ptr->next){
        printf("%u ",*Cont_Ln);
        printf("%s ",ptr->j->nome);
        printf("%s ",ptr->j->equipa1);
        printf("%s ",ptr->j->equipa2);
        printf("%u %u\n",ptr->j->score1,ptr->j->score2);
    }
    (*Cont_Ln)++;
}

/*Procura um determinado jogo e imprime erro se esse jogo nao existir*/
void Procura_Jogo(Jlink* Jheads,uint* Cont_Ln){
    pJogo ptrJogo;
    char buffer[MAX_CHAR];
    scanf(" %[^:\n]",buffer);
    ptrJogo=J_STSearch(Jheads,buffer);
    if(!ptrJogo)
        printf("%u Jogo inexistente.\n",*Cont_Ln);
    else{
        printf("%u %s %s %s ",*Cont_Ln,ptrJogo->nome,ptrJogo->equipa1,ptrJogo->equipa2);
        printf("%u %u\n",ptrJogo->score1,ptrJogo->score2);}
    (*Cont_Ln)++;
}

/*Adiciona uma equipa no sistema imprime erro se essa equipa ja existir*/
void Adiciona_Equipa(Elink *Eheads,uint* Cont_Ln,uint* Cont_Eq){
    char buffer[MAX_CHAR];
    scanf(" %[^:\n]",buffer);
    if (E_STSearch(Eheads,buffer)!=NULL)
        printf("%u Equipa existente.\n",*Cont_Ln);
    else{
        /*Alocacao dinamica da equipa*/
        pEquipa e;
        e=(pEquipa) malloc(sizeof(struct Equipa));
        e->nome=(char*) malloc(sizeof(char)*(strlen(buffer)+1));
        strcpy(e->nome,buffer);e->vit=0;
        /*Insersecao da equipa e atualizacao do numero de equipas*/
        E_STinsert(Eheads,e);
        (*Cont_Eq)++;}
    (*Cont_Ln)++;
}

/*Procura uma determinado equipa e imprime erro se essa equipa nao existir*/
void Procura_Equipa(Elink *Eheads,uint* Cont_Ln){
    pEquipa ptrEquipa;
    char buffer[MAX_CHAR];
    scanf(" %[^:\n]",buffer);
    ptrEquipa=E_STSearch(Eheads,buffer);
    if (!ptrEquipa)
        printf("%u Equipa inexistente.\n",*Cont_Ln);
    else
        printf("%u %s %d\n",*Cont_Ln,ptrEquipa->nome,ptrEquipa->vit);
    (*Cont_Ln)++;
}

/*Remove um determinado jogo no sistema e imprime erro se esse jogo nao existir*/
void Remove_Jogo(Elink *Eheads,Jlink* Jheads,Q Todos_Jogos,uint* Cont_Ln){
    pJogo ptrJogo;
    char buffer[MAX_CHAR];
    scanf(" %[^:\n]",buffer);
    ptrJogo=J_STSearch(Jheads,buffer);
    if(!ptrJogo)
        printf("%u Jogo inexistente.\n",*Cont_Ln);
    else{
        uint score1=ptrJogo->score1,score2=ptrJogo->score2;
        /*Decrementacao do numero de vitorias se houver vencedores antes de remover o jogo*/
        if (score1>score2){
            pEquipa e=E_STSearch(Eheads,ptrJogo->equipa1);
            e->vit--;}
        else if (score1<score2){
            pEquipa e=E_STSearch(Eheads,ptrJogo->equipa2);
            e->vit--;}
        /*Finalmente remove o jogo*/
        J_STdelete(Jheads,Todos_Jogos,ptrJogo);
    }
    (*Cont_Ln)++;
}

/*Altera o resultado de um determinado jogo devolve erro se esse jogo nao existir*/
void Altera_Score(Elink *Eheads,Jlink* Jheads,uint* Cont_Ln){
    pJogo ptrJogo;
    char buffer[MAX_CHAR];
    uint new_sc1,new_sc2;
    scanf(" %[^:\n]:%u:%u",buffer,&new_sc1,&new_sc2);
    ptrJogo=J_STSearch(Jheads,buffer);
    if(!ptrJogo)
        printf("%u Jogo inexistente.\n",*Cont_Ln);
    else{
        uint ant_sc1=ptrJogo->score1,ant_sc2=ptrJogo->score2;
        pEquipa e1=E_STSearch(Eheads,ptrJogo->equipa1),e2=E_STSearch(Eheads,ptrJogo->equipa2);
        /*Exploracao de todos os casos possiveis para atualizar o numero de vitorias das equipas*/
        if ((ant_sc1>ant_sc2)&&(new_sc1==new_sc2))
            e1->vit--;
        else if ((ant_sc1<ant_sc2)&&(new_sc1==new_sc2))
            e2->vit--;
        else if ((ant_sc1==ant_sc2)&&(new_sc1>new_sc2))
            e1->vit++;
        else if ((ant_sc1==ant_sc2)&&(new_sc1<new_sc2))
            e2->vit++;
        else if ((ant_sc1>ant_sc2)&&(new_sc1<new_sc2)){
            e1->vit--;e2->vit++;}
        else if ((ant_sc1<ant_sc2)&&(new_sc1>new_sc2)){
            e1->vit++;e2->vit--;}
        ptrJogo->score1=new_sc1;ptrJogo->score2=new_sc2;  
    }
    (*Cont_Ln)++;  
}

/*Mostra as equipas que ganharam mais jogos por ordem lexicografica
erros nao aplicaveis*/
void Mostra_Melhores_Equipas(Elink *Eheads,uint* Cont_Ln,uint Cont_Eq){
    if (Cont_Eq){
        int i,m_vit=0,Lim_equipas=0;
        /*Alocacao dinamica do vetor de chars usado para colocar as equipas*/
        char **equipas =(char**)malloc(sizeof(char*)*Cont_Eq);
        /*Ciclo que procura pelo maior umero de vitorias*/ 
        for (i = 0; i < HASH_E; i++){
            Elink ptr = Eheads[i];
            for(;ptr;ptr=ptr->next){
                if ((ptr->e->vit)>(m_vit))
                    m_vit=ptr->e->vit;
            }
        }
        /*Ciclo que procura as equipas com mais vitorias e que insere no vetor*/
        for (i = 0; i < HASH_E; i++){
            Elink ptr = Eheads[i];
            for(;ptr;ptr=ptr->next){
                if ((ptr->e->vit)==(m_vit)){
                    equipas[Lim_equipas]=(char*) malloc(sizeof(char)*(strlen(ptr->e->nome)+1));
                    strcpy(equipas[Lim_equipas],ptr->e->nome);
                    Lim_equipas++;}
            }
        }
        /*Ordenacao por ordem lexicografica*/
        qsort(equipas,Lim_equipas,sizeof(char *),Compara_strcmp);
        printf("%u Melhores %u\n",*Cont_Ln,m_vit);
        /*Imprime as equipas e da free a seguir ao indice do vetor*/
        for (i=0; i < Lim_equipas; i++){
            printf("%u * %s\n", *Cont_Ln, equipas[i]);
            free(equipas[i]);}
        /*Free do vetor das equipas*/
        free(equipas);}
    (*Cont_Ln)++;
}

/*Funcao que da free as hastables e a lista dos jogos antes de finalizar o programa*/
void Limpa(Jlink* Jheads,Elink* Eheads,Q Todos_Jogos){
    Limpa_Jheads(Jheads);
    Limpa_Eheads(Eheads);
    Limpa_QUEUE(Todos_Jogos);
}
