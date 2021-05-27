typedef struct {
    char dia[4];
    char mes[4];
    char ano[6];
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

//
// Funcoes auxiliares do programa
//

void inicializarLista(LISTA* l);

PONT buscarProxEndLivre(LISTA* l, PONT* ant);

PONT buscarPeloID(LISTA* l, int ID, PONT* ant);

PONT lerEbuscarNome(LISTA* l, PONT* ant);

void preencherDadosCliente(LISTA* l, PONT i);

PONT encontrarClienteMenu(LISTA* l, PONT* ant);

//
// Funcoes de acesso direto pela main
//

int criarCliente(LISTA* l); // op1

void exibirClientes(LISTA* l); // op2

void procurarCliente(LISTA* l); // op3

int atualizarDados(LISTA* l); // op4

int removerCliente(LISTA* l); // op5

int inserirDivida(LISTA* l); // op6

int quitarDividas(LISTA* l); // op7

int transferencia(LISTA* l); // op8

int deposito(LISTA* l); // op9

int saque(LISTA* l); // op10