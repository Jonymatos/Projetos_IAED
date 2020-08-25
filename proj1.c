/*  
Ficheiro: proj1.c
Nome: Joao Rui Vargas de Matos 
Numero: 95610 
Descricao: Codigo do primeiro projecto DE IAED desenvolvido em linguagem C 
*/

/* Bibliotecas */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Definicao de constantes */
#define MAX_PROD 10000
#define MAX_CHAR 63
#define MAX_PESO 200
#define MAX_ENCO 500

/* Definicao de chaves de abstracao */
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define equal(A, B) (key(A) == key(B))

/* Definicao de estreturas de dados */
typedef unsigned int uint;
typedef struct Produto{
    uint Id;
    char Descricao[MAX_CHAR];
    uint Preco;
    uint Peso;
    uint Stock;
}Produto;

/* Chamada de variaveis e de tabelas globais que servem para
atualizar e guardar os produtos e as encomendas respetivamente.*/
uint Cont_Prod=0,Cont_Eco=0;
Produto Vet_Prod[MAX_PROD] = {{0},{'\0'},{0},{0},{0}};
Produto Vet_Eco[MAX_ENCO][MAX_PESO] = {{{0},{'\0'},{0},{0},{0}}};
Produto Copia_Prod[MAX_PROD] = {{0},{'\0'},{0},{0},{0}}; /* Vetor auxiliar usado para fazer a ordenacao dos produtos */
Produto Vet_Ordenado[MAX_PROD] = {{0},{'\0'},{0},{0},{0}}; /* Vetor auxiliar que sera usado para copiar valores de acordo com o aMergesort */

/* Chamada de funcoes auxiliares que devolvem o peso e 
a quantidade de uma certa encomenda respetivamente */
uint Calcula_Peso(uint Id_Eco);
uint Devolve_Quant(uint Id_Eco,uint Id_Prod);

/* Chamadas das funcoes utilizadas nos comandos */
Produto Le_Prod();
void Comando_q();
void Comando_r();
void Comando_N();
void Comando_R();
void Comando_A();
void Comando_C();
void Comando_E();
void Comando_p();
void Comando_m();
void Comando_L();
void Comando_l();

/* Chamada das funcoes auxiliares comando l que
sao responsaveis por ordenar o vetor Vet_Ordenado */
void Mergesort(int esq, int dto);
void Merge(int esq, int m, int dto);

/* Codigo principal */
int main(){
    int car=getchar();
    while (car!='x'){
        switch(car){
            case 'a':
                Vet_Prod[Cont_Prod]=Le_Prod();
                break;
            case 'q':
                Comando_q();
                break;
            case 'N':
                Comando_N();
                break;
            case 'A':
                Comando_A();
                break;
            case 'r':
                Comando_r();
                break;
            case 'R':
                Comando_R();
                break;
            case 'C':
                Comando_C();
                break;
            case 'p':
                Comando_p();
                break;
            case 'E':
                Comando_E();
                break;
            case 'm':
                Comando_m();
                break;
            case 'l':
                Comando_l();
                break;
            case 'L':
                Comando_L();
                break;
        }
        car=getchar();}
    return 0;
}

/* Le as caracteristicas de um produtos e associa-o no indice do vetor que guarda os produtos */
Produto Le_Prod(){
    Produto P;
    /* Guardada uma variavel de caracter para ler os dois pontos */
    char dois_pts;
    /* Faz o getchar uma vez a mais para ler o espaco e depois a primeira letra da descricao */
    int i,c=getchar();c=getchar();
    P.Id=Cont_Prod;
    for (i=0;i<MAX_CHAR-1 && c!=':';i++){
        P.Descricao[i]=c;
        c=getchar();}
    P.Descricao[i]='\0';
    scanf("%u %c",&P.Preco,&dois_pts);                        
    scanf("%u %c",&P.Peso,&dois_pts);                         
    scanf("%u",&P.Stock);
    printf("Novo produto %u.\n",Cont_Prod);
    /* Incrementa a varivel global que atualiza o numero de produtos que o sistema tem */
    Cont_Prod++;
    return P;
}

