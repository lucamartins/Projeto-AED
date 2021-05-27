#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>

#include "functions.h"

//
// Funcoes auxiliares
//

void inicializarLista(LISTA* l){
    l->inicio = NULL;
    l->cntID = 0;
}

PONT buscarProxEndLivre(LISTA* l, PONT* ant){
    *ant = NULL;
    PONT atual = l->inicio;

    while(atual != NULL) {
        *ant = atual;
        atual = atual->prox;
    }

    return atual;
}

PONT buscarPeloID(LISTA* l, int ID, PONT* ant){
    *ant = NULL;
    PONT end = l->inicio;

    while((end != NULL) && (end->reg.ID < ID)){
        *ant = end;
        end = end->prox;
    }
    if((end != NULL) && (end->reg.ID == ID)){
        return end;
    }
    return NULL;
}

PONT lerEbuscarNome(LISTA* l, PONT* ant){
    *ant = NULL;
    PONT end = l->inicio;
    
    char nome[60];
    getchar();
    printf("\n# Informe o nome do cliente: ");
    scanf("%[^\n]%*c", nome);

    while(end != NULL){
        if(strcmp(end->reg.nome, nome) == 0) return end;
 
        *ant = end;
        end = end->prox;
    }
    return NULL;
}

void preencherDadosCliente(LISTA* l, PONT i){
    // Variavel de controle para sair do while loop
    int suc;

    // ID
    i->reg.ID = l->cntID+1;
    l->cntID++;

    // Nome
    printf("\n# Nome completo: ");
    scanf("%[^\n]%*c", i->reg.nome);

    // Data de nascimento
    suc = 0;
    while(suc == 0) {
        int dia, mes, ano;

        printf("\n# Data de nascimento\n");
        printf("- Informe o dia (DD): ");
        scanf("%d", &dia);
        printf("- Informe o mes (MM): ");
        scanf("%d", &mes);
        printf("- Informe o ano (AAAA): ");
        scanf("%d", &ano);

        if(dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12 && ano >= 0) {
            suc = 1;
            sprintf(i->reg.dataNasc.dia, "%d", dia);
            sprintf(i->reg.dataNasc.mes, "%d", mes);
            sprintf(i->reg.dataNasc.ano, "%d", ano);
        }
        else printf("*Data invalida! Tente novamente\n");
    }

    // Saldo
    suc = 0;
    while(suc == 0) {
        printf("\n# Digite '1' caso algum valor sera depositado no ato de criacao da conta ou '0' caso contrario: ");
        int ctr;
        scanf("%d", &ctr);

        while(ctr != 0 && ctr != 1) {
            printf("*FALHA: Opcao incorreta. Digite novamente: ");
            scanf("%d", &ctr);
        }

        if(ctr == 0) break;

        printf("- Informe o valor: ");
        double valor;
        scanf("%lf", &valor);

        if(valor >= 0) {
            suc = 1;
            i->reg.saldo = valor;
        }
        else printf("*Valor invalido! Tente novamente.\n");
    }
    
    // Debitos (dividas)
    i->reg.debitos = 0;

    // CPF
    suc = 0;
    getchar();
    while(suc == 0) {
        char cpf[20];
        printf("\n# Informe o CPF (XXX.XXX.XXX-XX): ");
        scanf("%[^\n]%*c", cpf);

        if(strlen(cpf) == 14 && cpf[3] == '.' && cpf[7] == '.' && cpf[11] == '-') {
            suc = 1;
            strcpy(i->reg.cpf, cpf);
        }
        else {
            printf("*CPF invalido. Tente novamente\n");
        }
    }

    // Endereco (CEP)
    suc = 0;
    while(suc == 0) {
        printf("\n# Informe o CEP (XXXXX-XXX): ");
        char cep[20];
        scanf("%[^\n]%*c", cep);

        if(cep[5] == '-' && strlen(cep) == 9) {
            suc = 1;
            strcpy(i->reg.cep, cep);
        }
        else {
            printf("*CEP invalido. Tente novamente\n");
        }
    }

    // Telefone
    printf("\n# Informe um numero de contato com o codigo de area ((DDD)NNNNN-NNNN): ");
    scanf("%[^\n]%*c", i->reg.telefone);
}

