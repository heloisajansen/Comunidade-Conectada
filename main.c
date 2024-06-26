#include <stdio.h>
#include <stdlib.h>

//Define qntd. máxima de vértices
#define MAXV 1000

//Implementação de um grafo por lista de adjacência, utilizando uma linked list:
typedef struct {
    int adj; //nódulo adjacente ao vértice
    struct node* next; //Ponteiro apontando p/ o próximo vértice
} node; //Nomeia a struct de node

typedef struct {
    node *vertices[MAXV + 1]; //Cada um dos elementos desse vetor aponta p/ um dos vértices do grafo
    int qntdVertices, qntdArestas, grau[MAXV + 1]; //Número de vértices, arestas e o valor de grau de cada vértice.
} grafo; //Nomeia a struct de grafo

//Cria um grafo vazio
void criaGrafo(grafo *g) {
    g->qntdVertices = 0;
    g->qntdArestas = 0;

    for (int i = 1; i <= MAXV; i++) {
        g->grau[i] = 0;
        g->vertices[i] = NULL; //g->vertices[i] precisa do valor NULL nesse caso uma vez que sem nódulos, não há vértices, ou seja, não há casos de adjacência
    }
}

//Insere cada relação no grafo
void insereAresta(grafo *g, int x, int y) {
    node *tempPtr = malloc(sizeof(node)); //Aloca dinaminacamente um ponteiro com o tamanho de bytes de node
    tempPtr->adj = y;
    tempPtr->next = g->vertices[x];
    g->vertices[x] = tempPtr;
    g->grau[x]++; //Incrementa o grau do vértice x
    g->qntdArestas++; //Incrementa a quantidade de arestas
}

//Função p/ receber os elementos que irão compor o grafo:
void elementosGrafo(grafo *g) {
    int n, x, y; //Número de arestas, primeiro vértice e o vértice que está conectado a ele
    char entrada[100]; //A string entrada será utilizada p/ que seja possível ler os input na formação adequada

    FILE* fptr = fopen("arquivo.txt", "r"); //Abre o arquivo no modo de leitura
    if (fptr == NULL){ //Checa se foi possível abrir o arquivo
        printf("Erro: Arquivo inválido");
        exit(1); //Termina de rodar o código se a leitura não puder ser concluída
    }

    criaGrafo(g); //Cria um grafo vázio antes de inserir os elementos

    if (fscanf(fptr, "%d  %d", &(g->qntdVertices), &n) != 2){ //leitura da quantidade de vertices e arestas
        printf("Erro: Não foi possível ler o número de vértices e arestas");
        exit(1);
    }

    for (int i = 1; i <= n; i++){
        if(fscanf(fptr, "%s %d %d", entrada, &x, &y) != 3){ //Leitura dos vértices relacionados entre si
            printf("Erro: Não foi possível ler os vértices");
            exit(1);
        }
        insereAresta(g, x, y);
        insereAresta(g, y, x);// Como o grafo é não direcionado, ao criar uma aresta de x p/ y, é necessário também criar uma aresta de y p/ x
    }
    fclose(fptr); //Fecha o arquivo
}

//Função mostraGrafo utilizada p/ visualização da lista de adjacência:
/* 
void mostraGrafo(grafo *g) {
    node *tempPtr;

    for (int i = 1; i <= g->qntdVertices; i++) {
        printf("%d:", i); // Cabeça do vértice
        tempPtr = g->vertices[i];
        while (tempPtr != NULL) {
            printf(" %d", tempPtr->adj);
            tempPtr = tempPtr->next;
        } //Enquanto há vértices a serem mostrados, o nódulo adjacente é exibido e o ponteiro temporário aponta para o próximo vértice.
        printf("\n");
    }
}
*/

int ehVizinho(int x, int y, grafo *g) {
    //inicializa um ponteiro temporário tempPtr para o início da lista de adjacência do vértice x.
    node *tempPtr = g->vertices[ x];
    // Percorre a lista de adjacência enquanto tempPtr não for NULL.Se encontrar um nó cujo campo adj é igual a v, retorna 1 indicando que x e y são vizinhos. Avança para o próximo nó na lista de adjacência.
    while (tempPtr != NULL) {
        if (tempPtr->adj == y) 
            return 1;
        tempPtr = tempPtr->next;
    }

    return 0;
}

