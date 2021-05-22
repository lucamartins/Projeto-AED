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
        atual = atual->prox;
        *ant = atual;
    }

    return atual;
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
        scanf("%d", &valor);

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

int criarCliente(LISTA* l) {
    PONT ant, i = buscarProxEndLivre(l, &ant);

    i = (PONT) malloc(sizeof(ELEMENTO));

    if(ant == NULL) {
        i->prox = l->inicio;
        l->inicio = i;
    }
    else {
        i->prox = ant->prox;
        ant->prox = i;
    }

    preencherDadosCliente(l, i);    

    return i->reg.ID;
}

void exibirClientes(LISTA* l){         //funcao para exibir os detalhes de todos os clientes cadastrados
    PONT end = l->inicio;

    while(end != NULL){
        printf("Código de ID: ......%d......\n", end->reg.ID);
        printf("Nome: ....... %s .......\n", end->reg.nome);
        printf("CPF: ........ %s .......\n", end->reg.cpf);
        printf("Data de Nascimento: %d/%d/%d\n", end->reg.dataNasc.dia, end->reg.dataNasc.mes, end->reg.dataNasc.ano);
        printf("CEP: ........ %s .......\n", end->reg.cep);
        printf("Telefone: ... %s .......\n", end->reg.telefone);
        printf("Saldo atual: R$%.2lf\n", end->reg.saldo);
        printf("Débitos: ....R$%2.lf\n\n", end->reg.debitos);

        end = end->prox;   
    }
    printf("\n\n");
}

void exibirConta(LISTA* l){             //Funcao para exibir detalhes de uma conta especifica
    int opcao;
    printf("Deseja acessar os detalhes da conta pelo nome ou pelo ID ?\n\n");
    printf("1- Nome\n2- ID");
    scanf("%d", &opcao);
    
    if(opcao == 1){             //opcao para procurar a conta pelo nome
        PONT ant, end = buscarNome(l, &ant);
        
        if(end == NULL){
            printf("Erro ! Cliente nao existente.\n");
        }else{
            printf("Detalhes da conta desejada: \n\n");
            printf("Código de ID: ......%d......\n", end->reg.ID);
            printf("Nome: ....... %s .......\n", end->reg.nome);
            printf("CPF: ........ %s .......\n", end->reg.cpf);
            printf("Data de Nascimento: %d/%d/%d\n", end->reg.dataNasc.dia, end->reg.dataNasc.mes, end->reg.dataNasc.ano);
            printf("CEP: ........ %s .......\n", end->reg.cep);
            printf("Telefone: ... %s .......\n", end->reg.telefone);
            printf("Saldo atual: R$%.2lf\n", end->reg.saldo);
            printf("Débitos: ....R$%2.lf\n\n", end->reg.debitos);
        }
    }else if(opcao == 2){       //opcao para procurar a conta pelo ID

        int ID;
        printf("Insira o ID do cliente: ");
        scanf("%d", &ID);
        PONT ant, end = buscarID(l, ID, &ant);
        
        if(end == NULL){
            printf("Erro ! Cliente nao existente.\n");
        }else{
            printf("Detalhes da conta desejada: \n\n");
            printf("Código de ID: ......%d......\n", end->reg.ID);
            printf("Nome: ....... %s .......\n", end->reg.nome);
            printf("CPF: ........ %s .......\n", end->reg.cpf);
            printf("Data de Nascimento: %d/%d/%d\n", end->reg.dataNasc.dia, end->reg.dataNasc.mes, end->reg.dataNasc.ano);
            printf("CEP: ........ %s .......\n", end->reg.cep);
            printf("Telefone: ... %s .......\n", end->reg.telefone);
            printf("Saldo atual: R$%.2lf\n", end->reg.saldo);
            printf("Débitos: ....R$%2.lf\n\n", end->reg.debitos);
        }
    }else{
        printf("Opcão não existe\n");
    }
    return;
}


