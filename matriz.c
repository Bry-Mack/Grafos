/*
Implementa uma estrutura para armazenar um grafo utilizando matriz de adjacencia com linhas e colunas indexadas por vertices
*/

#include <stdio.h>
#include <stdlib.h>

// TAD - Tipo Abstrato de Dados para representar um grafo.
typedef struct{
	int V; // quantidade de vertices
	int A; // quantidade de arestas
	int **adj; //matriz de adjacencia
}TGrafo;

TGrafo * Init( int V );
void insereA( TGrafo *G, int v, int w);
void removeA( TGrafo *G, int v, int w);
void show(TGrafo *G);
void indeg(TGrafo *G, int x);
void outdeg(TGrafo *G, int x);
void libera(TGrafo *G);

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
    removeA( g, 1, 3);
    show(g);
    indeg(g, 0);
    indeg(g,1);
    indeg(g,2);
    indeg(g,3);
    outdeg(g, 0);
    outdeg(g,1);
    outdeg(g,2);
    outdeg(g,3);
    libera(g);
    return 0;
}

//inicia o grafo
TGrafo * Init( int V ){
    int i;
    TGrafo *grafo = (TGrafo*)calloc( 1, sizeof(TGrafo));
    grafo->V = V;
    grafo->A = 0;

    // cria a matriz
    // aloca vetor que ira reprentar as linhas da matriz
    grafo->adj = (int **) calloc( V, sizeof(int *));
    for( i=0; i < V; i++)
        grafo->adj[i] = (int *) calloc( V, sizeof(int));

    return grafo;
}

//insere aresta
void insereA( TGrafo *G, int v, int w){
    // testa se nao existe aresta
    if( !G->adj[v][w]){
        G->adj[v][w]=1; //cria aresta
        G->A++;//atualiza a quantidade de arestas
    }
}

//reomve aresta
void removeA( TGrafo *G, int v, int w){
    // testa se existe aresta
    if(G->adj[v][w]){
        G->adj[v][w]=0; //cria aresta
        G->A--;//atualiza a quantidade de arestas
    }
}

//exibe o grafo
void show(TGrafo *G){
    int v,w;
    printf("\nGrafo V=%d A=%d", G->V, G->A);
    for(v = 0; v < G->V; v++){
        printf("\n%d:",v);
        for(w = 0; w < G->V; w++)
            if(G->adj[v][w])
                printf(" %d",w);

    }
}

//retorna grau de entrada de um vertice x
void indeg(TGrafo *G, int x){
    int cont = 0;
    int v,w;
    for(v = 0;v < G->V; v++){
      if(G->adj[v][x] == 1){
                cont++;
      }
    }
    printf("\nindeg para %d: %d",x,cont);
}

//retorna grau de saída de um vertice x
void outdeg(TGrafo *G, int x){
    int cont = 0;
    int w;
    for(w = 0;w < G->V; w++){
        if (G->adj[x][w]==1){
                cont++;
        }
    }
    printf("\noutdeg para %d: %d",x,cont);
}

//libera grafo
void libera(TGrafo *G){
  free(G);
}
