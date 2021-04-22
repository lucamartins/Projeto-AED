typedef struct {
    char dia;
    char mes;
    char ano;
} NASC;

typedef struct {
    int ID;
    NASC dataNasc;
    double saldo;
    double debitos;
    char nome[60];
    char cpf[15];
    char cep[10];
    char telefone[20];
} REGISTRO;

typedef struct aux {
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
    PONT inicio;
    int cntID;
} LISTA;

void inicializarLista(LISTA* l);

int criarCliente(LISTA* l);

void preencherDadosCliente(LISTA* l, PONT i);

PONT buscarProxEndLivre(LISTA* l, PONT* ant);