/* Adiciona uma certa quantidade a um determinado produto, 
imprime erro caso a identificacao de um produto nao existir */
void Comando_q(){
    uint Id,Quant;
    char dois_pts;
    scanf("%u %c %u",&Id,&dois_pts,&Quant);
    if (Id>=Cont_Prod)
        printf("Impossivel adicionar produto %u ao stock. Produto inexistente.\n",Id);
    else
        Vet_Prod[Id].Stock+=Quant;
}

/* Adiona uma encomenda ao sistema*/
void Comando_N(){
    printf("Nova encomenda %u.\n",Cont_Eco);
    /* Incrementa a varivel global que atualiza o numero de encomendas que o sistema tem */
    ++Cont_Eco;
}

/* Remove uma certa quantidade uma um determinado produto,
imprime erro caso a identificacao de um produto nao existir
ou de ser impossivel retirar essa quantidade*/
void Comando_r(){
    uint Id_Prod,Quant;
    char dois_pts;
    scanf("%u %c %u",&Id_Prod,&dois_pts,&Quant);
    if (Id_Prod>=Cont_Prod)
        printf("Impossivel remover stock do produto %u. Produto inexistente.\n",Id_Prod);
    else if (Vet_Prod[Id_Prod].Stock<Quant)
        printf("Impossivel remover %u unidades do produto %u do stock. Quantidade insuficiente.\n", Quant, Id_Prod);
    else
        Vet_Prod[Id_Prod].Stock-=Quant;
}

/* Remove toda a quantidade de uma certa encomenda de um determinado produto,
imprime erro caso a identificacao de um produto ou da encomenda nao existir */
void Comando_R(){
    uint Id_Eco,Id_Prod;
    char dois_pts;
    scanf("%u %c %u",&Id_Eco,&dois_pts,&Id_Prod);
    if (Id_Eco>=Cont_Eco)
        printf("Impossivel remover produto %u a encomenda %u. Encomenda inexistente.\n",Id_Prod,Id_Eco);
    else if (Id_Prod>=Cont_Prod)
        printf("Impossivel remover produto %u a encomenda %u. Produto inexistente.\n",Id_Prod,Id_Eco);
    else{
        uint i;
        for (i=0;i<MAX_PESO && Vet_Eco[Id_Eco][i].Preco;i++){
            if (Vet_Eco[Id_Eco][i].Id==Id_Prod){
                Vet_Prod[Id_Prod].Stock+=Vet_Eco[Id_Eco][i].Stock;
                Vet_Eco[Id_Eco][i].Stock=0;
                break;}
        }
    }
}

/* Adiciona uma certa quantidade de um produto a uma encomenda
imprime erro caso a identificacao de um produto ou da encomenda nao existir,
ou se a encomenda exceder o peso */
void Comando_A(){
    uint Id_Eco,Id_Prod,Quant;
    char dois_pts;
    scanf("%u %c %u",&Id_Eco,&dois_pts,&Id_Prod);
    scanf("%c %u",&dois_pts,&Quant);
    if (Id_Eco>=Cont_Eco)
        printf("Impossivel adicionar produto %u a encomenda %u. Encomenda inexistente.\n",Id_Prod,Id_Eco);
    else if (Id_Prod>=Cont_Prod)
        printf("Impossivel adicionar produto %u a encomenda %u. Produto inexistente.\n",Id_Prod,Id_Eco);
    else if (Vet_Prod[Id_Prod].Stock<Quant)
        printf("Impossivel adicionar produto %u a encomenda %u. Quantidade em stock insuficiente.\n",Id_Prod,Id_Eco);
    else if ((Calcula_Peso(Id_Eco)+(Vet_Prod[Id_Prod].Peso*Quant))>MAX_PESO)
        printf("Impossivel adicionar produto %u a encomenda %u. Peso da encomenda excede o maximo de 200.\n",Id_Prod,Id_Eco);
    else{
        uint i;
        for(i=0;i<MAX_PESO;i++){
            /* Se for encontrado um indice vazio sem produto coloca esse produto nesse indice */
            if (!(Vet_Eco[Id_Eco][i].Preco)){
                Vet_Eco[Id_Eco][i]=Vet_Prod[Id_Prod];
                Vet_Eco[Id_Eco][i].Stock=Quant;
                break;}
            /* Se for encontrado um indice com o mesma identificacao do mesmo produto apenas adiciona a quantidade desejada */
            else if (Vet_Eco[Id_Eco][i].Id==Id_Prod){
                Vet_Eco[Id_Eco][i].Stock+=Quant;
                break;}
        }
        Vet_Prod[Id_Prod].Stock-=Quant;}
}

