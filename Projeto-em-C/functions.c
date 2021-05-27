#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>

#include "functions.h"

void inicializarLista(LISTA* l) {
    l->inicio = NULL;
    l->cntID = 0;
}

PONT buscarProxEndLivre(LISTA* l, PONT* ant) {
    *ant = NULL;
    PONT atual = l->inicio;

    while(atual != NULL) {
        *ant = atual;
        atual = atual->prox;
    }

    return atual;
}

int criarCliente(LISTA* l) {
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

    printf("Cliente criado com sucesso!\n");
    system("pause");

    return i->reg.ID;
}

void preencherDadosCliente(LISTA* l, PONT i) {
    int suc;

    // ID
    i->reg.ID = l->cntID+1;
    l->cntID++;

    // Nome
    printf("Informe o seu nome completo: ");
    scanf("%[^\n]%*c", i->reg.nome);

    // Data de nascimento
    printf("Digite a sua data de nascimento (FORMATO DD/MM/AAAA): ");
    suc = 0;
    while(suc == 0) {
        int dia, mes, ano;
        char barra1, barra2;
        scanf("%d %c %d %c %d", &dia, &barra1, &mes, &barra2, &ano);
        if(dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12 && ano >= 0 && barra1 == '/' && barra2 == '/') {
            suc = 1;
            i->reg.dataNasc.dia = dia;
            i->reg.dataNasc.mes = mes;
            i->reg.dataNasc.ano = ano;
        }
        else {
            printf("Data invalida. Tente novamente\n");
        }
    }

    // Saldo
    suc = 0;
    while(suc == 0) {
        printf("Informe o valor, a partir de 0, que sera depositado no ato de criacao da conta: ");
        double valor;
        scanf("%lf", &valor);

        if(valor >= 0) {
            suc = 1;
            i->reg.saldo = valor;
        }
        else {
            printf("Valor invalido. Tente novamente\n");
        }
    }
    
    // Debitos
    i->reg.debitos = 0;

    // CPF
    suc = 0;
    while(suc == 0) {
        char cpf[20];
        printf("Informe o CPF (FORMATO XXX.XXX.XXX-XX): ");
        getchar();
        scanf("%[^\n]%*c", cpf);

        if(strlen(cpf) == 14 && cpf[3] == '.' && cpf[7] == '.' && cpf[11] == '-') {
            suc = 1;
            strcpy(i->reg.cpf, cpf);
        }
        else {
            printf("CPF invalido. Tente novamente\n");
        }
    }

    // Endereco (CEP)
    suc = 0;
    while(suc == 0) {
        printf("Informe o CEP (FORMATO XXXXX-XXX): ");
        char cep[20];
        scanf("%[^\n]%*c", cep);

        if(cep[5] == '-' && strlen(cep) == 9) {
            suc = 1;
            strcpy(i->reg.cep, cep);
        }
        else {
            printf("CEP invalido. Tente novamente\n");
        }
    }

    // Telefone
    printf("Informe um numero de contato com o codigo de area: ");
    scanf("%[^\n]%*c", i->reg.telefone);
}

void exibirClientes(LISTA* l){
    PONT end = l->inicio;

    while(end != NULL){
        printf("=================================\n");
        printf("Codigo de ID: %d\n", end->reg.ID);
        printf("Nome: %s\n", end->reg.nome);
        printf("CPF: %s\n", end->reg.cpf);
        printf("Data de Nascimento: %d/%d/%d\n", end->reg.dataNasc.dia, end->reg.dataNasc.mes, end->reg.dataNasc.ano);
        printf("CEP: %s\n", end->reg.cep);
        printf("Telefone: %s\n", end->reg.telefone);
        printf("Saldo atual: R$%.2lf\n", end->reg.saldo);
        printf("Debitos: R$%.2lf\n", end->reg.debitos);
        printf("\n\n");

        end = end->prox;   
    }

    printf("=================================\n\n");
    system("pause");
}

