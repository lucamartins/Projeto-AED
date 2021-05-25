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

PONT buscarProxEndLivre(LISTA* l, PONT* ant);

void preencherDadosCliente(LISTA* l, PONT i);

PONT buscarID(LISTA* l, int ID, PONT* ant);

PONT buscarNome(LISTA* l, PONT* ant);

int criarCliente(LISTA* l); // op1

void exibirClientes(LISTA* l); // op2

void exibirConta(LISTA* l); // op3

int atualizarDados(LISTA* l); // op4

int inserirDividas(LISTA* l); // op5

int quitarDividas(LISTA* l); // op6

int removerCliente(LISTA* l); // op7