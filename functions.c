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
    PONT ant, i = buscarProxEndLivre(&l, &ant);

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

void exibirCliente(LISTA* l){

    PONT end = l->inicio;

    while(end != NULL){
        
        printf("Código de ID: ......%d......\n", end->reg.ID);
        printf("Nome: ....... %s .......\n", end->reg.nome);
        printf("CPF: ........ %s .......\n", end->reg.cpf);
        printf("Data de Nascimento: %d/%d/%d\n", end->reg.dataNasc.dia, end->reg.dataNasc.mes, end->reg.dataNasc.ano);
        printf("CEP: ........ %s .......\n", end->reg.cep);
        printf("Telefone: ... %s .......\n", end->reg.telefone);
        printf("Saldo atual: R$%.2lf\n", end->reg.saldo);

        end = end->prox;
        
    }
    printf("\n\n");

}

PONT buscarID(LISTA *l, int ID, PONT* ant){

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