PONT encontrarClienteMenu(LISTA* l, PONT* ant){
    printf("1 -- Procurar cliente atrave do nome\n");
    printf("2 -- Procurar cliente atraves do ID\n");

    int opcao;
    printf("\n# Informe a opcao desejada: ");
    scanf("%d", &opcao);

    while(opcao != 1 && opcao != 2) {
        printf("*Opcao invalida. Tente novamente: ");
        scanf("%d", &opcao);
    }
    
    PONT end;

    if(opcao == 1) end = lerEbuscarNome(l, ant);

    else if(opcao == 2){ // Opcao para procurar a conta pelo ID
        int ID;
        printf("\n# Insira o ID do cliente: ");
        scanf("%d", &ID);
        end = buscarPeloID(l, ID, ant);
    }
    
    return end;
}

//
// Funcoes de acesso direto pela main
//

int criarCliente(LISTA* l){
    system("cls");
    printf("= = = = = CRIAR NOVO CLIENTE = = = = =\n");

    PONT ant, i = buscarProxEndLivre(l, &ant);
    i = (PONT) malloc(sizeof(ELEMENTO));

    preencherDadosCliente(l, i);    

    if(ant == NULL) {
        i->prox = l->inicio;
        l->inicio = i;
    }
    else {
        i->prox = ant->prox;
        ant->prox = i;
    }

    printf("\n\n@ Cliente criado com sucesso!\n\n");
    system("pause");

    return i->reg.ID;
}

void exibirClientes(LISTA* l){
    system("cls");
    printf("= = = = = LISTA DE CLIENTES = = = = =\n");

    PONT end = l->inicio;

    if(end == NULL) printf("\n * NAO HA CLIENTES!\n");

    while(end != NULL){
        printf("\n- Codigo ID: %d\n", end->reg.ID);
        printf("- Nome: %s\n", end->reg.nome);
        printf("- CPF: %s\n", end->reg.cpf);
        printf("- Data de Nascimento: %02s/%02s/%04s\n", end->reg.dataNasc.dia, end->reg.dataNasc.mes, end->reg.dataNasc.ano);
        printf("- CEP: %s\n", end->reg.cep);
        printf("- Telefone: %s\n", end->reg.telefone);
        printf("- Saldo atual: R$%.2lf\n", end->reg.saldo);
        printf("- Debitos: R$%.2lf\n", end->reg.debitos);
        printf("\n= = = = = = = = = = = = = = = = = =\n");

        end = end->prox;   
    }

    printf("\n\n@ Lista de clientes gerada com sucesso!\n\n");
    system("pause");
}

void procurarCliente(LISTA* l){
    system("cls");
    printf("= = = = = PROCURAR CLIENTE = = = = =\n\n");

    PONT ant, end = encontrarClienteMenu(l, &ant);

    if(end == NULL) {
        printf("\n\n@ FALHA: Cliente nao encontrado!\n\n");
        system("pause");
        return;
    }

    else {
        printf("\n# Detalhes da conta procurada: \n\n");
        printf("= = = = = = = = = = = = = = = = = =\n\n");
        printf("- Codigo ID: %d\n", end->reg.ID);
        printf("- Nome: %s\n", end->reg.nome);
        printf("- CPF: %s\n", end->reg.cpf);
        printf("- Data de Nascimento: %02s/%02s/%04s\n", end->reg.dataNasc.dia, end->reg.dataNasc.mes, end->reg.dataNasc.ano);
        printf("- CEP: %s\n", end->reg.cep);
        printf("- Telefone: %s\n", end->reg.telefone);
        printf("- Saldo atual: R$%.2lf\n", end->reg.saldo);
        printf("- Debitos: R$%.2lf\n", end->reg.debitos);
        printf("\n= = = = = = = = = = = = = = = = = =\n");
    }

    printf("\n\n");
    system("pause");
}

int inserirDivida(LISTA* l){
    system("cls");
    printf("= = = = = INSERCAO DE DIVIDA = = = = =\n\n");

    PONT ant, end = encontrarClienteMenu(l, &ant);

    if(end == NULL) {
        printf("\n\n@ FALHA: Cliente nao encontrado!\n\n");
        system("pause");
        return 0;
    }

    // Inserir divida
    int ID, suc;
    double dividas;

    suc = 0;
    while(suc == 0){
        printf("\n# Insira o valor da divida: ");
        scanf("%lf", &dividas);

        if(dividas < 0){
            printf("Valor invalido! Tente novamente.\n");
        }
        else{
            end->reg.debitos = end->reg.debitos + dividas;
            suc = 1;
        }
    }

    printf("\n\n@ Divida inserida com suceso!\n\n");
    system("pause");
    return 1;
}

