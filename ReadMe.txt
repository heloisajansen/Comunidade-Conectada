Comunidade conectada

Este projeto consiste em um algoritmo para encontrar a maior comunidade conectada em uma rede social. Entede-se "comunidade conectada" por aquele grupo, dentro de uma rede, conectado por laços de amizade diretos. Assim, o algoritmo procura os cliques máximos no grafo, ou seja, ele procura todos os vertíces que estão diretamente conectados cada um a todos os outros, não sendo possível adicionar mais vertíces a esse conjunto sem violar a propriedade de que todos os vertíces estão conectados. 

Construção do Código:

A primeira etapa consiste na construção de um grafo por lista de adjacência, utilizando-se de duas structs: "node" e "grafo". A struct "grafo" declara um ponteiro para um vetor de vértices, a quantidade de vértices, arestas e o grau de cada vértice. A struct "node" define um nódulo adjacente e um ponteiro para o próximo vértice da lista. Primeiramente, cria-se uma função para inicializar um grafo vazio. Em seguida, outra função insere os dados necessários, lidos a partir de um arquivo na função elementosGrafo.

Posteriormente, utiliza-se do Algoritmo de Bron-Kerbosch para encontrar o maior grupo de pessoas conectadas, usando de elementos  de:
R[]: Conjunto dos vértices que estão no clique atual. 
P[]: Conjunto dos vértices que podem ser adicionados ao clique.
X[]: Conjunto dos vértices que já foram considerados e não podem ser adicionados ao clique.
Além do tamanho de cada conjunto e os ponteiros do grafo e do tamanho do maior clique encontrado

Durante esse processo, BronKerbosch utiliza a função auxiliar tamanhoClique para determinar o tamanho de cada clique encontrado e atualizar o maior clique "max_clique" e seu tamanho "max_clique_size" conforme necessário.

Como usar?

Ele lerá o arquivo de texto "arquivo.txt", na primeira linha dele haverá o número de vertíces e o número de arestas respectivamente. Nas linhas posteriores terão os pares de vértice que são conectados por uma aresta.

Execute o programa e ele lerá o arquivo, construirá o grafo e procurará os cliques máximos.

A solução será exibida no console e salvo no arquivo chamado "resultado.txt"

Feito por:
Álvaro Brandão Raposo
Carlos André Almeida Medeiros
Heloísa Jansen Ferreira Ribeiro 