PONT buscarID(LISTA* l, int ID, PONT* ant){ //buscar o cliente pelo ID

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

PONT buscarNome(LISTA* l, PONT* ant){ // buscar o cliente pelo nome
    *ant = NULL;
    PONT end = l->inicio;
    
    char nome[60];
    printf("Insira o nome do cliente.\n");
    scanf("%[^\n]%*c", nome);

    while(end != NULL){

        if(strcmp(end->reg.nome, nome) == 0){
            return end;
        }
        *ant = end;
        end = end->prox;
    }
    return NULL;
}

int removerCliente(LISTA* l, int opcao){ //remover o cliente ou pelo ID ou pelo nome
    if(opcao == 1){
        int ID;
        printf("Insira o ID do cliente.\n");    //removendo cliente atraves do id
        scanf("%d", &ID);

        PONT i, ant;

        i = buscarID(l, ID, &ant);

        if(i == NULL) return 0;

        if(ant == NULL) l->inicio = i->prox;
        else ant->prox = i->prox;
        free(i);    
        return 1;
    }
    else if(opcao == 2){        //removendo cliente atraves do nome

        PONT i, ant;

        i = buscarNome(l, &ant);

        if(i == NULL) return 0;

        if(ant == NULL) l->inicio = i->prox;
        else ant->prox = i->prox;
        free(i);    
        return 1;
    }
    else{
        return 0;
    } 
}

int atualizarDados(LISTA* l){       //funcao para atualizar os dados do cliente escolhido
    int ID, suc;
    printf("Insira o ID do cliente: ");
    scanf("%d", &ID);

               
    PONT ant, i = buscarID(l, ID, &ant);
    
    if(i == NULL){
        printf("Erro ! Cliente nao existente.\n");
        return 0;
    }else{
        int n;
        printf("Qual dados voce deseja atualizar?\n\n");
        printf("1- CPF\n2- Data de nascimento\n3- Telefone de contato\n4- CEP\n\n");
        scanf("%d", &n);

        if(n == 1){         //atualizando o cpf
            suc = 0;

            while(suc == 0) {
                char cpf[20];
                printf("Informe o CPF (FORMATO XXX.XXX.XXX-XX): ");
                scanf("%[^\n]%*c", cpf);

                if(strlen(cpf) == 14 && cpf[3] == '.' && cpf[7] == '.' && cpf[11] == '-') {
                    suc = 1;
                    strcpy(i->reg.cpf, cpf);
                    return 1;
                }
                else {
                    printf("CPF invalido. Tente novamente\n");
                    return 0;
                }
            }
        }
        else if(n == 2){        //atualizar a data de nascimento
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
                return 1;
            }else {
            printf("Data invalida. Tente novamente\n");
            return 0;
            }
        }
    }
        else if(n == 3){        //atualizar o telefone
            printf("Informe um numero de contato com o codigo de area: ");
            scanf("%[^\n]%*c", i->reg.telefone);
            return 1;
        }
        else if(n == 4){       //atualizar o CEP

            suc = 0;
            while(suc == 0) {
                printf("Informe o CEP (FORMATO XXXXX-XXX): ");
                char cep[20];
                scanf("%[^\n]%*c", cep);

                if(cep[5] == '-' && strlen(cep) == 9) {
                    suc = 1;
                    strcpy(i->reg.cep, cep);
                    return 1;
                }
                else {
                    printf("CEP invalido. Tente novamente\n");
                    return 0;
                }
            }
        }
        else{
            printf("Opcao nao existe!\n");
            return 0;
        }
    }
    
}

int inserirDividas(LISTA* l){

    int ID, suc;
    double dividas;

    printf("Insira o ID do cliente :");
    scanf("%d", &ID);

    PONT ant, end = buscarID(l, ID, &ant);
    if(end == NULL){
        printf("Cliente nao existente!\n");
        return 0;
    }
    suc = 0;
    while(suc == 0){
        printf("Insira o valor de dividas (positivo): ");
        scanf("%lf", &dividas);
        if(dividas < 0){
            printf("Voce inseriu um valor negativo, tente novamente.\n");
        }else{
            end->reg.debitos = end->reg.debitos - dividas;
            printf("Debito inserido com sucesso\n");
            suc = 1;
        }
    }
    return 1;
}

int quitarDividas(LISTA* l){

    int ID, opcao;
    printf("Insira o ID do cliente: ");
    scanf("%d", &ID);

    PONT ant, end = buscarID(l, ID, &ant);

    if(end == NULL){
        printf("cliente nao existente.\n");
        return 0;
    }
    printf("Voce deseja quitar a sua divida em uma vez ou deseja pagar uma parcela?\n\n");
    printf("1- Pagar tudo a vista\n2- Pagar uma parcela");
    scanf("%d", &opcao);
    while(1){
        if(opcao == 1){
            
            if(end->reg.saldo < end->reg.debitos){
                printf("Saldo insuficiente.\n");
                return 0;
            }
            double aux = end->reg.debitos;
            end->reg.saldo = end->reg.saldo - aux;
            end->reg.debitos = end->reg.debitos + aux;
            printf("Divida total quitada com sucesso.\n\n");
            return 1;
        }
        else if(opcao == 2){
            int parcelas;
            printf("Quantas vezes deseja dividir a divida?\n");
            scanf("%d", &parcelas);

            double aux;
            aux = end->reg.debitos / parcelas;

            if(end->reg.saldo < aux){
                printf("Saldo insuficiente.\n");
                return 0;
            }
            end->reg.saldo = end->reg.saldo - aux;
            end->reg.debitos = end->reg.debitos + aux;

            printf("Parcela quitada com sucesso.\n");

            return 1;
        }else{
            printf("Opcao nao existente.\n");
        }
    }

}