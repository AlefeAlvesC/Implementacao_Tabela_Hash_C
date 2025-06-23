//TAD de tabela hash
#ifndef _HASH_H_
#define _HASH_H_

#include <stdbool.h>
#include "lista_encad.h"

#define TAMANHO_HASH 127 //127 pois no trabalho pede que seja um número primo, mas podemos deixar um número primo menor do que 120 tbm

typedef struct tabela_hash{
    Lista *tabela_hash[TAMANHO_HASH];
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

// Funcao para buscar todas as ocorrencia de uma chave na tabela hash e imprimir seus valores.
// Devolve o numero de ocorrencias achadas na hash
int buscar_todas(TabelaHash* tabela, const char* chave);

//Função para remover um item da tabela hash
//Essa função recebe o ponteiro para tabela hash, a chave e valor do item a ser inserido e retorna TRUE ou FALSE para o resultado da remoção
bool remover(TabelaHash* tabela, const char* chave);

//Função para imprimir a tabela hash
void imprimir_tabela(TabelaHash* tabela);

//Função para liberar a memória alocada a tabela hash
void liberar_tabela(TabelaHash* tabela);

#endif