int quitarDividas(LISTA* l){
    system("cls");
    printf("= = = = = QUITACAO DE DIVIDA = = = = =\n\n");

    PONT ant, end = encontrarClienteMenu(l, &ant);

    if(end == NULL) {
        printf("\n\n@ FALHA: Cliente nao encontrado!\n\n");
        system("pause");
        return 0;
    }

    // Pagar divida
    printf("\n\n# # #\n\n\n");
    printf("$ Divida total = R$%.2lf\n", end->reg.debitos);
    printf("1 -- Pagar divida a vista\n");
    printf("2 -- Pagar uma parcela da divida\n");

    int opcao;
    printf("\n# Insira a opcao desejada: ");
    scanf("%d", &opcao);

    while(opcao != 1 && opcao != 2) {
        printf("\n*Opcao invalida. Tente novamente: ");
        scanf("%d", &opcao);
    }

    if(opcao == 1){
        if(end->reg.saldo < end->reg.debitos){
            printf("\n\n@ FALHA: Operacao negada. Saldo insuficiente!\n\n");
            system("pause");
            return 0;
        }

        end->reg.saldo = end->reg.saldo - end->reg.debitos;
        end->reg.debitos = 0;

        printf("\n\n@ Divida quitada com sucesso.\n\n");
        system("pause");
        return 1;
    }

    else if(opcao == 2){
        int parcelas;
        printf("\n# Digite em quantas parcelas voce deseja dividir a divida: ");
        scanf("%d", &parcelas);

        double aux;
        aux = end->reg.debitos / parcelas;

        printf("\n$ Saldo da conta: R$%.2lf\n", end->reg.saldo);
        printf("$ Valor da parcela (R$%.2lf / %d) = R$%.2lf\n", end->reg.debitos, parcelas, aux);

        if(end->reg.saldo < aux){
            printf("\n\n@ FALHA: Operacao negada. Saldo insuficiente!\n\n");
            system("pause");
            return 0;
        }
        end->reg.saldo = end->reg.saldo - aux;
        end->reg.debitos = end->reg.debitos - aux;

        printf("\n\n@ Parcela paga com sucesso!\n\n");
        system("pause");
        return 1;
    }
}

int atualizarDados(LISTA* l){
    system("cls");
    printf("= = = = = ATUALIZAR DADOS DO CLIENTE = = = = =\n\n");

    PONT ant, end = encontrarClienteMenu(l, &ant);

    if(end == NULL) {
        printf("\n\n@ FALHA: Cliente nao encontrado!\n\n");
        system("pause");
        return 0;
    }

    // Atualizar
    int suc;

    printf("\n# # #\n");
    printf("1 -- Atualizar CPF\n");
    printf("2 -- Atualizar data de nascimento\n");
    printf("3 -- Atualizar telefone de contato\n");
    printf("4 -- Atualizar CEP\n");

    int n;
    printf("\n# Insira a opcao desejada: ");
    scanf("%d", &n);

    while(n != 1 && n != 2 && n != 3 && n != 4) {
        printf("*Opcao invalida. Digite novamente: ");
        scanf("%d", &n);
    }

    if(n == 1){ // Atualizando o cpf
        suc = 0;
        getchar();

        while(suc == 0) {
            char cpf[20];
            printf("\n# Informe o CPF (FORMATO XXX.XXX.XXX-XX): ");
            scanf("%[^\n]%*c", cpf);

            if(strlen(cpf) == 14 && cpf[3] == '.' && cpf[7] == '.' && cpf[11] == '-') {
                suc = 1;
                strcpy(end->reg.cpf, cpf);
            }
            else printf("*CPF invalido. Tente novamente\n");
        }
    }

    else if(n == 2){ // Atualizar a data de nascimento
        suc = 0;
        while(suc == 0) {
            int dia, mes, ano;

            printf("\n# Data de nascimento\n");
            printf("Informe o dia (DD): ");
            scanf("%d", &dia);
            printf("Informe o mes (MM): ");
            scanf("%d", &mes);
            printf("Informe o ano (AAAA): ");
            scanf("%d", &ano);

            if(dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12 && ano >= 0) {
                suc = 1;
                sprintf(end->reg.dataNasc.dia, "%d", dia);
                sprintf(end->reg.dataNasc.mes, "%d", mes);
                sprintf(end->reg.dataNasc.ano, "%d", ano);
            }
            else printf("*Data invalida! Tente novamente\n");
        }
    }

    else if(n == 3){ // Atualizar o telefone
        getchar();
        printf("\n# Informe um numero de contato com o codigo de area ((DDD)NNNNN-NNNN): ");
        scanf("%[^\n]%*c", end->reg.telefone);
    }

    else if(n == 4){ // Atualizar o CEP
        suc = 0;
        getchar();
        while(suc == 0) {
            printf("\n# Informe o CEP (FORMATO XXXXX-XXX): ");
            char cep[20];
            scanf("%[^\n]%*c", cep);

            if(cep[5] == '-' && strlen(cep) == 9) {
                suc = 1;
                strcpy(end->reg.cep, cep);
            }
            else printf("*CEP invalido. Tente novamente\n");
        }
    }

    printf("\n\n@ Dados atualizados com sucesso!\n\n");
    system("pause");
    return 1;
}

