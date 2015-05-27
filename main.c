#include <stdio.h>
#include <string.h>
#include "prim.h"

int main(int argc, char **argv) {
	Prim prim1;
	char arquivo_parametro[64]; // tamanho maximo do nome do arquivo
	
	if(argc <= 1){
		printf("\n\nUtilizacao:\nPara utilizar esse programa voce deve digitar o nome do arquivo");
		printf(" como PARAMETRO.\nEXEMPLO\n./prim teste.txt\nteste.txt eh o arquivo que voce deseja carregar!\n\n\n");
		return 0; // nao possui o arquivo para leitura
	}

	strcpy(arquivo_parametro, argv[1]);

	// inicializa prim com no maximo 200 vertices
	inicializar_prim(&prim1, arquivo_parametro, 200);

	// calcula o custo minimo
	calcular_custo_minimo(&prim1);

	// salva informacoes no arquivo "saida.txt"
	gerar_saida(&prim1);

	// libera grafo da memoria
	liberar_grafo(&prim1);

	return 0;
}