// R[]: Conjunto dos vértices que estão no clique atual. 
// P[]: Conjunto dos vértices que podem ser adicionados ao clique.
// X[]: Conjunto dos vértices que já foram considerados e não podem ser adicionados ao clique.
void Maximal(int R[], int P[], int X[], int tamanho_R, int tamanho_P, int tamanho_X, grafo *g, int *max_clique_size, int *max_clique[]) {
    //condição base - Se ambos os conjuntos P e X estiverem vazios, então R é um clique máximo. Os elementos de R são impressos e a função retorna.
    if (tamanho_P == 0 && tamanho_X == 0) {
        if (tamanho_R > *max_clique_size) {
            *max_clique_size = tamanho_R;
            for (int i = 0; i < tamanho_R; i++) {
                (*max_clique)[i] = R[i];
            }
        }
        return;
    }
    //Uma cópia do conjunto P é criada para evitar a modificação do conjunto original durante a iteração.
    int P_copy[MAXV + 1];
    for (int i = 0; i < tamanho_P; i++) {
        P_copy[i] = P[i];
    }

    //Intera sobre P
    for (int i = 0; i < tamanho_P; i++) {
        int v = P_copy[i];

    //Para cada vértice v em P_copy, verifica se v é vizinho ao último elemento de R ou se R está vazio. Se a condição é satisfeita, v é adicionado a R.
        if (ehVizinho(v, R[tamanho_R - 1], g) || tamanho_R == 0) {
            R[tamanho_R] = v;
            int Novo_P[MAXV + 1], Novo_X[MAXV + 1];
            int Novo_P_tamanho = 0, Novo_X_tamanho = 0;
//Novos conjuntos Novo_P e Novo_X são criados contendo apenas os vizinhos de v.
            for (int j = 0; j < tamanho_P; j++) {
                if (ehVizinho(v, P[j], g)) {
                    Novo_P[Novo_P_tamanho++] = P[j];
                }
            }

            for (int j = 0; j < tamanho_X; j++) {
                if (ehVizinho(v, X[j], g)) {
                    Novo_X[Novo_X_tamanho++] = X[j];
                }
            }
//A função BronKerbosch é chamada recursivamente com os novos conjuntos R, Novo_P, Novo_X, e seus respectivos tamanhos atualizados.
            Maximal(R, Novo_P, Novo_X, tamanho_R + 1, Novo_P_tamanho, Novo_X_tamanho, g, max_clique_size, max_clique);

            //Após a chamada recursiva, v é removido de P (marcado como -1) e adicionado a X.
            P[i] = -1;// Marca v como removido de P
            X[tamanho_X++] = v;// Adiciona v a X
        }
    }
}

// Função principal para encontrar todos os cliques máximos no grafo
void encontrarCliques(grafo *g, int *max_clique_size, int **max_clique) {
    int R[MAXV + 1], P[MAXV + 1], X[MAXV + 1];
    int p_size = 0, x_size = 0;
    // Inicializa o conjunto P com todos os vértices do grafo
    for (int i = 1; i <= g->qntdVertices; i++) {
        P[p_size++] = i; // Adiciona cada vértice do grafo ao conjunto P
    }

    Maximal(R, P, X, 0, p_size, x_size, g, max_clique_size, max_clique);
}

// Função auxiliar para calcular o tamanho de um clique
int tamanhoClique(int clique[], int tamanho) {
    int count;
    for (int i = 0; i < tamanho; i++) {
        if (clique[i] != -1) {
            count+=1;
        }
    }
    return count;
}

int main() {
    
    grafo g;
    elementosGrafo(&g); //P/ inserir todos os elementos no grafo a partir da leitura de um arquivo
    //mostraGrafo(&g); //Chamada da função mostraGrafo p/ visualização do grafo

    int max_clique_size = 0;
    int *max_clique = malloc((MAXV + 1) * sizeof(int));
    for (int i = 0; i <= MAXV; i++) {
        max_clique[i] = -1;
    }

    encontrarCliques(&g, &max_clique_size, &max_clique);// Encontra todos os cliques maximais no grafo
    printf("A resposta está salva no arquivo txt: resultado.txt\n");

    //Mostrando e salvando o resultado:
    
    FILE *resultado;
    
    resultado = fopen("resultado.txt","w");
    // char string[25];
    
    fprintf(resultado,"Tamanho do maior clique encontrado: %d\n",max_clique_size); 

    //Imprimindo os resultados:
    printf("Tamanho do maior clique encontrado: %d\n", max_clique_size);
    printf("Vertices do maior clique: ");
    for (int i = 0; i < MAXV + 1; i++) {
        if (max_clique[i] != -1) {
            printf("%d ", max_clique[i]);
            
            fprintf(resultado, "%d ", max_clique[i]);
        }
    }

    free(max_clique);// Libera a memória alocada para o vetor de clique máximo

    return 0;
}
