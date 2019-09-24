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
	TNo **adj; //listas de adjac�ncia
}TGrafo;

TGrafo * Init( int V );
void insereA( TGrafo *G, int v, int w);
void show(TGrafo *G);
/*
Falta implementar
void removeA(TGrafo *G, int v, int w);
void libera(TGrafo *G);
*/

// Funcao cliente que utiliza a TAD TGrafo
int main(void){

    TGrafo *g;

    // aloca a estrutura TGrafo e atribui em g
    g = Init(4);
    insereA( g, 0, 1);
    insereA( g, 0, 2);
    insereA( g, 2, 1);
    insereA( g, 2, 3);
    insereA( g, 1, 3);
    insereA( g, 0, 3);
    show(g);

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

//insere aresta
void insereA( TGrafo *G, int v, int w){
    TNo *novo; //inicializa novo no
    novo = (TNo *) calloc( 1, sizeof(TNo));
    novo->elem = w; //atribui elemento w
    novo->prox = G->adj[v]; //adiciona na lista v
    G->adj[v] = novo;
    G->A++;
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