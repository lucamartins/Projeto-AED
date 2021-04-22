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
        printf("Informe o CPF: ");
        scanf("%[^\n]%*c", cpf);

        if(strlen(cpf) == 14 && cpf[3] == '.' && cpf[7] == '.' && cpf[11] == '-') {
            suc = 1;
            strcpy(i->reg.cpf, cpf);
        }
        else {
            printf("CPF invalido. Tente novamente\n");
        }
    }

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