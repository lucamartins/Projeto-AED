//
// main driver program
//

#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

void exibirMenu() {
    system("cls");
    
    printf("= = = = = MENU = = = = =\n\n");
    printf("1 -- Criar novo cliente\n");
    printf("2 -- Gerar lista de clientes\n");
    printf("3 -- Procurar por um cliente\n");
    printf("4 -- Atualizar dados de um cliente\n");
    printf("5 -- Remover um cliente\n");
    printf("6 -- Inserir divida\n");
    printf("7 -- Quitar divida\n");
    printf("8 -- Transferir\n");
    printf("9 -- Deposito\n");
    printf("10 -- Saque/Pagamento\n");
    printf("-1 -- Encerrar programa\n\n");

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
        else if(op == 3) procurarCliente(&l);
        else if(op == 4) atualizarDados(&l);
        else if(op == 5) removerCliente(&l);
        else if(op == 6) inserirDivida(&l);
        else if(op == 7) quitarDividas(&l);
        else if(op == 8) transferencia(&l);
        else if(op == 9) deposito(&l);
        else if(op == 10) saque(&l);

        exibirMenu();
        scanf("%d", &op);
        getchar();
    }

    return 0;
}