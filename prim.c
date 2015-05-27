#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prim.h"

void inicializar_prim(Prim *prim, char *file, int qtd_max_vertices) {
	int i, m, n, peso;

	strcpy(prim->nome_arquivo, file);
	strcpy(prim->arquivo_saida, "saida.txt");
	FILE *arquivo;
	arquivo = fopen(prim->nome_arquivo, "r");
	prim->max_vertices = qtd_max_vertices;
	prim->infinito = 9999; // valor que significa infinito
	
	if(arquivo == NULL){
		printf("Erro! O arquivo nao foi encontrado!\n");
		exit(0);
	}
	
	// verifica se o arquivo esta vazio
	if(verificar_arquivo_vazio(prim) == 0) {
		printf("Erro! O arquivo %s esta vazio!\n", prim->nome_arquivo);
		exit(0);
	}

	// carrega quantidade de vertices e arestas
	for(i = 0; i < 2; i++) {
		if(i == 0) {
			fscanf(arquivo, "%d", &(prim->vertices));
		} else {
			fscanf(arquivo, "%d", &(prim->arestas));
		}
	}
	
	// verifica se existem vertices
	if(prim->vertices == 0) {
		printf("Erro! Nao existem vertices!\n");
		exit(0);
	}

	alocar_grafo(prim);

	for(i = 2; i < (prim->arestas + 2); i++) {
		fscanf(arquivo, "%d %d %d", &m, &n, &peso);
		if(peso < 0) {
			printf("Erro! Nao pode existem peso negativo!\n");
			exit(0);
		}
		if(m >= prim->vertices || m < 0) {
			printf("Erro! O vertice %d nao existe!\n", m);
			exit(0);
		}
		if(n >= prim->vertices || n < 0) {
			printf("Erro! O vertice %d nao existe!\n", n);
			exit(0);
		}

		prim->grafo[m][n] = peso;
		prim->grafo[n][m] = peso;
	}

	fclose(arquivo);
}

void alocar_grafo(Prim *prim) {
	int i, j;
	if(prim->vertices > prim->max_vertices) {
		printf("Erro! Impossivel alocar um grafo com mais de %d vertices!\n", prim->max_vertices);
		exit(0);
	}

	// alocar linhas
	prim->grafo = (int**)malloc(sizeof(int*) * prim->vertices);
	if(prim->grafo == NULL) {
		printf("Erro ao alocar grafo! Memoria insuficiente!\n");
		exit(0);
	}

	// alocar colunas
	for(i = 0; i < prim->vertices; i++) {
		prim->grafo[i] = (int*)malloc(sizeof(int) * prim->vertices);
		if(prim->grafo[i] == NULL) {
			printf("Erro ao alocar grafo! Memoria insuficiente!\n");
			exit(0);
		}
	}

	for(i = 0; i < prim->vertices; i++) {
		for(j = 0; j < prim->vertices; j++) {
			prim->grafo[i][j] = prim->infinito;
		}
	}

}

void liberar_grafo(Prim *prim) {
	int i;
	if(prim->grafo == NULL) {
		printf("Erro! Grafo nao existe!\n");
		exit(0);
	}
	for(i = 0; i < prim->vertices; i++) {
		free(prim->grafo[i]);
	}
	free(prim->grafo);
}

void calcular_custo_minimo(Prim *prim) {
	mostrar_custo_minimo(prim);
	mostrar_ordem_vertices(prim);
}

void mostrar_custo_minimo(Prim *prim) {
	int i, j;
	int visitados[prim->vertices];
	int minimo = prim->infinito;
	int u = 0, v = 0, total = 0;
	int esta_rodando = 1;

	for (v = 0; v < prim->vertices; v++)
		visitados[v] = -1;

	visitados[0] = 0;
	while (esta_rodando != 0) {
	   	minimo = prim->infinito;
	   	for (i = 0; i < prim->vertices; i++) 
	       	if (visitados[i] != -1) 
	          	for (j = 0; j < prim->vertices; j++)
	           		if (visitados[j] == -1 && minimo > prim->grafo[i][j]) {
	               		minimo = prim->grafo[i][j];
	               		u = i;
	               		v = j;
	           		}
	   	
	   	if (minimo == prim->infinito) {
	   		esta_rodando = 0; // fim do laco
	   		break; // sai do laco
	   	}

	   	visitados[v] = u;
	   	total+= minimo;
	}
	prim->custo_minimo = total;
	printf("%d\n", prim->custo_minimo);
}

void mostrar_ordem_vertices(Prim *prim) {
	int i, j;
	int visitados[prim->vertices];
	int minimo = prim->infinito;
	int u = 0, v = 0;
	int esta_rodando = 1;

	for (v = 0; v < prim->vertices; v++)
		visitados[v] = -1;

	visitados[0] = 0;
	while (esta_rodando != 0) {
	   	minimo = prim->infinito;
	   	for (i = 0; i < prim->vertices; i++) 
	       	if (visitados[i] != -1) 
	          	for (j = 0; j < prim->vertices; j++)
	           		if (visitados[j] == -1 && minimo > prim->grafo[i][j]) {
	               		minimo = prim->grafo[i][j];
	               		u = i;
	               		v = j;
	           		}
	   	
	   	if (minimo == prim->infinito) {
	   		esta_rodando = 0; // fim do laco
	   		break; // sai do laco
	   	}

	   	visitados[v] = u;
	   	printf("(%d, %d) ", u, v);
	}
	printf("\n");
}

void gerar_saida(Prim *prim) {
	FILE *arquivo;
	arquivo = fopen(prim->arquivo_saida, "a");
	fprintf(arquivo, "%s: %d\n", prim->nome_arquivo, prim->custo_minimo); // salva informacoes no arquivo prim->arquivo_saida
	fclose(arquivo);
}

int verificar_arquivo_vazio(Prim *prim) {
	FILE *arquivo = fopen(prim->nome_arquivo, "r");
	int c, vazio = 1;
	int qtd = 0;
	  
	while((c = fgetc(arquivo)) != EOF){
		vazio = 0;
	    if(c == '\n')
	    	qtd++;
	}
	
	if(vazio == 0)
		qtd++;

	return qtd;
}