int removerCliente(LISTA* l){
    system("cls");
    printf("= = = = = REMOVER CLIENTE = = = = =\n\n");

    PONT ant, end = encontrarClienteMenu(l, &ant);

    if(end == NULL) {
        printf("\n\n@ FALHA: Cliente inexistente!\n\n");
        system("pause");
        return 0;
    }

    if(end->reg.saldo > 0 || end->reg.debitos > 0) {
        printf("\n\n@ FALHA: Nao eh possivel excluir conta com saldo ou com debitos abertos.\n\n");
        system("pause");
        return 0;
    }

    if(ant == NULL) l->inicio = end->prox;
    else ant->prox = end->prox;

    free(end);
    printf("\n\n@ Cliente removido com sucesso!\n\n");
    system("pause");
    return 1;
}

int transferencia(LISTA* l){
    system("cls");
    printf("= = = = = TRANSFERENCIA = = = = =\n");

    printf("\n# # # Cliente REMETENTE:\n");
    PONT ant, remetente = encontrarClienteMenu(l, &ant);

    printf("\n\n# # # Cliente DESTINATARIO:\n");
    PONT destinatario = encontrarClienteMenu(l, &ant);

    if(remetente == NULL && destinatario == NULL) {
        printf("\n\n@ FALHA: Ambos clientes nao encontrados!\n\n");
        system("pause");
        return 0;
    }
    else if(remetente == NULL) {
        printf("\n\n@ FALHA: Remetente nao encontrado!\n\n");
        system("pause");
        return 0;
    }
    else if(destinatario == NULL) {
        printf("\n\n@ FALHA: Destinatario nao encontrado!\n\n");
        system("pause");
        return 0;
    }

    double valor;
    printf("\n\n# # # Insira o valor que sera transferido: ");
    scanf("%lf", &valor);

    if(valor > remetente->reg.saldo || valor <= 0){
        printf("\n\n@ FALHA: Saldo insuficiente para realizar transferencia ou valor invalido!\n\n");
        system("pause");
        return 0;
    }

    remetente->reg.saldo = remetente->reg.saldo - valor;
    destinatario->reg.saldo = destinatario->reg.saldo + valor;

    printf("\n\n@ Transferencia realizada com sucesso!\n\n");
    system("pause");
    return 1;
}

int deposito(LISTA* l){
    system("cls");
    printf("= = = = = DEPOSITO = = = = =\n\n");

    PONT ant, end = encontrarClienteMenu(l, &ant);

    if(end == NULL) {
        printf("\n\n@ FALHA: Cliente nao encontrado!\n\n");
        system("pause");
        return 0;
    }

    double valor;
    printf("\n# Insira o valor a ser depositado: ");
    scanf("%lf", &valor);

    while(valor < 0){
        printf("\n*FALHA: Valor negativo!\n");
        printf("\n# Insira novamente o valor a ser depositado: ");
        scanf("%lf", &valor);
    }

    end->reg.saldo = end->reg.saldo + valor;

    printf("\n\n@ Deposito realizado com sucesso!\n\n");
    system("pause");
    return 1;
}

int saque(LISTA* l){
    system("cls");
    printf("= = = = = SAQUE = = = = =\n\n");

    PONT ant, end = encontrarClienteMenu(l, &ant);

    if(end == NULL) {
        printf("\n\n@ FALHA: Cliente nao encontrado!\n\n");
        system("pause");
        return 0;
    }
    
    double valor;
    printf("\n# Insira o valor do saque/pagamento: ");
    scanf("%lf", &valor);

    while(valor < 0){
        printf("FALHA: Valor negativo!\n");
        printf("\n# Insira novamente o valor: ");
        scanf("%lf", &valor);
    }

    if(valor > end->reg.saldo){
        printf("\n\n@ FALHA: Saldo insuficiente!\n\n");
        system("pause");
        return 0;
    }

    end->reg.saldo = end->reg.saldo - valor;

    printf("\n\n@ Saque/pagemnto realizado com sucesso!\n\n");
    system("pause");
    return 1;
}