void exibirConta(LISTA* l){
    printf("1 - Nome\n");
    printf("2 - ID\n");
    
    printf("Digite como deseja acessar a conta: ");
    int opcao;
    scanf("%d", &opcao);

    while(opcao != 1 && opcao != 2) {
        printf("Opcao invalida. Tente novamente: ");
        scanf("%d", &opcao);
    }
    
    if(opcao == 1){ // Opcao para procurar a conta pelo nome
        PONT ant, end = buscarNome(l, &ant);
        
        if(end == NULL){
            printf("Erro! Cliente nao existente.\n");
        }
        else{
            printf("Detalhes da conta desejada: \n\n");
            printf("Codigo de ID: %d\n", end->reg.ID);
            printf("Nome: %s\n", end->reg.nome);
            printf("CPF: %s\n", end->reg.cpf);
            printf("Data de Nascimento: %d/%d/%d\n", end->reg.dataNasc.dia, end->reg.dataNasc.mes, end->reg.dataNasc.ano);
            printf("CEP: %s\n", end->reg.cep);
            printf("Telefone: %s\n", end->reg.telefone);
            printf("Saldo atual: R$%.2lf\n", end->reg.saldo);
            printf("Debitos: R$%.2lf\n\n", end->reg.debitos);
        }
    }
    else if(opcao == 2){ // Opcao para procurar a conta pelo ID
        int ID;
        printf("Insira o ID do cliente: ");
        scanf("%d", &ID);
        PONT ant, end = buscarID(l, ID, &ant);
        
        if(end == NULL){
            printf("ERRO! Cliente nao existente.\n");
        }
        else{
            printf("Detalhes da conta desejada: \n\n");
            printf("Codigo de ID: %d\n", end->reg.ID);
            printf("Nome: %s\n", end->reg.nome);
            printf("CPF: %s \n", end->reg.cpf);
            printf("Data de Nascimento: %d/%d/%d\n", end->reg.dataNasc.dia, end->reg.dataNasc.mes, end->reg.dataNasc.ano);
            printf("CEP: %s \n", end->reg.cep);
            printf("Telefone: %s \n", end->reg.telefone);
            printf("Saldo atual: R$%.2lf\n", end->reg.saldo);
            printf("Debitos: R$%.2lf\n\n", end->reg.debitos);
        }
    }

    system("pause");
}