/* Calcula o custo de uma determinada encomenda, imprime erro se a
encomenda referida nao existir no sistema */
void Comando_C(){
    uint Id_Eco;
    scanf("%u",&Id_Eco);
    if (Id_Eco>=Cont_Eco)
        printf("Impossivel calcular custo da encomenda %u. Encomenda inexistente.\n",Id_Eco);
    else{
        uint i,Custo=0;
        for (i=0;i<MAX_PESO && Vet_Eco[Id_Eco][i].Preco;i++)
            Custo+=(Vet_Eco[Id_Eco][i].Preco*Vet_Eco[Id_Eco][i].Stock);
        printf("Custo da encomenda %u %u.\n",Id_Eco,Custo);}
}

/* Mostra a quantidade de um certo produto presente numa dada encomenda,
imprime erro caso a identificacao de um produto ou da encomenda nao existir */
void Comando_E(){
    uint Id_Eco,Id_Prod;
    char dois_pontos;
    scanf("%u %c %u",&Id_Eco,&dois_pontos,&Id_Prod);
    if (Id_Eco>=Cont_Eco)
        printf("Impossivel listar encomenda %u. Encomenda inexistente.\n",Id_Eco);
    else if (Id_Prod>=Cont_Prod)
        printf("Impossivel listar produto %u. Produto inexistente.\n",Id_Prod);
    else
        printf("%s %u.\n",Vet_Prod[Id_Prod].Descricao,Devolve_Quant(Id_Eco,Id_Prod));
}

/* Altera o custo de um certo produto no sistema, imprime erro caso
esse produto nao existir no sistema */
void Comando_p(){
    uint Id_Prod,Preco;
    char dois_pontos;
    scanf("%u %c %u",&Id_Prod,&dois_pontos,&Preco);
    if (Id_Prod>=Cont_Prod)
        printf("Impossivel alterar preco do produto %u. Produto inexistente.\n",Id_Prod);
    else{
        uint i,j;
        /* Primeiro muda o preco no vetor dos produtos */
        Vet_Prod[Id_Prod].Preco=Preco;
        /* Seguidamente muda na matriz das encomendas */
        for (i=0;i<Cont_Eco;i++){
            for (j=0;j<MAX_PESO && Vet_Eco[i][j].Preco;j++){
                if (Vet_Eco[i][j].Id==Id_Prod){
                    Vet_Eco[i][j].Preco=Preco;
                    break;}
            }
        }
    }
}

/* Mostra identificador da encomenda em que um dado produto tem maior quantidade,
imprime erro caso a identificacao de um produto ou da encomenda nao existir */
void Comando_m(){
    uint Id_Prod;
    scanf("%u",&Id_Prod);
    if (Id_Prod>=Cont_Prod)
        printf("Impossivel listar maximo do produto %u. Produto inexistente.\n",Id_Prod);
    else{
        uint i,Quant,Maior_Id=0;
        for (i=0;i<Cont_Eco;i++){
            if (Devolve_Quant(i,Id_Prod)>Devolve_Quant(Maior_Id,Id_Prod))
                Maior_Id=i;}
        Quant=Devolve_Quant(Maior_Id,Id_Prod);
        if (Quant)
            printf("Maximo produto %u %u %u.\n",Id_Prod,Maior_Id,Quant);}
}

