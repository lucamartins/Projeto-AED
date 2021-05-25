//
// main driver program
//

#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

void exibirMenu() {
    system("cls");
    
    printf("-1 -- Encerrar programa\n");
    printf("1 -- Criar novo cliente\n");
    printf("2 -- Exibir dados de todos os clientes\n");
    printf("3 -- Exibir dados de um cliente\n");
    printf("4 -- Atualizar dados de um cliente\n");
    printf("5 -- Inserir divida\n");
    printf("6 -- Quitar divida\n");
    printf("7 -- Remover um cliente\n\n");

    printf("Digite a opcao desejada: ");
}


int main() {
    LISTA l;
    inicializarLista(&l);

    exibirMenu();
    int op;
    scanf("%d", &op);
    getchar();

    while(op != -1) {
        if(op == 1) criarCliente(&l);
        else if(op == 2) exibirClientes(&l);
        else if(op == 3) exibirConta(&l);
        else if(op == 4) atualizarDados(&l);
        else if(op == 5) inserirDividas(&l);
        else if(op == 6) quitarDividas(&l);
        else if(op == 7) removerCliente(&l);

        exibirMenu();
        scanf("%d", &op);
        getchar();
    }


    return 0;
}