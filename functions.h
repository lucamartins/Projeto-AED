typedef struct {
    int dia;
    int mes;
    int ano;
} NASC;

typedef struct {
    char* cep;
    char* rua;
    char* setor;
    char* cidade;
    char* estado;
} ENDERECO;

typedef struct {
    int ID;
    NASC dataNasc;
    double saldo;
    double divida;
    char* nome;
    char* cpf;
    ENDERECO endereco;
    char* telefone;
} REGISTRO;

typedef struct aux {
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
    PONT inicio;
} LISTA;