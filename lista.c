/*
GRAFO REPRESENTADO POR LISTAS LIGADAS EM C
*/

#include <stdio.h>
#include <stdlib.h>

// Tipo para armazenar um No da lista de adjacencias
typedef struct _TNo{
    int elem; // w
    struct _TNo *prox;
}TNo;

// TAD - Tipo Abstrato de Dados para representar um grafo.
typedef struct{
	int V; // quantidade de vertices
	int A; // quantidade de arestas
	TNo **adj; //listas de adjac?ncia
}TGrafo;

TGrafo * Init( int V );
void insereA( TGrafo *G, int v, int w);
void show(TGrafo *G);
void indeg(TGrafo *G, int x);
void outdeg(TGrafo *G, int x);
void libera(TGrafo *G);
void removeA(TGrafo *G, int v, int w);
int ehCaminho(int seq[], int k,TGrafo *G);


// Funcao cliente que utiliza a TAD TGrafo
int main(void){

    TGrafo *g;
    int seq [] = {2,4,1,2,4,1};
    // aloca a estrutura TGrafo e atribui em g
    g = Init(6);
    insereA( g, 0, 2);
    insereA( g, 0, 4);
    insereA( g, 0, 3);
    insereA( g, 1, 2);
    insereA( g, 2, 4);
    insereA( g, 3, 4);
    insereA( g, 3, 5);
    insereA( g, 4, 1);
    insereA( g, 4, 5);
    insereA( g, 5, 1);
    //removeA(g, 3, 5);
    show(g);
    printf("\nresposta: %d", ehCaminho(seq, 5, g));

    //indeg(g, 2); // saida 1
    //outdeg(g, 2); //saida 2

    return 0;
}

//inicializa o grafo
TGrafo * Init( int V ){
    int i;
    TGrafo *grafo = (TGrafo*)calloc( 1, sizeof(TGrafo));
    grafo->V = V;
    grafo->A = 0;

    // cria as entradas para armazenar os inicios das
    // listas de adjacencia
    grafo->adj = (TNo **) calloc( V, sizeof(TNo *));

    return grafo;
}

/*insere aresta (sem ordenação)
void insereA( TGrafo *G, int v, int w){
    TNo *novo; //inicializa novo no
    novo = (TNo *) calloc( 1, sizeof(TNo));
    novo->elem = w; //atribui elemento w
    novo->prox = G->adj[v]; //adiciona na lista v
    G->adj[v] = novo;
    G->A++;
}*/

//insere aresta (ordenada)
void insereA( TGrafo *G, int v, int w){
    TNo *novo, *aux, *ant;

    // andar na lista
    aux = G->adj[v];
    ant = NULL;
    while( aux && aux->elem <= w ){ // aux != NULL
        // testa se o w jah estah inserido na lista de adjacencia
        if( aux->elem == w )
            return;
        ant = aux;
        aux = aux->prox;
    }
    novo = (TNo *) calloc( 1, sizeof(TNo));
    novo->elem = w;
    // lista vazia, insere no inicio
    if( ant == NULL )
      G->adj[v] = novo;
    else
        ant->prox = novo;

    novo->prox = aux;

    G->A++;
}

//insere aresta (ordenada)
void removeA( TGrafo *G, int v, int w){
    TNo *aux, *ant;

    // andar na lista
    aux = G->adj[v];
    ant = aux;
    while( aux && aux->elem < w ){ // aux != NULL
        ant = aux;
        aux = aux->prox;
    }
    // lista vazia, insere no inicio
    if(ant==aux){
      G->adj[v]=G->adj[v]->prox;
      aux=NULL; 
    }
    else{
      ant->prox = aux->prox;
      aux=NULL;
   
      G->A--;
    }
  
}

//exibe o grafo
void show(TGrafo *G){
    int v,w;
    TNo *aux;
    printf("\nGrafo V=%d A=%d", G->V, G->A);
    for(v=0;v<G->V;v++){
        printf("\n%d:",v);
        aux = G->adj[v]; //percorre vértice origem
        while( aux ){ // aux != NULL
            printf(" %d",aux->elem); //percorre lista de vértices destino do vértice origem
            aux = aux->prox;
        }
    }
}

void indeg(TGrafo *G, int x){
    int cont=0;
    int v;
    for(v=0;v<G->V;v++){
        TNo *aux;
        aux = G->adj[v]; //percorre vértice origem
        while( aux ){ // aux != NULL
            if(aux->elem==x){
                cont++;
            }
            aux = aux->prox;
        }
    }
    printf("\nindeg para %d: %d",x,cont);
}

void outdeg(TGrafo *G, int x){
    int cont=0;
    TNo *aux;
    aux = G->adj[x]; //percorre vértice origem
    while( aux ){ // aux != NULL
      cont++;
      aux = aux->prox;
    
    }
    printf("\noutdeg para %d: %d",x,cont);
}

//libera grafo
void libera(TGrafo *G){
  free(G);
}

int ehCaminho(int seq[], int k, TGrafo *G){
    //k eh o comprimento do caminho
    int i,v,w;
    TNo *aux;
    for( i=0; i < k; i++){
        v = seq[i];
        w = seq[i+1];
        // busca o w
        /*aux = G->adj[v];
        while( aux && aux->elem != w )
            aux = aux->prox
        */
        for( aux = G->adj[v]; aux && aux->elem != w; aux = aux->prox );

        //if ( aux == NULL )
        if( !aux )
            return 0;
    }

    return 1;
}

