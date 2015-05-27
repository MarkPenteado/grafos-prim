#ifndef PRIM_C
#define PRIM_C

struct prim {
	char nome_arquivo[64];
	int vertices;
	int arestas;
	int **grafo; // grafo com ate max_vertices quantidades de vertices
	int max_vertices;
	int infinito;
	int custo_minimo; // custo minimo do grafo
	char arquivo_saida[64]; // armazena arquivo de saida
};

typedef struct prim Prim;

/* Funcao qual ira inicializar a matriz de acordo com os parametros
 * de entrada dados pelo usuário. 
 */
void inicializar_prim(Prim *prim, char *file, int qtd_max_vertices);

/* Funcao qual ira alocar o grafo. */
void alocar_grafo(Prim *prim);

/* Funcao qual ira liberar o grafo. */
void liberar_grafo(Prim *prim);

/* Funcao qual ira fazer o calculo do custo minimo no grafo. */
void calcular_custo_minimo(Prim *prim);

/* Funcao qual ira calcuar o custo minimo no grafo de acordo com o
 * algoritmo de Prim. 
 */
void mostrar_custo_minimo(Prim *prim);

/* Funcao qual ira mostrar a ordem dos vertices, em outras palavras,
 * ira montar a "arvore geradora de custo minimo" mostrando os 
 * conjuntos de vertices. 
 */
void mostrar_ordem_vertices(Prim *prim);

/* Funcao qual ira salvar no arquivo de texto ".txt" os dados
 * armazenados na struct.
 */
void gerar_saida(Prim *prim);

/* Funcao qual ira verificar se o arquivo ".txt" carregado esta vazio */
int verificar_arquivo_vazio(Prim *prim);

#endif // PRIM_C