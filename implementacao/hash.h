//TAD de tabela hash
#include <stdbool.h>
#define TAMANHO_MAX_CHAVE 6
#define TAMANHO_HASH 127

//Struct para o ParChaveValor que deve ser guardado na tabela hash
typedef struct ParChaveValor{
    char chave[TAMANHO_MAX_CHAVE];
    int codigo;
}Viagem;

typedef struct tabela_hash{
    Viagem tabela_hash[TAMANHO_HASH];
}TabelaHash;

//Função HASH
//Essa função recebe uma chave do tipo string e retorna o index correspondente do tipo int 
int hash(const char chave[]);

//Função para criar uma tabela hash
//Essa função aloca memoria a um ponteiro de tabela hash e retorna esse ponteiro
TabelaHash* criar_tabela_hash();

//Função para inserir um novo item na tabela hash
//Essa função recebe o ponteiro para tabela hash, a chave e valor do item a ser inserido e retorna TRUE ou FALSE para o resultado da inserção
bool inserir(TabelaHash* tabela, const char* chave, int valor);

//Função para realizar uma consulta na tabela hash
//Essa função recebe o ponteiro para a tabela hash e a chave para consulta, retornando então o valor correspondente a pesquisa
int* buscar(TabelaHash* tabela, const char* chave);

//Função para remover um item da tabela hash
//Essa função recebe o ponteiro para tabela hash, a chave e valor do item a ser inserido e retorna TRUE ou FALSE para o resultado da remoção
bool remover(TabelaHash* tabela, const char* chave);

//Função para imprimir a tabela hash
void imprimir_tabela(TabelaHash* tabela);

//Função para liberar a memória alocada a tabela hash
void liberar_tabela(TabelaHash* tabela);