PONT buscarID(LISTA* l, int ID, PONT* ant){
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

PONT buscarNome(LISTA* l, PONT* ant){
    *ant = NULL;
    PONT end = l->inicio;
    
    char nome[60];
    getchar();
    printf("Insira o nome do cliente: ");
    scanf("%[^\n]%*c", nome);

    while(end != NULL){
        if(strcmp(end->reg.nome, nome) == 0) return end;
 
        *ant = end;
        end = end->prox;
    }
    return NULL;
}

PONT encontrarClienteMenu(LISTA* l, PONT* ant) {
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

    if(opcao == 1) end = buscarNome(l, ant);

    else if(opcao == 2){ // Opcao para procurar a conta pelo ID
        int ID;
        printf("\n# Insira o ID do cliente: ");
        scanf("%d", &ID);
        end = buscarID(l, ID, ant);
    }
    
    return end;
}

int inserirDividas(LISTA* l){
    int ID, suc;
    double dividas;

    printf("Insira o ID do cliente: ");
    scanf("%d", &ID);

    PONT ant, end = buscarID(l, ID, &ant);

    if(end == NULL){
        printf("Cliente nao existente!\n");
        system("pause");
        return 0;
    }

    suc = 0;
    while(suc == 0){
        printf("Insira o valor de dividas (numero positivo): ");
        scanf("%lf", &dividas);

        if(dividas < 0){
            printf("Valor invalido! Tente novamente.\n");
        }
        else{
            end->reg.debitos = end->reg.debitos + dividas;
            suc = 1;
        }
    }

    printf("Divida inserida com suceso!\n");
    system("pause");
    return 1;
}

int quitarDividas(LISTA* l) {
    int ID, opcao;

    printf("Insira o ID do cliente: ");
    scanf("%d", &ID);

    PONT ant, end = buscarID(l, ID, &ant);

    if(end == NULL){
        printf("ERRO! Cliente nao existente.\n");
        system("pause");
        return 0;
    }

    printf("1 -- Pagar tudo a vista\n");
    printf("2 -- Pagar uma parcela\n");
    printf("Digite qual opcao desejada para quitar a sua divida: ");
    scanf("%d", &opcao);

    while(opcao != 1 && opcao != 2) {
        printf("Opcao invalida. Tente novamente: ");
        scanf("%d", &opcao);
    }

    while(1){
        if(opcao == 1){
            if(end->reg.saldo < end->reg.debitos){
                printf("Operacao negada! Saldo insuficiente.\n");
                system("pause");
                return 0;
            }

            end->reg.saldo = end->reg.saldo - end->reg.debitos;
            end->reg.debitos = 0;

            printf("Divida quitada com sucesso.\n");
            system("pause");
            return 1;
        }
        else if(opcao == 2){
            int parcelas;
            printf("Digite em quantas parcelas voce deseja dividir a divida: ");
            scanf("%d", &parcelas);

            double aux;
            aux = end->reg.debitos / parcelas;

            if(end->reg.saldo < aux){
                printf("Operacao negada! Saldo insuficiente.\n");
                system("pause");
                return 0;
            }
            end->reg.saldo = end->reg.saldo - aux;
            end->reg.debitos = end->reg.debitos - aux;

            printf("Parcela da divida quitada com sucesso.\n");
            system("pause");
            return 1;
        }
    }
}

int atualizarDados(LISTA* l){
    int ID, suc;

    printf("Insira o ID do cliente: ");
    scanf("%d", &ID);

    PONT ant, i = buscarID(l, ID, &ant);
    
    if(i == NULL){
        printf("ERRO! Cliente nao existente.\n");
        system("pause");
        return 0;
    }

    printf("1 -- CPF\n");
    printf("2 -- Data de nascimento\n");
    printf("3 -- Telefone de contato\n");
    printf("4 -- CEP\n");

    int n;
    printf("Digite o numero correspondente ao dado que voce deseja atualizar: ");
    scanf("%d", &n);

    while(n != 1 && n != 2 && n != 3 && n != 4) {
        printf("Opcao invalida. Digite novamente: ");
        scanf("%d", &n);
    }

    if(n == 1){ // Atualizando o cpf
        suc = 0;

        while(suc == 0) {
            char cpf[20];
            printf("Informe o CPF (FORMATO XXX.XXX.XXX-XX): ");
            scanf("%[^\n]%*c", cpf);

            if(strlen(cpf) == 14 && cpf[3] == '.' && cpf[7] == '.' && cpf[11] == '-') {
                suc = 1;
                strcpy(i->reg.cpf, cpf);
            }
            else printf("CPF invalido. Tente novamente\n");
        }
    }

    else if(n == 2){ // Atualizar a data de nascimento
        suc = 0;

        while(suc == 0) {
            int dia, mes, ano;
            char barra1, barra2;
            printf("Digite a sua data de nascimento (FORMATO DD/MM/AAAA): ");
            scanf("%d %c %d %c %d", &dia, &barra1, &mes, &barra2, &ano);

            if(dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12 && ano >= 0 && barra1 == '/' && barra2 == '/') {
                suc = 1;
                i->reg.dataNasc.dia = dia;
                i->reg.dataNasc.mes = mes;
                i->reg.dataNasc.ano = ano;
            }
            else printf("Data invalida! Tente novamente\n");
        }
    }

    else if(n == 3){ // Atualizar o telefone
        printf("Informe um numero de contato com o codigo de area: ");
        scanf("%[^\n]%*c", i->reg.telefone);
    }

    else if(n == 4){ // Atualizar o CEP
        suc = 0;

        while(suc == 0) {
            printf("Informe o CEP (FORMATO XXXXX-XXX): ");
            char cep[20];
            scanf("%[^\n]%*c", cep);

            if(cep[5] == '-' && strlen(cep) == 9) {
                suc = 1;
                strcpy(i->reg.cep, cep);
            }
            else printf("CEP invalido. Tente novamente\n");
        }
    }

    printf("Dado atualizado com sucesso!\n");
    system("pause");
    return 1;
}

int removerCliente(LISTA* l){
    printf("1 -- Remover cliente atraves do ID\n");
    printf("2 -- Remover cliente atraves nome\n");
    printf("Digite a opcao desejada: ");

    int opcao;
    scanf("%d", &opcao);

    while(opcao != 1 && opcao != 2) {
        printf("Opcao invalida. Digite novamente: ");
        scanf("%d", &opcao);
    }

    PONT i, ant;
    
    if(opcao == 1){
        int ID;
        printf("Insira o ID do cliente: ");
        scanf("%d", &ID);

        i = buscarID(l, ID, &ant);
    }
    else if(opcao == 2) i = buscarNome(l, &ant);

    if(i == NULL) {
        printf("ERRO! Falha ao remover, cliente nao existente.\n");
        system("pause");
        return 0;
    }

    if(ant == NULL) l->inicio = i->prox;
    else ant->prox = i->prox;

    free(i);
    printf("Cliente removido com sucesso!\n");
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