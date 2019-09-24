/*
GRAFO REPRESENTADO POR MATRIZ EM C
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
int ehCaminho(int seq[], int k, TGrafo *G);
void BuscaProf(TGrafo *G, int v, int * visitado);
void Busca( TGrafo * G);


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
    //printf("\nBusca em Profundidade: ");
    //Busca(g);
    printf("\nExiste caminho de 1 ateh 0 ?\n");
    int *visitado = (int*)calloc(g->V, sizeof(int));
    BuscaProf(g, 1, visitado);
    if(visitado[0])
        printf("\nSIM");
    else
        printf("\nNAO");
     // libera a memoria do vetor visitado
    free(visitado);

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

//remove aresta
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

int ehCaminho(int seq[], int k, TGrafo *G){
    //k eh o comprimento do caminho
    int i,v,w;
    for( i=0; i < k; i++){
        v = seq[i];
        w = seq[i+1];
        // busca o w
        /*aux = G->adj[v];
        while( aux && aux->elem != w )
            aux = aux->prox
        */
        if(G->adj[v][w]==0){
          return 0;
        }
  
    }

    return 1;
}

void Busca( TGrafo * G){
    //para Cada vertice v de G faca
    //marque v como nao visitado
    //calloc aloca e inicializa com 0
    int *visitado = (int*)calloc(G->V, sizeof(int));
    int v;
    // para Cada vertice v de G faca
    for(v=0; v <G->V; v++)
        // se v nao foi visitado entao
        //if( visitado[v]== 0)
        if( !visitado[v])
            //Busca-prof( G, v)
            BuscaProf( G, v, visitado );
    // libera a memoria do vetor visitado
    free(visitado);
}

void BuscaProf(TGrafo *G, int v, int * visitado){
    // marque v como visitado
    visitado[v]=1;
	  //imprime v
	  printf("%d ",v);
    //para Cada vertice w adjacente a v faca
    for(int t=0; t<G->V; t++){
      if(!visitado[G->adj[v][t]]){
        BuscaProf(G, G->adj[v][t], visitado);
      }
  }
}