/* Lista os produtos de uma encomenda por ordem alfabetica,
usando o insertion sort, imprime erro caso a encomenda nao existir */
void Comando_L(){
    uint Id_Eco;
    Produto Copia_Eco[MAX_PESO];
    scanf("%u",&Id_Eco);
    if (Id_Eco>=Cont_Eco)
        printf("Impossivel listar encomenda %u. Encomenda inexistente.\n",Id_Eco);
    else{
        int i,j,k,lim=-1;
        printf("Encomenda %u\n",Id_Eco);
        for (i=0,k=0;i<MAX_PESO && Vet_Eco[Id_Eco][i].Preco ;i++,k++){
            if (!(Vet_Eco[Id_Eco][i].Stock))
                k--;
            else{
                Copia_Eco[k]=Vet_Eco[Id_Eco][i];
                lim++;}
        }
        for (i=1; i <= lim; i++) {
            Produto P=Copia_Eco[i];
            for (j=i-1;j >= 0 && (strcmp(P.Descricao,Copia_Eco[j].Descricao)<0);j--)
                Copia_Eco[j+1] = Copia_Eco[j];
            Copia_Eco[j+1] = P;}
        for (i=0;i<=lim;i++)
            printf("* %s %u %u\n",Copia_Eco[i].Descricao,Copia_Eco[i].Preco,Copia_Eco[i].Stock);
        }    
}

/* Funcao responsavel pela ordenacao dos produtos */
void Mergesort(int esq, int dto){
    int m = (dto+esq)/2;
    if (dto <= esq)
        return;
    Mergesort(esq, m);
    Mergesort(m+1, dto);
    Merge(esq, m, dto);
}

/* Funcao auxiliar do mergesort que copia os produtos para um vetor 
auxiliar chamado globalmente e responsavel de ordenar os valores */
void Merge(int esq, int m, int dto){
    int i, j, k;
    for (i = m+1; i > esq; i--)
        Copia_Prod[i-1] = Vet_Ordenado[i-1];
    for (j = m; j < dto; j++)
        Copia_Prod[dto+m-j] = Vet_Ordenado[j+1];
    for (k = esq; k <= dto; k++)
        if (less(Copia_Prod[j].Preco,Copia_Prod[i].Preco) || (equal(Copia_Prod[j].Preco,Copia_Prod[i].Preco) && Copia_Prod[j].Id < Copia_Prod[i].Id))
            Vet_Ordenado[k] = Copia_Prod[j--];
        else
            Vet_Ordenado[k] = Copia_Prod[i++];
}


/* Lista os produtos presentes no sistema por ordem crescente do preco
usando o algoritmo de ordenacao mergesort */
void Comando_l(){
    if (!(Cont_Prod))
        printf("Produtos\n");
    else{
        uint i;
        for (i=0;i<=Cont_Prod-1;i++)
            Vet_Ordenado[i]=Vet_Prod[i];
        Mergesort(0,Cont_Prod-1);
        printf("Produtos\n");
        for (i=0;i<=Cont_Prod-1;i++)
            printf("* %s %u %u\n",Vet_Ordenado[i].Descricao,Vet_Ordenado[i].Preco,Vet_Ordenado[i].Stock);}
}

/* Funcao auxiliar que devolve a quntidade de uma certa encomenda */
uint Devolve_Quant(uint Id_Eco,uint Id_Prod){
    uint i,Quant=0;
    for (i=0;i<MAX_PESO && Vet_Eco[Id_Eco][i].Preco;i++){
            if (Vet_Eco[Id_Eco][i].Id==Id_Prod){
                Quant=Vet_Eco[Id_Eco][i].Stock;
                break;}
    }
    return Quant;
}

/* Funcao auxiliar que devolve o peso de uma certa encomenda */
uint Calcula_Peso(uint Id_Eco){
    uint i,Peso=0;
    for (i=0;i<MAX_PESO && Vet_Eco[Id_Eco][i].Preco;i++)
            Peso+=(Vet_Eco[Id_Eco][i].Peso*Vet_Eco[Id_Eco][i].Stock);
    return Peso;
}
